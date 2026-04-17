#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TicketDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActionNew();
    void onActionView();
    void onActionEdit();
    void onActionDelete();
    void onActionAbout();

    void updateActionsState();

private:
    void setupModel();
    void setupConnections();
    void fillDemoData();
    int currentRow() const;

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_model;

    TicketDialog *m_ticketDialog;
};
#endif // MAINWINDOW_H
