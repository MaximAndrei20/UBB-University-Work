#pragma once
#include "Service.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <QPushButton>
class GUI :
    public QWidget
{
private:
	Service& service;

	QListWidget* allEquations;
	QLineEdit* aInput;
	QLineEdit* bInput;
	QLineEdit* cInput;

	QPushButton* modifyButton;
	QPushButton* showSolutionButton;
public:
	GUI(Service& service, QWidget* parent = nullptr);
	void initGUI();
	void populateList();
	void connectSignalsAndSlots();

	void modifyButtonHandler();
	void showSolutionButtonHandler();
};

