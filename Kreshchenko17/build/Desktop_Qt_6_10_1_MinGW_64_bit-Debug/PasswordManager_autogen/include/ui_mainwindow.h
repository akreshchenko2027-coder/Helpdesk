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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
<<<<<<< HEAD
#include <QtWidgets/QMainWindow>
=======
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
>>>>>>> 4b716b0887b5d060678cd516c62b27e26a2a9d69
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
<<<<<<< HEAD
    QAction *actionDelete;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;
=======
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionSave;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditSearch;
    QTableView *tableViewPasswords;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *toolBar;
    QStatusBar *statusbar;
>>>>>>> 4b716b0887b5d060678cd516c62b27e26a2a9d69

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
<<<<<<< HEAD
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
=======
        MainWindow->resize(900, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName("actionEdit");
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
>>>>>>> 4b716b0887b5d060678cd516c62b27e26a2a9d69
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
<<<<<<< HEAD
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);

        verticalLayout->addWidget(tableView);
=======
        lineEditSearch = new QLineEdit(centralwidget);
        lineEditSearch->setObjectName("lineEditSearch");

        verticalLayout->addWidget(lineEditSearch);

        tableViewPasswords = new QTableView(centralwidget);
        tableViewPasswords->setObjectName("tableViewPasswords");

        verticalLayout->addWidget(tableViewPasswords);
>>>>>>> 4b716b0887b5d060678cd516c62b27e26a2a9d69

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
<<<<<<< HEAD
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addAction(actionNew);
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionExit);
=======
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(toolBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionEdit);
        menuEdit->addAction(actionDelete);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionEdit);
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionSave);
>>>>>>> 4b716b0887b5d060678cd516c62b27e26a2a9d69

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PasswordManager", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
<<<<<<< HEAD
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
=======
        actionEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\210\321\203\320\272...", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
>>>>>>> 4b716b0887b5d060678cd516c62b27e26a2a9d69
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
