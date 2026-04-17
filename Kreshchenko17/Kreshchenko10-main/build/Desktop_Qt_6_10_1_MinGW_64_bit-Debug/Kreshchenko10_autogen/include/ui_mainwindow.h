/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *timeLabel;
    QLabel *speedLabel;
    QLabel *accuracyLabel;
    QLabel *textLabel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName("timeLabel");

        hboxLayout->addWidget(timeLabel);

        speedLabel = new QLabel(centralwidget);
        speedLabel->setObjectName("speedLabel");

        hboxLayout->addWidget(speedLabel);

        accuracyLabel = new QLabel(centralwidget);
        accuracyLabel->setObjectName("accuracyLabel");

        hboxLayout->addWidget(accuracyLabel);


        vboxLayout->addLayout(hboxLayout);

        textLabel = new QLabel(centralwidget);
        textLabel->setObjectName("textLabel");
        textLabel->setAlignment(Qt::AlignCenter);
        textLabel->setTextFormat(Qt::RichText);

        vboxLayout->addWidget(textLabel);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TypingTrainer", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        speedLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        accuracyLabel->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        textLabel->setText(QCoreApplication::translate("MainWindow", "Typing Trainer", nullptr));
        textLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
