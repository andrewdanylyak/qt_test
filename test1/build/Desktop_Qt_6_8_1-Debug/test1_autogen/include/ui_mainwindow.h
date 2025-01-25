/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *mOpenButton;
    QTextEdit *mMsgBox;
    QPushButton *mCloseButton;
    QPushButton *mWriteButton;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mOpenButton = new QPushButton(centralwidget);
        mOpenButton->setObjectName("mOpenButton");
        mOpenButton->setGeometry(QRect(20, 510, 231, 25));
        mMsgBox = new QTextEdit(centralwidget);
        mMsgBox->setObjectName("mMsgBox");
        mMsgBox->setGeometry(QRect(13, 309, 771, 181));
        mMsgBox->setReadOnly(true);
        mCloseButton = new QPushButton(centralwidget);
        mCloseButton->setObjectName("mCloseButton");
        mCloseButton->setGeometry(QRect(260, 510, 89, 25));
        mWriteButton = new QPushButton(centralwidget);
        mWriteButton->setObjectName("mWriteButton");
        mWriteButton->setGeometry(QRect(360, 510, 89, 25));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 270, 731, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        mOpenButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        mCloseButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        mWriteButton->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
