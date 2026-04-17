#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>

namespace Ui {
class TicketDialog;
}

class TicketDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode {
        ModeView,
        ModeEdit,
        ModeNew
    };

    explicit TicketDialog(QWidget *parent = nullptr);
    ~TicketDialog();

    void setMode(Mode mode);
    void setTicketData(const QString &id,
                       const QString &title,
                       const QString &description,
                       const QString &status,
                       const QString &priority,
                       const QString &created);

private slots:
    void onEditClicked();
    void onSaveClicked();
    void onCancelClicked();
    void onCloseClicked();

private:
    void applyMode();

private:
    Ui::TicketDialog *ui;
    Mode m_mode;
};
#endif // TICKETDIALOG_H
