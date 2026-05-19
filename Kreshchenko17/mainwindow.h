#pragma once

#include <QMainWindow>
#include <QStandardItemModel>

#include "databasemanager.h"
#include "vaultrepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNew();
    void onDelete();
    void onItemChanged(QStandardItem *item);
    void onExit();

private:
    void setupUi();
    void loadData();

    Ui::MainWindow *ui;
    QStandardItemModel *model;

    DatabaseManager dbManager;
    VaultRepository *repo;

    bool loading = false;
};
