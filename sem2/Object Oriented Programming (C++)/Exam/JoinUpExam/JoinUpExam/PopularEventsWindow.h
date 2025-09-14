#pragma once

#include <QWidget>
#include "ui_PopularEventsWindow.h"
#include "Service.h"
#include "Observer.h"

class PopularEventsWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	PopularEventsWindow(Service& service, QWidget *parent = nullptr);
	~PopularEventsWindow();
	void update() override;
	void populateList();

private:
	Ui::PopularEventsWindowClass ui;
	Service& service;
};

