#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);

    setupTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable()
{
    model->setColumnCount(7);

    model->setHorizontalHeaderLabels({
        "ID",
        "Title",
        "Username",
        "Password",
        "Website",
        "Category",
        "UpdatedAt"
    });

    ui->tableViewPasswords->setModel(model);

    ui->tableViewPasswords->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewPasswords->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewPasswords->setEditTriggers(
        QAbstractItemView::DoubleClicked |
        QAbstractItemView::SelectedClicked |
        QAbstractItemView::EditKeyPressed
        );

    ui->tableViewPasswords->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_actionNew_triggered()
{
    int row = model->rowCount();

    model->insertRow(row);

    for(int i=0;i<7;i++)
        model->setItem(row,i,new QStandardItem(""));

    model->setData(model->index(row,0), row + 1);
    model->setData(model->index(row,6),
                   QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"));

    ui->tableViewPasswords->selectRow(row);
    ui->tableViewPasswords->edit(model->index(row,1));
}

void MainWindow::on_actionEdit_triggered()
{
    QModelIndex current = ui->tableViewPasswords->currentIndex();

    if(current.isValid())
        ui->tableViewPasswords->edit(current);
}

void MainWindow::on_actionDelete_triggered()
{
    QModelIndex current = ui->tableViewPasswords->currentIndex();

    if(!current.isValid())
        return;

    int row = current.row();

    auto answer = QMessageBox::question(
        this,
        "Delete",
        "Видалити вибраний запис?"
        );

    if(answer == QMessageBox::Yes)
        model->removeRow(row);
}

void MainWindow::on_actionSave_triggered()
{
    QMessageBox::information(
        this,
        "Save",
        "Дані успішно збережені (умовно)."
        );
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
