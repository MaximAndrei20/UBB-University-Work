#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTDesignerTest.h"

class QTDesignerTest : public QMainWindow
{
    Q_OBJECT

public:
    QTDesignerTest(QWidget *parent = nullptr);
    ~QTDesignerTest();

private:
    Ui::QTDesignerTestClass ui;
};

