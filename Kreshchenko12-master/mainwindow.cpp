#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHeaderView>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new TicketTableModel(this);

    ui->tableView->setModel(model);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    auto *h = ui->tableView->horizontalHeader();

    h->setSectionResizeMode(TicketTableModel::TitleCol, QHeaderView::Stretch);
    h->setSectionResizeMode(TicketTableModel::IdCol, QHeaderView::ResizeToContents);
    h->setSectionResizeMode(TicketTableModel::PriorityCol, QHeaderView::ResizeToContents);
    h->setSectionResizeMode(TicketTableModel::StatusCol, QHeaderView::ResizeToContents);
    h->setSectionResizeMode(TicketTableModel::CreatedCol, QHeaderView::ResizeToContents);

    fillTestData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTestData()
{
    for(int i = 1; i <= 8; i++)
    {
        Ticket t;

        t.id = i;
        t.title = "Problem #" + QString::number(i);
        t.priority = (i % 2 == 0) ? "High" : "Low";
        t.status = (i % 3 == 0) ? "Closed" : "Open";
        t.createdAt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");

        model->addTicket(t);
    }
}

void MainWindow::addTicket()
{
    Ticket t;

    t.id = model->rowCount() + 1;
    t.title = "New Ticket";
    t.priority = "Medium";
    t.status = "Open";
    t.createdAt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");

    model->addTicket(t);
}

void MainWindow::deleteTicket()
{
    QModelIndex cur = ui->tableView->currentIndex();

    if(!cur.isValid())
        return;

    model->removeTicket(cur.row());
}
