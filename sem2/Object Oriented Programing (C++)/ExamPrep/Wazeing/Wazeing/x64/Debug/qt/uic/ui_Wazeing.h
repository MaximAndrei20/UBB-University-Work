/********************************************************************************
** Form generated from reading UI file 'Wazeing.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAZEING_H
#define UI_WAZEING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WazeingClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WazeingClass)
    {
        if (WazeingClass->objectName().isEmpty())
            WazeingClass->setObjectName("WazeingClass");
        WazeingClass->resize(600, 400);
        menuBar = new QMenuBar(WazeingClass);
        menuBar->setObjectName("menuBar");
        WazeingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WazeingClass);
        mainToolBar->setObjectName("mainToolBar");
        WazeingClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(WazeingClass);
        centralWidget->setObjectName("centralWidget");
        WazeingClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(WazeingClass);
        statusBar->setObjectName("statusBar");
        WazeingClass->setStatusBar(statusBar);

        retranslateUi(WazeingClass);

        QMetaObject::connectSlotsByName(WazeingClass);
    } // setupUi

    void retranslateUi(QMainWindow *WazeingClass)
    {
        WazeingClass->setWindowTitle(QCoreApplication::translate("WazeingClass", "Wazeing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WazeingClass: public Ui_WazeingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAZEING_H
