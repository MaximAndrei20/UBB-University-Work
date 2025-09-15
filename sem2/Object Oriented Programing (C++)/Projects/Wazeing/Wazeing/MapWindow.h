#pragma once

#include <QWidget>
#include "ui_MapWindow.h"
#include "Observer.h"

class MapWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	MapWindow(QWidget *parent = nullptr);
	~MapWindow();

private:
	Ui::MapWindowClass ui;
};

