#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDateTime>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    setupUi();

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onNew);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onDelete);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onExit);

    connect(model, &QStandardItemModel::itemChanged,
            this, &MainWindow::onItemChanged);

    dbManager.open("vault.db");
    dbManager.init();

    repo = new VaultRepository(dbManager.db());

    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUi()
{
    ui->tableView->setModel(model);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setEditTriggers(
        QAbstractItemView::DoubleClicked |
        QAbstractItemView::EditKeyPressed |
        QAbstractItemView::SelectedClicked
        );
}

void MainWindow::loadData()
{
    loading = true;

    model->setRowCount(0);

    model->setHorizontalHeaderLabels({
        "ID","Title","Username","Password","Website","Category","Updated"
    });

    auto items = repo->loadAll();

    for (const auto &r : items)
    {
        QList<QStandardItem*> row;

        row << new QStandardItem(QString::number(r.id))
            << new QStandardItem(r.title)
            << new QStandardItem(r.username)
            << new QStandardItem(r.password)
            << new QStandardItem(r.website)
            << new QStandardItem(r.category)
            << new QStandardItem(r.updatedAt);

        model->appendRow(row);
    }

    loading = false;
}

void MainWindow::onNew()
{
    VaultRecord r;
    r.title = "New";
    r.username = "";
    r.password = "";
    r.website = "";
    r.category = "";
    r.updatedAt = QDateTime::currentDateTime().toString();

    repo->insert(r);
    loadData();
}

void MainWindow::onDelete()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    int id = model->item(index.row(),0)->text().toInt();

    if (QMessageBox::question(this,"Delete","Delete record?")
        == QMessageBox::Yes)
    {
        repo->remove(id);
        loadData();
    }
}

void MainWindow::onItemChanged(QStandardItem *item)
{
    if (loading || !item) return;
    if (item->column() == 0) return;

    int row = item->row();

    VaultRecord r;
    r.id = model->item(row,0)->text().toInt();
    r.title = model->item(row,1)->text();
    r.username = model->item(row,2)->text();
    r.password = model->item(row,3)->text();
    r.website = model->item(row,4)->text();
    r.category = model->item(row,5)->text();
    r.updatedAt = QDateTime::currentDateTime().toString();

    repo->update(r);
}

void MainWindow::onExit()
{
    close();
}
