/********************************************************************************
** Form generated from reading UI file 'QTDesignerTest.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDESIGNERTEST_H
#define UI_QTDESIGNERTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTDesignerTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTDesignerTestClass)
    {
        if (QTDesignerTestClass->objectName().isEmpty())
            QTDesignerTestClass->setObjectName("QTDesignerTestClass");
        QTDesignerTestClass->resize(600, 400);
        menuBar = new QMenuBar(QTDesignerTestClass);
        menuBar->setObjectName("menuBar");
        QTDesignerTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTDesignerTestClass);
        mainToolBar->setObjectName("mainToolBar");
        QTDesignerTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTDesignerTestClass);
        centralWidget->setObjectName("centralWidget");
        QTDesignerTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTDesignerTestClass);
        statusBar->setObjectName("statusBar");
        QTDesignerTestClass->setStatusBar(statusBar);

        retranslateUi(QTDesignerTestClass);

        QMetaObject::connectSlotsByName(QTDesignerTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTDesignerTestClass)
    {
        QTDesignerTestClass->setWindowTitle(QCoreApplication::translate("QTDesignerTestClass", "QTDesignerTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTDesignerTestClass: public Ui_QTDesignerTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDESIGNERTEST_H
