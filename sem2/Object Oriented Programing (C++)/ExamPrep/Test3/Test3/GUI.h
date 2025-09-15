#pragma once
#include <qwidget.h>
#include <QListWidget>
#include "Service.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class GUI :
    public QWidget
{
private:
    Service& service;

	QListWidget* weatherList;
	QListWidget* filteredList;
	QLineEdit* precipitationTreshold;
    QLineEdit* description;
    QLineEdit* startTime;
    QLabel* totalHours;

	QPushButton* filterButton;
    QPushButton* showIntervalsAndTotalTime;

public:
    GUI(Service& serv);
	void initGUI();
    void populateList();
    void connectSignalsAndSlots();

    void filterButtonHandler();
	void showIntervalsAndTotalTimeHandler();
};

