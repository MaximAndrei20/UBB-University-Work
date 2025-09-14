/********************************************************************************
** Form generated from reading UI file 'QThw01.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTHW01_H
#define UI_QTHW01_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QThw01Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QThw01Class)
    {
        if (QThw01Class->objectName().isEmpty())
            QThw01Class->setObjectName("QThw01Class");
        QThw01Class->resize(600, 400);
        menuBar = new QMenuBar(QThw01Class);
        menuBar->setObjectName("menuBar");
        QThw01Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QThw01Class);
        mainToolBar->setObjectName("mainToolBar");
        QThw01Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QThw01Class);
        centralWidget->setObjectName("centralWidget");
        QThw01Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QThw01Class);
        statusBar->setObjectName("statusBar");
        QThw01Class->setStatusBar(statusBar);

        retranslateUi(QThw01Class);

        QMetaObject::connectSlotsByName(QThw01Class);
    } // setupUi

    void retranslateUi(QMainWindow *QThw01Class)
    {
        QThw01Class->setWindowTitle(QCoreApplication::translate("QThw01Class", "QThw01", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QThw01Class: public Ui_QThw01Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHW01_H
