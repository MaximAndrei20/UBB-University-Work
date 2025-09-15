#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mochtest32.h"

class mochtest32 : public QMainWindow
{
    Q_OBJECT

public:
    mochtest32(QWidget *parent = nullptr);
    ~mochtest32();

private:
    Ui::mochtest32Class ui;
};

