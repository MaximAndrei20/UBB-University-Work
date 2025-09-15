/********************************************************************************
** Form generated from reading UI file 'Test3.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST3_H
#define UI_TEST3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test3Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Test3Class)
    {
        if (Test3Class->objectName().isEmpty())
            Test3Class->setObjectName("Test3Class");
        Test3Class->resize(600, 400);
        menuBar = new QMenuBar(Test3Class);
        menuBar->setObjectName("menuBar");
        Test3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Test3Class);
        mainToolBar->setObjectName("mainToolBar");
        Test3Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Test3Class);
        centralWidget->setObjectName("centralWidget");
        Test3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Test3Class);
        statusBar->setObjectName("statusBar");
        Test3Class->setStatusBar(statusBar);

        retranslateUi(Test3Class);

        QMetaObject::connectSlotsByName(Test3Class);
    } // setupUi

    void retranslateUi(QMainWindow *Test3Class)
    {
        Test3Class->setWindowTitle(QCoreApplication::translate("Test3Class", "Test3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Test3Class: public Ui_Test3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST3_H
