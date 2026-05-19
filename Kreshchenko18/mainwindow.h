#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class PasswordRepository;
class PasswordTableModel;
class PasswordFilterProxyModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddClicked();
    void onDeleteClicked();
    void updateEmptyState();

private:
    void setupUI();
    void reloadTable();

    PasswordRepository *m_repository;
    PasswordTableModel *m_tableModel;
    PasswordFilterProxyModel *m_proxyModel;

    // UI Елементи
    QTableView *m_tableView;
    QLineEdit *m_searchEdit;
    QComboBox *m_categoryCombo;
    QPushButton *m_btnAdd;
    QPushButton *m_btnDelete;
    QLabel *m_emptyLabel;
};

#endif // MAINWINDOW_H
