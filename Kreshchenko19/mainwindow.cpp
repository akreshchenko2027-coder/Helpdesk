#include "mainwindow.h"
#include "PasswordRepository.h"
#include "PasswordTableModel.h"
#include "PasswordFilterProxyModel.h"
#include "PasswordLeakChecker.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_repository = new PasswordRepository();
    m_leakChecker = new PasswordLeakChecker(this);

    setupUI();

    m_tableModel = new PasswordTableModel(m_repository, this);
    m_proxyModel = new PasswordFilterProxyModel(this);

    m_proxyModel->setSourceModel(m_tableModel);

    m_tableView->setModel(m_proxyModel);

    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setAlternatingRowColors(true);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_searchEdit, &QLineEdit::textChanged, this, [this](const QString &text){
        m_proxyModel->setTextFilter(text);
        updateEmptyState();
    });

    connect(m_categoryCombo, &QComboBox::currentTextChanged, this, [this](const QString &category){
        m_proxyModel->setCategoryFilter(category);
        updateEmptyState();
    });

    connect(m_btnCheckLeak, &QPushButton::clicked, this, &MainWindow::onCheckLeakClicked);
    connect(m_leakChecker, &PasswordLeakChecker::checkCompleted, this, &MainWindow::onLeakCheckCompleted);
    connect(m_leakChecker, &PasswordLeakChecker::checkFailed, this, &MainWindow::onLeakCheckFailed);

    reloadTable();
}

MainWindow::~MainWindow() { delete m_repository; }

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Search by Title...");
    m_categoryCombo = new QComboBox(this);
    m_categoryCombo->addItems({"All", "Email", "Social", "Banking", "Work", "Other"});

    topLayout->addWidget(new QLabel("Search:", this));
    topLayout->addWidget(m_searchEdit);
    topLayout->addWidget(new QLabel("Category:", this));
    topLayout->addWidget(m_categoryCombo);

    m_tableView = new QTableView(this);

    m_emptyLabel = new QLabel("No results found.", this);
    m_emptyLabel->setAlignment(Qt::AlignCenter);
    m_emptyLabel->setStyleSheet("color : gray; font-size: 16px;");
    m_emptyLabel->hide();

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    m_btnAdd = new QPushButton("New Record", this);
    m_btnDelete = new QPushButton("Delete Selected", this);
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_btnAdd);
    bottomLayout->addWidget(m_btnDelete);

    connect(m_btnAdd, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(m_btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *netLayout = new QHBoxLayout();
    m_passwordCheckEdit = new QLineEdit(this);
    m_passwordCheckEdit->setPlaceholderText("Enter password to check leaks...");
    m_passwordCheckEdit->setEchoMode(QLineEdit::Password);

    m_btnCheckLeak = new QPushButton("Check Password via API", this);
    m_statusLabel = new QLabel("Status: Idle", this);
    m_statusLabel->setStyleSheet("color: blue; font-weight: bold;");

    netLayout->addWidget(new QLabel("Security Check:", this));
    netLayout->addWidget(m_passwordCheckEdit);
    netLayout->addWidget(m_btnCheckLeak);
    netLayout->addWidget(m_statusLabel);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_tableView);
    mainLayout->addWidget(m_emptyLabel);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(line);
    mainLayout->addLayout(netLayout);
}

void MainWindow::reloadTable()
{
    m_tableModel->setItems(m_repository->loadAll());
    updateEmptyState();
}

void MainWindow::updateEmptyState()
{
    bool empty = (m_proxyModel->rowCount() == 0);
    m_tableView->setVisible(!empty);
    m_emptyLabel->setVisible(empty);
}

void MainWindow::onAddClicked()
{
    PasswordRecord r; r.title = "New Title"; r.login = "user"; r.category = "Other";
    if (m_repository->insert(r)) reloadTable();
}

void MainWindow::onDeleteClicked()
{
    QModelIndex proxyIndex = m_tableView->currentIndex();
    if (!proxyIndex.isValid()) return;
    PasswordRecord record = m_tableModel->itemAt(m_proxyModel->mapToSource(proxyIndex).row());

    if (QMessageBox::question(this, "Confirm", "Delete: " + record.title + "?") == QMessageBox::Yes) {
        if (m_repository->remove(record.id)) reloadTable();
    }
}

void MainWindow::onCheckLeakClicked()
{
    QString pass = m_passwordCheckEdit->text();
    if (pass.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a password first.");
        return;
    }

    m_statusLabel->setText("Status: Connecting to API...");
    m_btnCheckLeak->setEnabled(false);
}

void MainWindow::onLeakCheckCompleted(bool found, int count)
{
    m_btnCheckLeak->setEnabled(true);
    if (found) {
        m_statusLabel->setStyleSheet("color: red; font-weight: bold;");
        m_statusLabel->setText(QString("⚠️ CRITICAL LEAK! Found %1 times.").arg(count));
    } else {
        m_statusLabel->setStyleSheet("color: green; font-weight: bold;");
        m_statusLabel->setText("✅ SAFE. Not found in leaks.");
    }
}

void MainWindow::onLeakCheckFailed(const QString &message)
{
    m_btnCheckLeak->setEnabled(true);
    m_statusLabel->setStyleSheet("color: gray;");
    m_statusLabel->setText("Status: Check failed.");
    QMessageBox::critical(this, "Network Error", message);
}
