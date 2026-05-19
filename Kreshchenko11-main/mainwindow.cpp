#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticketdialog.h"

#include <QMessageBox>
#include <QItemSelectionModel>
#include <QStandardItem>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(new QStandardItemModel(this))
    , m_ticketDialog(nullptr)
{
    ui->setupUi(this);

    setupModel();
    fillDemoData();
    setupConnections();
    updateActionsState();

    setWindowTitle("Helpdesk");
    resize(900, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    QStringList headers;
    headers << "No/ID" << "Title" << "Status" << "Priority" << "Created" << "Assignee";
    m_model->setHorizontalHeaderLabels(headers);

    ui->tableViewTickets->setModel(m_model);
    ui->tableViewTickets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewTickets->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewTickets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewTickets->setAlternatingRowColors(true);
    ui->tableViewTickets->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewTickets->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewTickets->verticalHeader()->setVisible(false);
}

void MainWindow::fillDemoData()
{
    QList<QList<QString>> rows = {
        {"1001", "Cannot login to account", "Open", "High", "2026-03-14 09:15", "Ivan"},
        {"1002", "Printer not working", "In Progress", "Medium", "2026-03-14 10:40", "Olena"},
        {"1003", "Need software installation", "New", "Low", "2026-03-14 11:05", "Andrii"}
    };

    for (const auto &rowData : rows) {
        QList<QStandardItem*> rowItems;
        for (const QString &text : rowData) {
            rowItems << new QStandardItem(text);
        }
        m_model->appendRow(rowItems);
    }
}

void MainWindow::setupConnections()
{
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onActionAbout);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);

    connect(ui->tableViewTickets->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::updateActionsState);

    connect(ui->tableViewTickets->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this,
            &MainWindow::updateActionsState);
}

int MainWindow::currentRow() const
{
    QModelIndex index = ui->tableViewTickets->currentIndex();
    if (!index.isValid())
        return -1;
    return index.row();
}

void MainWindow::updateActionsState()
{
    bool hasSelection = currentRow() >= 0;
    ui->actionView->setEnabled(hasSelection);
    ui->actionEdit->setEnabled(hasSelection);
    ui->actionDelete->setEnabled(hasSelection);
}

void MainWindow::onActionNew()
{
    if (m_ticketDialog) {
        m_ticketDialog->close();
        m_ticketDialog->deleteLater();
        m_ticketDialog = nullptr;
    }

    m_ticketDialog = new TicketDialog(this);
    m_ticketDialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_ticketDialog, &QObject::destroyed, this, [this]() {
        m_ticketDialog = nullptr;
    });

    m_ticketDialog->setMode(TicketDialog::ModeNew);
    m_ticketDialog->show();
    m_ticketDialog->raise();
    m_ticketDialog->activateWindow();
}

void MainWindow::onActionView()
{
    int row = currentRow();
    if (row < 0)
        return;

    if (m_ticketDialog) {
        m_ticketDialog->close();
        m_ticketDialog->deleteLater();
        m_ticketDialog = nullptr;
    }

    m_ticketDialog = new TicketDialog(this);
    m_ticketDialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_ticketDialog, &QObject::destroyed, this, [this]() {
        m_ticketDialog = nullptr;
    });

    m_ticketDialog->setTicketData(
        m_model->item(row, 0)->text(),
        m_model->item(row, 1)->text(),
        "User cannot sign in. Password reset may be required.",
        m_model->item(row, 2)->text(),
        m_model->item(row, 3)->text(),
        m_model->item(row, 4)->text()
        );

    m_ticketDialog->setMode(TicketDialog::ModeView);
    m_ticketDialog->show();
    m_ticketDialog->raise();
    m_ticketDialog->activateWindow();
}

void MainWindow::onActionEdit()
{
    int row = currentRow();
    if (row < 0)
        return;

    if (m_ticketDialog) {
        m_ticketDialog->close();
        m_ticketDialog->deleteLater();
        m_ticketDialog = nullptr;
    }

    m_ticketDialog = new TicketDialog(this);
    m_ticketDialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_ticketDialog, &QObject::destroyed, this, [this]() {
        m_ticketDialog = nullptr;
    });

    m_ticketDialog->setTicketData(
        m_model->item(row, 0)->text(),
        m_model->item(row, 1)->text(),
        "Editable ticket description for selected request.",
        m_model->item(row, 2)->text(),
        m_model->item(row, 3)->text(),
        m_model->item(row, 4)->text()
        );

    m_ticketDialog->setMode(TicketDialog::ModeEdit);
    m_ticketDialog->show();
    m_ticketDialog->raise();
    m_ticketDialog->activateWindow();
}

void MainWindow::onActionDelete()
{
    int row = currentRow();
    if (row < 0)
        return;

    auto reply = QMessageBox::question(
        this,
        "Delete ticket",
        "Delete selected ticket?"
        );

    if (reply == QMessageBox::Yes) {
        m_model->removeRow(row);
    }

    updateActionsState();
}

void MainWindow::onActionAbout()
{
    QMessageBox::about(
        this,
        "About Helpdesk",
        "Helpdesk demo application\n"
        "Практична робота No11\n"
        "Qt Widgets, QMainWindow, QTableView, немодальні діалоги."
        );
}
