#include "mainwindow.h"
#include "PasswordRepository.h"
#include "PasswordTableModel.h"
#include "PasswordFilterProxyModel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_repository = new PasswordRepository();
    setupUI();

    // Ініціалізація моделей
    m_tableModel = new PasswordTableModel(m_repository, this);
    m_proxyModel = new PasswordFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_tableModel);

    m_tableView->setModel(m_proxyModel);

    // Налаштування таблиці
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setAlternatingRowColors(true);
    m_tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Підключення фільтрів
    connect(m_searchEdit, &QLineEdit::textChanged, this, [this](const QString &text){
        m_proxyModel->setTextFilter(text);
        updateEmptyState();
    });

    connect(m_categoryCombo, &QComboBox::currentTextChanged, this, [this](const QString &category){
        m_proxyModel->setCategoryFilter(category);
        updateEmptyState();
    });

    reloadTable();
}

MainWindow::~MainWindow()
{
    delete m_repository;
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Панель інструментів (Пошук та Фільтр)
    QHBoxLayout *topLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Search by Title...");

    m_categoryCombo = new QComboBox(this);
    m_categoryCombo->addItems({"All", "Email", "Social", "Banking", "Work", "Other"});

    topLayout->addWidget(new QLabel("Search:", this));
    topLayout->addWidget(m_searchEdit);
    topLayout->addWidget(new QLabel("Category:", this));
    topLayout->addWidget(m_categoryCombo);

    // Таблиця
    m_tableView = new QTableView(this);

    // Повідомлення про порожній результат
    m_emptyLabel = new QLabel("No results found.", this);
    m_emptyLabel->setAlignment(Qt::AlignCenter);
    m_emptyLabel->setStyleSheet("QLabel { color : gray; font-size: 16px; }");
    m_emptyLabel->hide();

    // Кнопки управління
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    m_btnAdd = new QPushButton("New Record", this);
    m_btnDelete = new QPushButton("Delete Selected", this);
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_btnAdd);
    bottomLayout->addWidget(m_btnDelete);

    connect(m_btnAdd, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(m_btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);

    // Додаємо все на головний Layout
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_tableView);
    mainLayout->addWidget(m_emptyLabel);
    mainLayout->addLayout(bottomLayout);
}

void MainWindow::reloadTable()
{
    QList<PasswordRecord> items = m_repository->loadAll();
    m_tableModel->setItems(items);
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
    // Створюємо порожній шаблонний запис для демонстрації
    PasswordRecord newRecord;
    newRecord.title = "New Title";
    newRecord.login = "user";
    newRecord.category = "Other";

    if (m_repository->insert(newRecord)) {
        reloadTable();
    }
}

void MainWindow::onDeleteClicked()
{
    QModelIndex proxyIndex = m_tableView->currentIndex();
    if (!proxyIndex.isValid()) {
        QMessageBox::warning(this, "Warning", "Please select a record to delete.");
        return;
    }

    // Використання mapToSource для роботи з відфільтрованим списком
    QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);
    int row = sourceIndex.row();

    PasswordRecord record = m_tableModel->itemAt(row);

    if (QMessageBox::question(this, "Confirm", "Delete record: " + record.title + "?") == QMessageBox::Yes) {
        if (m_repository->remove(record.id)) {
            reloadTable();
        }
    }
}
