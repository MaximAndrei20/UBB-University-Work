/********************************************************************************
** Form generated from reading UI file 'mochtest32.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOCHTEST32_H
#define UI_MOCHTEST32_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mochtest32Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mochtest32Class)
    {
        if (mochtest32Class->objectName().isEmpty())
            mochtest32Class->setObjectName("mochtest32Class");
        mochtest32Class->resize(600, 400);
        menuBar = new QMenuBar(mochtest32Class);
        menuBar->setObjectName("menuBar");
        mochtest32Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mochtest32Class);
        mainToolBar->setObjectName("mainToolBar");
        mochtest32Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(mochtest32Class);
        centralWidget->setObjectName("centralWidget");
        mochtest32Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(mochtest32Class);
        statusBar->setObjectName("statusBar");
        mochtest32Class->setStatusBar(statusBar);

        retranslateUi(mochtest32Class);

        QMetaObject::connectSlotsByName(mochtest32Class);
    } // setupUi

    void retranslateUi(QMainWindow *mochtest32Class)
    {
        mochtest32Class->setWindowTitle(QCoreApplication::translate("mochtest32Class", "mochtest32", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mochtest32Class: public Ui_mochtest32Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOCHTEST32_H
