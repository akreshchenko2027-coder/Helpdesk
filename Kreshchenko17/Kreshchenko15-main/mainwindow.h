#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

#include "tickettablemodel.h"
#include "ticketfilterproxymodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    TicketTableModel *model;
    TicketFilterProxyModel *proxy;

    QTableView *table;
    QLineEdit *searchEdit;
    QComboBox *statusCombo;
    QComboBox *priorityCombo;
    QLabel *emptyLabel;

    void updateEmptyState();
};
