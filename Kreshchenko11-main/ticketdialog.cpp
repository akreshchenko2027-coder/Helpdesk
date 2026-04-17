#include "ticketdialog.h"
#include "ui_ticketdialog.h"

#include <QMessageBox>

TicketDialog::TicketDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketDialog)
    , m_mode(ModeView)
{
    ui->setupUi(this);

    setWindowTitle("Ticket");
    resize(500, 400);

    connect(ui->btnEdit, &QPushButton::clicked, this, &TicketDialog::onEditClicked);
    connect(ui->btnSave, &QPushButton::clicked, this, &TicketDialog::onSaveClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &TicketDialog::onCancelClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &TicketDialog::onCloseClicked);

    ui->comboStatus->addItems({"New", "Open", "In Progress", "Resolved", "Closed"});
    ui->comboPriority->addItems({"Low", "Medium", "High", "Critical"});

    applyMode();
}

TicketDialog::~TicketDialog()
{
    delete ui;
}

void TicketDialog::setTicketData(const QString &id,
                                 const QString &title,
                                 const QString &description,
                                 const QString &status,
                                 const QString &priority,
                                 const QString &created)
{
    ui->editTicketId->setText(id);
    ui->editTitle->setText(title);
    ui->textDescription->setPlainText(description);
    ui->comboStatus->setCurrentText(status);
    ui->comboPriority->setCurrentText(priority);
    ui->editCreated->setText(created);
}

void TicketDialog::setMode(Mode mode)
{
    m_mode = mode;
    applyMode();
}

void TicketDialog::applyMode()
{
    bool editable = (m_mode == ModeEdit || m_mode == ModeNew);

    ui->editTitle->setReadOnly(!editable);
    ui->textDescription->setReadOnly(!editable);
    ui->comboStatus->setEnabled(editable);
    ui->comboPriority->setEnabled(editable);

    ui->editTicketId->setReadOnly(true);
    ui->editCreated->setReadOnly(true);

    bool isView = (m_mode == ModeView);
    bool isEditOrNew = (m_mode == ModeEdit || m_mode == ModeNew);

    ui->btnEdit->setVisible(isView);
    ui->btnClose->setVisible(isView);

    ui->btnSave->setVisible(isEditOrNew);
    ui->btnCancel->setVisible(isEditOrNew);

    if (m_mode == ModeView) {
        setWindowTitle("View Ticket");
    } else if (m_mode == ModeEdit) {
        setWindowTitle("Edit Ticket");
    } else {
        setWindowTitle("New Ticket");
        if (ui->editTicketId->text().isEmpty())
            ui->editTicketId->setText("Auto");
        if (ui->editCreated->text().isEmpty())
            ui->editCreated->setText("Auto");
    }
}

void TicketDialog::onEditClicked()
{
    setMode(ModeEdit);
}

void TicketDialog::onSaveClicked()
{
    QMessageBox::information(this, "Save", "Ticket saved (demo).");

    if (m_mode == ModeNew) {
        close();
    } else {
        setMode(ModeView);
    }
}

void TicketDialog::onCancelClicked()
{
    if (m_mode == ModeNew) {
        close();
    } else {
        setMode(ModeView);
    }
}

void TicketDialog::onCloseClicked()
{
    close();
}
