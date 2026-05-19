#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>

#include "requesttablemodel.h"
#include "csvticketrepository.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    RequestTableModel *model;
    CsvTicketRepository *repo;

    QTableView *table;
    QPushButton *addBtn;

    int nextId;

    void loadData();
    void saveData();

private slots:
    void addRequest();
};

#endif
