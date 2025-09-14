/********************************************************************************
** Form generated from reading UI file 'PopularEventsWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPULAREVENTSWINDOW_H
#define UI_POPULAREVENTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopularEventsWindowClass
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *PopularEventsWindowClass)
    {
        if (PopularEventsWindowClass->objectName().isEmpty())
            PopularEventsWindowClass->setObjectName("PopularEventsWindowClass");
        PopularEventsWindowClass->resize(600, 400);
        listWidget = new QListWidget(PopularEventsWindowClass);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(90, 20, 391, 351));

        retranslateUi(PopularEventsWindowClass);

        QMetaObject::connectSlotsByName(PopularEventsWindowClass);
    } // setupUi

    void retranslateUi(QWidget *PopularEventsWindowClass)
    {
        PopularEventsWindowClass->setWindowTitle(QCoreApplication::translate("PopularEventsWindowClass", "PopularEventsWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PopularEventsWindowClass: public Ui_PopularEventsWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPULAREVENTSWINDOW_H
