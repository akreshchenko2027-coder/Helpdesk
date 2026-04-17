#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "requestdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model = new RequestTableModel(this);

    ui->tableView->setModel(m_model);

    connect(ui->actionAdd, &QAction::triggered,
            this, &MainWindow::onAddTriggered);

    connect(ui->actionEdit, &QAction::triggered,
            this, &MainWindow::onEditTriggered);

    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::onOpenTriggered);

    connect(ui->actionRemove, &QAction::triggered,
            this, &MainWindow::onRemoveTriggered);

    connect(ui->tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::updateActionsState);

    updateActionsState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::currentRow() const
{
    auto rows = ui->tableView->selectionModel()->selectedRows();

    if(rows.isEmpty())
        return -1;

    return rows.first().row();
}

void MainWindow::updateActionsState()
{
    bool hasSelection = ui->tableView->selectionModel()->hasSelection();

    ui->actionOpen->setEnabled(hasSelection);
    ui->actionEdit->setEnabled(hasSelection);
    ui->actionRemove->setEnabled(hasSelection);
}

void MainWindow::onAddTriggered()
{
    auto *dialog = new RequestDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setMode(RequestDialog::Mode::Create);

    connect(dialog, &RequestDialog::createRequested,
            this, [=](const Request &r)
            {
                m_model->appendRequest(r);
                dialog->close();
            });

    dialog->show();
}

void MainWindow::onEditTriggered()
{
    int row = currentRow();
    if(row < 0) return;

    Request req = m_model->requestAt(row);

    auto *dialog = new RequestDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->setMode(RequestDialog::Mode::Edit);
    dialog->loadRequest(req);

    connect(dialog, &RequestDialog::updateRequested,
            this, [=](const Request &r)
            {
                m_model->replaceRequest(row, r);
                dialog->close();
            });

    dialog->show();
}

void MainWindow::onOpenTriggered()
{
    int row = currentRow();
    if(row < 0) return;

    Request req = m_model->requestAt(row);

    auto *dialog = new RequestDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->setMode(RequestDialog::Mode::View);
    dialog->loadRequest(req);

    dialog->show();
}

void MainWindow::onRemoveTriggered()
{
    int row = currentRow();
    if(row < 0) return;

    auto result = QMessageBox::question(
        this,
        "Remove",
        "Delete selected request?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
        );

    if(result == QMessageBox::Yes)
        m_model->eraseRequest(row);
}
