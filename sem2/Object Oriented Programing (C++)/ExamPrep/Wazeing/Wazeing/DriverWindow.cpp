#include "DriverWindow.h"
#include <QMessageBox>

DriverWindow::DriverWindow(Service& service, Driver* driver, QWidget *parent)
	: QWidget(parent), service(service), driver(driver)
{
	ui.setupUi(this);
	setWindowTitle(QString::fromStdString(driver->getName()));
	setStyleSheet("color: black;");
	if (driver->getStatus() == "baby") {
		setStyleSheet("background-color: lightblue;");
	}
	else if (driver->getStatus() == "grown-up") {
		setStyleSheet("background-color: lightgreen;");
	}
	else if (driver->getStatus() == "knight") {
		setStyleSheet("background-color: lightgoldenrodyellow;");
	}
	update();
	connectSignalsAndSlots();
}

DriverWindow::~DriverWindow()
{}

void DriverWindow::update() {
	populateList();
	if (driver->getStatus() == "baby") {
		setStyleSheet("background-color: lightblue;");
	}
	else if (driver->getStatus() == "grown-up") {
		setStyleSheet("background-color: lightgreen;");
	}
	else if (driver->getStatus() == "knight") {
		setStyleSheet("background-color: lightgoldenrodyellow;");
	}
}

void DriverWindow::populateList()
{
	std::vector<Report> reports = service.getReportsNearDriver(*driver, radius);
	//set color black
	ui.reportsListWidget->setStyleSheet("color: black;");
	ui.reportsListWidget->clear();
	for (const auto& report : reports) {
		QString itemText = QString::fromStdString(report.getDescription()) + " - " +
			QString::fromStdString(report.getReporter()) + " (" +
			QString::number(report.getLocation().first) + ", " +
			QString::number(report.getLocation().second) + ")" +
			QString::fromStdString(report.isValidated() ? " [Validated]" : " [Not Validated]");
		ui.reportsListWidget->addItem(itemText);
	}

}

void DriverWindow::onAddBtnClicked()
{
	QString description = ui.descriptionLineEdit->text();
	QString reporter = QString::fromStdString(driver->getName());
	QString latitudeStr = ui.latitudeLineEdit->text();
	QString longitudeStr = ui.longitudeLineEdit->text();
	double latitude = latitudeStr.toDouble();
	double longitude = longitudeStr.toDouble();

	bool validated = false;
	// description empty or latitude/longitude too far (more than 20 units away from driver)
	if (description.isEmpty()){
		QMessageBox::warning(this, "Invalid Report", "Please provide a valid description and location.");
		return;
	}
	double distance = std::sqrt(std::pow(latitude - driver->getLocation().first, 2) +
		std::pow(longitude - driver->getLocation().second, 2));
	if (distance > 20.0) {
		QMessageBox::warning(this, "Invalid Location", "The report location is too far from your current location.");
		return;
	}
	Report newReport(description.toStdString(), reporter.toStdString(), std::make_pair(latitude, longitude), validated);
	service.getReports().push_back(newReport);
	service.notifyObservers();
	populateList();
}

void DriverWindow::onSliderValueChanged(int value)
{
	radius = value;
	update();
}

void DriverWindow::onValidateBtnClicked()
{
	if (ui.reportsListWidget->currentItem() == nullptr) {
		QMessageBox::warning(this, "No Report Selected", "Please select a report to validate.");
		return;
	}
	QString selectedText = ui.reportsListWidget->currentItem()->text();
	QStringList parts = selectedText.split(" - ");
	if (parts.size() < 2) {
		QMessageBox::warning(this, "Invalid Report", "The selected report is not valid.");
		return;
	}
	bool validated = parts[1].endsWith("[Validated]");
	if (validated) {
		QMessageBox::information(this, "Validation", "The selected report has already been validated.");
		return;
	}

	QString reporter = parts[1].split(" (")[0];
	if (reporter == driver->getName().c_str()) {
		QMessageBox::warning(this, "Validation Error", "You cannot validate your own report.");
		return;
	}

	// Find the report in the service
	Report* reportToValidate = nullptr;
	for (auto& report : service.getReports()) {
		if (report.getDescription() == parts[0].toStdString() &&
			report.getReporter() == reporter.toStdString()) {
			reportToValidate = &report;
			break;
		}
	}

	if (reportToValidate && !reportToValidate->isValidated()) {
		service.validateReport(*reportToValidate, *driver);
		service.notifyObservers();
		QMessageBox::information(this, "Validation", "The report has been validated successfully.");
		return;
	}
	
	QMessageBox::information(this, "Validation", "The selected report has already been validated or does not exist.");
}

void DriverWindow::onNorthBtnClicked()
{
	// Move the driver north by 1 unit (latitude)
	auto location = driver->getLocation();
	location.first += 1.0;
	driver->setLocation(location);
	service.notifyObservers();
}

void DriverWindow::onSouthBtnClicked()
{
	// Move the driver south by 1 unit (latitude)
	auto location = driver->getLocation();
	location.first -= 1.0;
	driver->setLocation(location);
	service.notifyObservers();
}

void DriverWindow::onEastBtnClicked() {
	// Move the driver east by 1 unit (longitude)
	auto location = driver->getLocation();
	location.second += 1.0;
	driver->setLocation(location);
	service.notifyObservers();
}

void DriverWindow::onWestBtnClicked() {
	// Move the driver west by 1 unit (longitude)
	auto location = driver->getLocation();
	location.second -= 1.0;
	driver->setLocation(location);
	service.notifyObservers();
}

void DriverWindow::connectSignalsAndSlots()
{
	connect(ui.addButton, &QPushButton::clicked, this, &DriverWindow::onAddBtnClicked);
	connect(ui.distanceSlider, &QSlider::valueChanged, this, &DriverWindow::onSliderValueChanged);
	connect(ui.validateButton, &QPushButton::clicked, this, &DriverWindow::onValidateBtnClicked);

	connect(ui.northButton, &QPushButton::clicked, this, &DriverWindow::onNorthBtnClicked);
	connect(ui.southButton, &QPushButton::clicked, this, &DriverWindow::onSouthBtnClicked);
	connect(ui.eastButton, &QPushButton::clicked, this, &DriverWindow::onEastBtnClicked);
	connect(ui.westButton, &QPushButton::clicked, this, &DriverWindow::onWestBtnClicked);
}

