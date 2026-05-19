#include "mainwindow.h"
#include <QVBoxLayout>
#include <QDateTime>

int findNextId(const QList<RequestEntry> &items)
{
    int maxId = 0;
    for (const auto &e : items)
        if (e.id > maxId) maxId = e.id;
    return maxId + 1;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new RequestTableModel(this);
    repo = new CsvTicketRepository("tickets.csv");

    table = new QTableView;
    table->setModel(model);

    addBtn = new QPushButton("Add");

    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(central);

    layout->addWidget(table);
    layout->addWidget(addBtn);

    setCentralWidget(central);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addRequest);

    loadData();
}

void MainWindow::loadData()
{
    QList<RequestEntry> items = repo->loadAll();
    model->setItems(items);
    nextId = findNextId(items);
}

void MainWindow::saveData()
{
    repo->saveAll(model->items());
}

void MainWindow::addRequest()
{
    RequestEntry e;

    e.id = nextId++;
    e.title = "Нова заявка";
    e.priority = "High";
    e.status = "Open";
    e.description = "Опис";
    e.createdAt = QDateTime::currentDateTime();

    model->addItem(e);

    saveData();
}
