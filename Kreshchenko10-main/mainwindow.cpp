#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lessonLines =
        {
            "hello world",
            "typing trainer example",
            "qt widgets practice"
        };

    setFocusPolicy(Qt::StrongFocus);

    QSettings settings("TypingTrainer","TypingTrainer");
    speedMode = settings.value("ui/speedMode","CPM").toString();

    timer = new QTimer(this);

    connect(timer,&QTimer::timeout,this,&MainWindow::updateStats);

    startTraining();
    updateText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTraining()
{
    lineIndex = 0;
    charIndex = 0;

    totalTyped = 0;
    correctTyped = 0;

    elapsed.restart();
    timer->start(1000);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString text = event->text();

    if(event->key() == Qt::Key_Backspace)
    {
        if(charIndex > 0)
            charIndex--;

        updateText();
        return;
    }

    if(text.isEmpty())
        return;

    QString currentLine = lessonLines[lineIndex];

    if(charIndex >= currentLine.length())
        return;

    QChar expected = currentLine[charIndex];
    QChar typed = text[0];

    totalTyped++;

    if(typed == expected)
    {
        correctTyped++;
        lastError = false;
    }
    else
    {
        lastError = true;
    }

    charIndex++;

    if(charIndex >= currentLine.length())
    {
        lineIndex++;
        charIndex = 0;

        if(lineIndex >= lessonLines.size())
        {
            timer->stop();
            return;
        }
    }

    updateText();
}

void MainWindow::updateText()
{
    QString prevLine = "";
    QString currentLine = lessonLines[lineIndex];

    if(lineIndex > 0)
        prevLine = lessonLines[lineIndex-1];

    QString pre = currentLine.left(charIndex);
    QString cur = currentLine.mid(charIndex,1);
    QString post = currentLine.mid(charIndex+1);

    QString html;

    html += "<div style='color:gray'>" + prevLine.toHtmlEscaped() + "</div>";

    html += "<span style='background:#cfe8ff;'>"
            + pre.toHtmlEscaped() +
            "</span>";

    if(lastError)
        html += "<span style='background:#ff8080;'>"
                + cur.toHtmlEscaped() +
                "</span>";
    else
        html += "<span style='background:#ffe08a;'>"
                + cur.toHtmlEscaped() +
                "</span>";

    html += post.toHtmlEscaped();

    ui->textLabel->setText(html);
}

void MainWindow::updateStats()
{
    qint64 ms = elapsed.elapsed();
    int seconds = ms / 1000;

    int minutes = seconds / 60;
    int sec = seconds % 60;

    QString timeText =
        QString("%1:%2")
            .arg(minutes,2,10,QChar('0'))
            .arg(sec,2,10,QChar('0'));

    ui->timeLabel->setText(timeText);

    if(seconds > 0)
    {
        double cpm = (totalTyped * 60.0) / seconds;

        double speed = cpm;

        if(speedMode == "WPM")
            speed = cpm / 5.0;

        ui->speedLabel->setText(QString::number(speed,'f',1));
    }

    if(totalTyped > 0)
    {
        double acc = (correctTyped * 100.0) / totalTyped;

        ui->accuracyLabel->setText(
            QString::number(acc,'f',1) + "%"
            );
    }
}
