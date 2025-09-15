#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QThw01.h"

class QThw01 : public QMainWindow
{
    Q_OBJECT

public:
    QThw01(QWidget *parent = nullptr);
    ~QThw01();

private:
    Ui::QThw01Class ui;
};
