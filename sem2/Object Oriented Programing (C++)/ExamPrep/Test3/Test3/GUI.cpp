#include "GUI.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <utility>
#include <QVBoxLayout>
GUI::GUI(Service& serv) : service(serv)
{
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
}

void GUI::initGUI()
{


	QHBoxLayout* mainWindow = new QHBoxLayout(this);

	weatherList = new QListWidget();
	filteredList = new QListWidget();
	totalHours = new QLabel("Total Hours: 0");

	precipitationTreshold = new QLineEdit();
	QVBoxLayout* otherLayout = new QVBoxLayout();
	filterButton = new QPushButton("Filter");
	description = new QLineEdit();
	startTime = new QLineEdit();
	showIntervalsAndTotalTime = new QPushButton("Show Intervals and Total Time");

	precipitationTreshold->setPlaceholderText("Enter precipitation threshold");
	description->setPlaceholderText("Enter description");
	startTime->setPlaceholderText("Enter start time (0-23)");

	otherLayout->addWidget(precipitationTreshold);
	otherLayout->addWidget(filterButton);
	otherLayout->addWidget(description);
	otherLayout->addWidget(startTime);
	otherLayout->addWidget(showIntervalsAndTotalTime);

	mainWindow->addWidget(weatherList);
	mainWindow->addLayout(otherLayout);
	mainWindow->addWidget(filteredList);
	mainWindow->addWidget(totalHours);
}

void GUI::populateList()
{
	if (weatherList->count() > 0) {
		weatherList->clear();
	}
	std::vector<Weather> weathers = this->service.getAllWeathers();
	//sort the intervals in ascending order
	for (size_t i = 0; i < weathers.size() - 1; ++i) {
		for (size_t j = i + 1; j < weathers.size(); ++j) {
			if (weathers[i].getStart() > weathers[j].getStart()) {
				std::swap(weathers[i], weathers[j]);
			}
		}
	}

	for (const auto& weather : weathers) {
		QString itemText = QString::number(weather.getStart()) + " - " +
			QString::number(weather.getEnd()) + ": " +
			QString::number(weather.getTemperature()) + " C, " +
			QString::number(weather.getPrecipitation()) + "%, " +
			QString::fromStdString(weather.getDescription());
		weatherList->addItem(itemText);
	}
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(filterButton, &QPushButton::clicked, this, &GUI::filterButtonHandler);
	QObject::connect(showIntervalsAndTotalTime, &QPushButton::clicked, this, &GUI::showIntervalsAndTotalTimeHandler);
}

void GUI::filterButtonHandler()
{
	bool ok;
	int treshold = precipitationTreshold->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Invalid Input", "Please enter a valid number for precipitation threshold.");
		return;
	}
	// Clear the list before populating it with filtered results
	if (weatherList->count() > 0) {
		weatherList->clear();
	}
	std::vector<Weather> weathers = this->service.getAllWeathers();
	for (const auto& weather : weathers) {
		if (weather.getPrecipitation() < treshold) {
			QString itemText = QString::number(weather.getStart()) + " - " +
				QString::number(weather.getEnd()) + ": " +
				QString::number(weather.getTemperature()) + " C, " +
				QString::number(weather.getPrecipitation()) + "%, " +
				QString::fromStdString(weather.getDescription());
			weatherList->addItem(itemText);
		}
	}
	
	
}

void GUI::showIntervalsAndTotalTimeHandler()
{
	// get the description and start time
	bool ok;
	std::string desc = description->text().toStdString();
	int start = startTime->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Invalid Input", "Please enter a valid number for start time (0-23).");
		return;
	}
	if (desc.empty() || start < 0 || start > 23) {
		QMessageBox::warning(this, "Invalid Input", "Please enter a valid description and start time (0-23).");
		return;
	}
	int totalT = 0;
	std::vector<std::pair<int,int> > intervals;
	std::vector<Weather> weathers = this->service.getAllWeathers();
	for (const auto& weather : weathers) {
		int s = weather.getStart();
		int e = weather.getEnd();
		if (weather.getDescription() == desc && e > start) {
			
			if (s < start) {
				s = start; // Adjust start time if it is before the specified start
			}
			if (s < e) { // Only add valid intervals
				totalT += e - s;
				intervals.push_back(std::make_pair(s, e));
			}
		}
	}
	if (intervals.empty()) {
		QMessageBox::information(this, "No Intervals", "No intervals found for the specified description and start time.");
		return;
	}
	// add the intervals to filteredWeathers
	// and the time to totalHours
	filteredList->clear();
	for (const auto& interval : intervals) {
		QString itemText = QString::number(interval.first) + " - " + QString::number(interval.second);
		filteredList->addItem(itemText);
	}
	totalHours->setText("Total Hours: " + QString::number(totalT));
}
