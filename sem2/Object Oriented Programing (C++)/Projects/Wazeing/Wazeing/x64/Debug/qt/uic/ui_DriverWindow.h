/********************************************************************************
** Form generated from reading UI file 'DriverWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRIVERWINDOW_H
#define UI_DRIVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DriverWindowClass
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *descriptionLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *latitudeLineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *longitudeLineEdit;
    QPushButton *addButton;
    QPushButton *validateButton;
    QLabel *label_4;
    QSlider *distanceSlider;
    QListWidget *reportsListWidget;
    QGridLayout *gridLayout;
    QPushButton *westButton;
    QPushButton *eastButton;
    QPushButton *southButton;
    QPushButton *northButton;

    void setupUi(QWidget *DriverWindowClass)
    {
        if (DriverWindowClass->objectName().isEmpty())
            DriverWindowClass->setObjectName("DriverWindowClass");
        DriverWindowClass->resize(600, 509);
        verticalLayoutWidget = new QWidget(DriverWindowClass);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(100, 30, 361, 393));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        descriptionLineEdit = new QLineEdit(verticalLayoutWidget);
        descriptionLineEdit->setObjectName("descriptionLineEdit");

        horizontalLayout_3->addWidget(descriptionLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        latitudeLineEdit = new QLineEdit(verticalLayoutWidget);
        latitudeLineEdit->setObjectName("latitudeLineEdit");

        horizontalLayout_4->addWidget(latitudeLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        longitudeLineEdit = new QLineEdit(verticalLayoutWidget);
        longitudeLineEdit->setObjectName("longitudeLineEdit");

        horizontalLayout->addWidget(longitudeLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        addButton = new QPushButton(verticalLayoutWidget);
        addButton->setObjectName("addButton");

        verticalLayout->addWidget(addButton);

        validateButton = new QPushButton(verticalLayoutWidget);
        validateButton->setObjectName("validateButton");

        verticalLayout->addWidget(validateButton);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_4);

        distanceSlider = new QSlider(verticalLayoutWidget);
        distanceSlider->setObjectName("distanceSlider");
        distanceSlider->setMaximum(20);
        distanceSlider->setValue(10);
        distanceSlider->setTracking(true);
        distanceSlider->setOrientation(Qt::Orientation::Horizontal);
        distanceSlider->setInvertedAppearance(false);
        distanceSlider->setInvertedControls(false);

        verticalLayout->addWidget(distanceSlider);

        reportsListWidget = new QListWidget(verticalLayoutWidget);
        reportsListWidget->setObjectName("reportsListWidget");

        verticalLayout->addWidget(reportsListWidget);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        westButton = new QPushButton(verticalLayoutWidget);
        westButton->setObjectName("westButton");

        gridLayout->addWidget(westButton, 1, 0, 1, 1);

        eastButton = new QPushButton(verticalLayoutWidget);
        eastButton->setObjectName("eastButton");

        gridLayout->addWidget(eastButton, 2, 0, 1, 1);

        southButton = new QPushButton(verticalLayoutWidget);
        southButton->setObjectName("southButton");

        gridLayout->addWidget(southButton, 3, 0, 1, 1);

        northButton = new QPushButton(verticalLayoutWidget);
        northButton->setObjectName("northButton");

        gridLayout->addWidget(northButton, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(DriverWindowClass);

        QMetaObject::connectSlotsByName(DriverWindowClass);
    } // setupUi

    void retranslateUi(QWidget *DriverWindowClass)
    {
        DriverWindowClass->setWindowTitle(QCoreApplication::translate("DriverWindowClass", "DriverWindow", nullptr));
        label_2->setText(QCoreApplication::translate("DriverWindowClass", "Description:", nullptr));
        label_3->setText(QCoreApplication::translate("DriverWindowClass", "Latitude:", nullptr));
        label->setText(QCoreApplication::translate("DriverWindowClass", "Longitude:", nullptr));
        addButton->setText(QCoreApplication::translate("DriverWindowClass", "Add Report", nullptr));
        validateButton->setText(QCoreApplication::translate("DriverWindowClass", "Validate Report", nullptr));
        label_4->setText(QCoreApplication::translate("DriverWindowClass", "Input Distance Radius:", nullptr));
        westButton->setText(QCoreApplication::translate("DriverWindowClass", "Go West", nullptr));
        eastButton->setText(QCoreApplication::translate("DriverWindowClass", "Go East", nullptr));
        southButton->setText(QCoreApplication::translate("DriverWindowClass", "Go South", nullptr));
        northButton->setText(QCoreApplication::translate("DriverWindowClass", "Go North", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DriverWindowClass: public Ui_DriverWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRIVERWINDOW_H
