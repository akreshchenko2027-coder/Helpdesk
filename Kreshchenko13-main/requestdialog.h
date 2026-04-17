#pragma once

#include <QDialog>
#include "request.h"

namespace Ui {
class RequestDialog;
}

class RequestDialog : public QDialog
{
    Q_OBJECT

public:
    enum class Mode
    {
        View,
        Edit,
        Create
    };

    explicit RequestDialog(QWidget *parent = nullptr);
    ~RequestDialog();

    void setMode(Mode mode);
    Mode mode() const;

    void loadRequest(const Request &request);
    Request collectRequest() const;

signals:
    void createRequested(const Request &request);
    void updateRequested(const Request &request);

private slots:
    void onFormChanged();
    void onSaveClicked();

private:
    bool isSubjectValid() const;
    bool isFormValid() const;

    void updateUiForMode();
    void updateValidationUi();
    void updateButtonsState();

    Ui::RequestDialog *ui;
    Mode m_mode = Mode::Create;
};
