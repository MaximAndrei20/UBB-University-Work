/********************************************************************************
** Form generated from reading UI file 'MapWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPWINDOW_H
#define UI_MAPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapWindowClass
{
public:

    void setupUi(QWidget *MapWindowClass)
    {
        if (MapWindowClass->objectName().isEmpty())
            MapWindowClass->setObjectName("MapWindowClass");
        MapWindowClass->resize(600, 400);

        retranslateUi(MapWindowClass);

        QMetaObject::connectSlotsByName(MapWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MapWindowClass)
    {
        MapWindowClass->setWindowTitle(QCoreApplication::translate("MapWindowClass", "MapWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapWindowClass: public Ui_MapWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPWINDOW_H
