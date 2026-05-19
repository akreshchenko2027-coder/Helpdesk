#include "requestdialog.h"
#include "ui_requestdialog.h"

RequestDialog::RequestDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::RequestDialog)
{
    ui->setupUi(this);

    connect(ui->editSubject, &QLineEdit::textChanged,
            this, &RequestDialog::onFormChanged);

    connect(ui->editDetails, &QTextEdit::textChanged,
            this, &RequestDialog::onFormChanged);

    connect(ui->comboState, &QComboBox::currentTextChanged,
            this, &RequestDialog::onFormChanged);

    connect(ui->comboLevel, &QComboBox::currentTextChanged,
            this, &RequestDialog::onFormChanged);

    connect(ui->btnSave, &QPushButton::clicked,
            this, &RequestDialog::onSaveClicked);

    updateUiForMode();
}

RequestDialog::~RequestDialog()
{
    delete ui;
}

void RequestDialog::setMode(Mode mode)
{
    m_mode = mode;
    updateUiForMode();
}

RequestDialog::Mode RequestDialog::mode() const
{
    return m_mode;
}

void RequestDialog::loadRequest(const Request &request)
{
    ui->editSubject->setText(request.subject);
    ui->editDetails->setPlainText(request.details);
    ui->comboState->setCurrentText(request.state);
    ui->comboLevel->setCurrentText(request.level);
}

Request RequestDialog::collectRequest() const
{
    Request r;

    r.subject = ui->editSubject->text().trimmed();
    r.details = ui->editDetails->toPlainText().trimmed();
    r.state = ui->comboState->currentText();
    r.level = ui->comboLevel->currentText();
    r.createdAt = QDateTime::currentDateTime();

    return r;
}

bool RequestDialog::isSubjectValid() const
{
    return !ui->editSubject->text().trimmed().isEmpty();
}

bool RequestDialog::isFormValid() const
{
    return isSubjectValid();
}

void RequestDialog::onFormChanged()
{
    updateValidationUi();
    updateButtonsState();
}

void RequestDialog::updateValidationUi()
{
    if(isSubjectValid())
        ui->labelError->clear();
    else
        ui->labelError->setText("Subject required");
}

void RequestDialog::updateButtonsState()
{
    bool editable = (m_mode == Mode::Edit || m_mode == Mode::Create);

    ui->btnSave->setEnabled(editable && isFormValid());
}

void RequestDialog::updateUiForMode()
{
    bool editable = (m_mode == Mode::Edit || m_mode == Mode::Create);

    ui->editSubject->setReadOnly(!editable);
    ui->editDetails->setReadOnly(!editable);

    ui->comboState->setEnabled(editable);
    ui->comboLevel->setEnabled(editable);

    updateButtonsState();
}

void RequestDialog::onSaveClicked()
{
    if(!isFormValid())
        return;

    Request r = collectRequest();

    if(m_mode == Mode::Create)
        emit createRequested(r);
    else if(m_mode == Mode::Edit)
        emit updateRequested(r);
}
