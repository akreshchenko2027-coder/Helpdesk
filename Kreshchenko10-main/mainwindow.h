#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;

    QStringList lessonLines;
    int lineIndex = 0;
    int charIndex = 0;

    bool lastError = false;

    int totalTyped = 0;
    int correctTyped = 0;

    QTimer *timer;
    QElapsedTimer elapsed;

    QString speedMode;

    void updateText();
    void updateStats();
    void startTraining();
};

#endif
