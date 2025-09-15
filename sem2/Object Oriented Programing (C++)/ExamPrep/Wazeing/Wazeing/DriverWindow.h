#pragma once

#include <QWidget>
#include "ui_DriverWindow.h"
#include "Observer.h"
#include "Service.h"

class DriverWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	DriverWindow(Service& service, Driver* driver, QWidget *parent = nullptr);
	~DriverWindow();
	void update() override; 
	void populateList();
	void onAddBtnClicked();
	void onSliderValueChanged(int value);
	void onValidateBtnClicked();
	void onNorthBtnClicked();
	void onSouthBtnClicked();
	void onEastBtnClicked();
	void onWestBtnClicked();
	void connectSignalsAndSlots();

private:
	Ui::DriverWindowClass ui;
	Service& service;
	Driver* driver;
	int radius = 10;
};

