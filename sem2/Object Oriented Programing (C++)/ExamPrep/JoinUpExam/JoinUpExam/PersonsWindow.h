#pragma once

#include <QWidget>
#include "ui_PersonsWindow.h"
#include "Observer.h"
#include "Service.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class PersonsWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	PersonsWindow(Service& serv, Person* person, QWidget *parent = nullptr);
	~PersonsWindow();
	void update() override;
	void populateList();
	void onCheckBoxStateChanged(int state) {
		populateList();
	}
	void onAddButtonClicked();
	void onEventSelected();
	void onGoingButtonClicked();
	void onOrganizerEventSelected();
	void onChangeDescriptionButtonClicked();

	QLineEdit* eventNameEdit;
	QLineEdit* eventDescriptionEdit;
	QLineEdit* eventLatitudeEdit;
	QLineEdit* eventLongitudeEdit;
	QLineEdit* eventDateEdit;
	QPushButton* addEventButton;
	QPushButton* goingButton;
	QLabel* eventDescriptionLabel;
	QLabel* eventParticipantsLabel;
	QLabel* eventDescriptionOrganizersLabel;
	QLineEdit* changeDescription;
	QLineEdit* changeDate;
	QPushButton* changeDescriptionButton;

private:
	Ui::PersonsWindowClass ui;
	Service& service;
	Person* person;
};

