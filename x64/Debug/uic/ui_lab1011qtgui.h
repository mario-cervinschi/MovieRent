/********************************************************************************
** Form generated from reading UI file 'lab1011qtgui.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB1011QTGUI_H
#define UI_LAB1011QTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab1011qtguiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab1011qtguiClass)
    {
        if (lab1011qtguiClass->objectName().isEmpty())
            lab1011qtguiClass->setObjectName("lab1011qtguiClass");
        lab1011qtguiClass->resize(600, 400);
        menuBar = new QMenuBar(lab1011qtguiClass);
        menuBar->setObjectName("menuBar");
        lab1011qtguiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab1011qtguiClass);
        mainToolBar->setObjectName("mainToolBar");
        lab1011qtguiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab1011qtguiClass);
        centralWidget->setObjectName("centralWidget");
        lab1011qtguiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab1011qtguiClass);
        statusBar->setObjectName("statusBar");
        lab1011qtguiClass->setStatusBar(statusBar);

        retranslateUi(lab1011qtguiClass);

        QMetaObject::connectSlotsByName(lab1011qtguiClass);
    } // setupUi

    void retranslateUi(QMainWindow *lab1011qtguiClass)
    {
        lab1011qtguiClass->setWindowTitle(QCoreApplication::translate("lab1011qtguiClass", "lab1011qtgui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab1011qtguiClass: public Ui_lab1011qtguiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB1011QTGUI_H
