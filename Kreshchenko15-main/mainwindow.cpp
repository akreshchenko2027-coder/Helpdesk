#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow()
{
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    // --- SEARCH ---
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Search tickets...");

    // --- FILTERS ---
    statusCombo = new QComboBox;
    statusCombo->addItem("");
    statusCombo->addItems({"Open","In Progress","Closed"});

    priorityCombo = new QComboBox;
    priorityCombo->addItem("");
    priorityCombo->addItems({"Low","Medium","High"});

    QHBoxLayout *filters = new QHBoxLayout;
    filters->addWidget(searchEdit);
    filters->addWidget(statusCombo);
    filters->addWidget(priorityCombo);

    // --- BUTTONS ---
    QPushButton *addBtn = new QPushButton("Add");
    QPushButton *deleteBtn = new QPushButton("Delete");

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(addBtn);
    buttons->addWidget(deleteBtn);

    // --- TABLE ---
    table = new QTableView;

    emptyLabel = new QLabel("No tickets found");
    emptyLabel->setAlignment(Qt::AlignCenter);

    layout->addLayout(filters);
    layout->addLayout(buttons);
    layout->addWidget(table);
    layout->addWidget(emptyLabel);

    central->setLayout(layout);
    setCentralWidget(central);

    // --- MODEL ---
    model = new TicketTableModel(this);

    proxy = new TicketFilterProxyModel(this);
    proxy->setSourceModel(model);

    table->setModel(proxy);
    table->setSortingEnabled(true); // СОРТУВАННЯ

    // --- CONNECT FILTERS ---
    connect(searchEdit,&QLineEdit::textChanged,
            proxy,&TicketFilterProxyModel::setTextFilter);

    connect(statusCombo,&QComboBox::currentTextChanged,
            proxy,&TicketFilterProxyModel::setStatusFilter);

    connect(priorityCombo,&QComboBox::currentTextChanged,
            proxy,&TicketFilterProxyModel::setPriorityFilter);

    // --- EMPTY STATE ---
    connect(proxy,&QAbstractItemModel::modelReset,
            this,&MainWindow::updateEmptyState);

    connect(proxy,&QAbstractItemModel::rowsInserted,
            this,&MainWindow::updateEmptyState);

    connect(proxy,&QAbstractItemModel::rowsRemoved,
            this,&MainWindow::updateEmptyState);

    // --- DOUBLE CLICK ---
    connect(table,&QTableView::doubleClicked,this,
            [this](const QModelIndex &proxyIndex)
            {
                QModelIndex sourceIndex = proxy->mapToSource(proxyIndex);
                Ticket t = model->ticketAt(sourceIndex.row());

                QMessageBox::information(this,"Ticket",
                                         "Title: " + t.title +
                                             "\nStatus: " + t.status +
                                             "\nPriority: " + t.priority);
            });

    // --- ADD BUTTON ---
    connect(addBtn,&QPushButton::clicked,this,[this]()
            {
                int id = model->rowCount() + 1;

                model->addTicket({
                    id,
                    "New ticket",
                    "Open",
                    "Low",
                    QDateTime::currentDateTime()
                });
            });

    // --- DELETE BUTTON ---
    connect(deleteBtn,&QPushButton::clicked,this,[this]()
            {
                QModelIndex proxyIndex = table->currentIndex();
                if (!proxyIndex.isValid()) return;

                QModelIndex sourceIndex = proxy->mapToSource(proxyIndex);

                model->removeTicket(sourceIndex.row());
            });

    // --- DEMO DATA ---
    model->addTicket({1,"Printer not working","Open","High",QDateTime::currentDateTime()});
    model->addTicket({2,"Install software","Closed","Low",QDateTime::currentDateTime()});
    model->addTicket({3,"Network problem","In Progress","Medium",QDateTime::currentDateTime()});

    updateEmptyState();
}

void MainWindow::updateEmptyState()
{
    bool empty = proxy->rowCount() == 0;

    emptyLabel->setVisible(empty);
    table->setVisible(!empty);
}
