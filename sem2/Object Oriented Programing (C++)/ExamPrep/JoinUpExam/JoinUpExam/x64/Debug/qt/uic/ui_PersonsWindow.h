/********************************************************************************
** Form generated from reading UI file 'PersonsWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONSWINDOW_H
#define UI_PERSONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonsWindowClass
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *locationLabel;
    QCheckBox *nearEventsCheckBox;
    QListWidget *listWidget;

    void setupUi(QWidget *PersonsWindowClass)
    {
        if (PersonsWindowClass->objectName().isEmpty())
            PersonsWindowClass->setObjectName("PersonsWindowClass");
        PersonsWindowClass->resize(600, 400);
        verticalLayoutWidget = new QWidget(PersonsWindowClass);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(30, 20, 531, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        locationLabel = new QLabel(verticalLayoutWidget);
        locationLabel->setObjectName("locationLabel");
        locationLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(locationLabel);

        nearEventsCheckBox = new QCheckBox(verticalLayoutWidget);
        nearEventsCheckBox->setObjectName("nearEventsCheckBox");

        verticalLayout->addWidget(nearEventsCheckBox);

        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);


        retranslateUi(PersonsWindowClass);

        QMetaObject::connectSlotsByName(PersonsWindowClass);
    } // setupUi

    void retranslateUi(QWidget *PersonsWindowClass)
    {
        PersonsWindowClass->setWindowTitle(QCoreApplication::translate("PersonsWindowClass", "PersonsWindow", nullptr));
        locationLabel->setText(QCoreApplication::translate("PersonsWindowClass", "TextLabel", nullptr));
        nearEventsCheckBox->setText(QCoreApplication::translate("PersonsWindowClass", "Show Events Near You", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PersonsWindowClass: public Ui_PersonsWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONSWINDOW_H
