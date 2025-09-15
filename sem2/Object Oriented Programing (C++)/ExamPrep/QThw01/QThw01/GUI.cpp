#include "GUI.h"
#include "Service.h"
#include "CSVFileRepo.h"
#include "HTMLRepo.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <qgridlayout.h>
#include <vector>
#include <stdexcept>
#include <QMessageBox>
#include <QCloseEvent>
#include <QInputDialog>
#include <QShortcut>

using namespace std;

void GUI::closeEvent(QCloseEvent* event)
{
	try {
		serv.writetofile(); // Save data using your service
	}
	catch (const std::exception& ex) {
		QMessageBox::warning(this, "Error", QString::fromStdString(ex.what()));
	}
	event->accept(); // Accept the close event
}

GUI::GUI(Service& serv) : serv{ serv }
{
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
}

void GUI::initGUI()
{
	QVBoxLayout* adminLayout = new QVBoxLayout{};
	QLabel* allEventsLable = new QLabel("All events");
	adminLayout->addWidget(allEventsLable);

	QHBoxLayout* mainWindow = new QHBoxLayout{ this };

	mainWindow->addLayout(adminLayout);

	allEventsTable = new QTableView{};
	adminLayout->addWidget(allEventsTable);

	QFormLayout* eventDetails = new QFormLayout{};
	lineTitle = new QLineEdit{};
	lineDescription = new QLineEdit{};
	lineDateTime = new QLineEdit{};
	lineNumberOfPeople = new QLineEdit{};
	lineLink = new QLineEdit{};

	eventDetails->addRow("Title", lineTitle);
	eventDetails->addRow("Description", lineDescription);
	eventDetails->addRow("DateTime", lineDateTime);
	eventDetails->addRow("Number of people", lineNumberOfPeople);
	eventDetails->addRow("Link", lineLink);

	adminLayout->addLayout(eventDetails);

	QGridLayout* adminButtonsLayout = new QGridLayout{};

	addButton = new QPushButton{ "Add" };
	deleteButton = new QPushButton{ "Remove" };
	filterButton = new QPushButton{ "Filter" };
	updateButton = new QPushButton{ "Update" };
	undoButton = new QPushButton{ "Undo" };
	redoButton = new QPushButton{ "Redo" };

	adminButtonsLayout->addWidget(addButton, 0, 0);
	adminButtonsLayout->addWidget(deleteButton, 0, 1);
	adminButtonsLayout->addWidget(updateButton, 0, 2);
	adminButtonsLayout->addWidget(filterButton, 1, 1);
	adminButtonsLayout->addWidget(undoButton, 1, 2);
	adminButtonsLayout->addWidget(redoButton, 2, 2);

	adminLayout->addLayout(adminButtonsLayout);

	copyButton = new QPushButton(">");

	mainWindow->addWidget(copyButton);

	QVBoxLayout* userLayout = new QVBoxLayout{};

	QLabel* userEventsLable = new QLabel("Your Events");

	userLayout->addWidget(userEventsLable);

	mainWindow->addLayout(userLayout);


	userEvents = new QListWidget{};
	userLayout->addWidget(userEvents);

	removeFromUserButton = new QPushButton{ "Remove" };
	showButton = new QPushButton{ "Show Website" };
	showCsvButton = new QPushButton{ "Show CSV" };
	showHtmlButton = new QPushButton{ "Show HTML" };

	QHBoxLayout* userButtons = new QHBoxLayout{};

	userButtons->addWidget(removeFromUserButton);
	userButtons->addWidget(showButton);
	userButtons->addWidget(showCsvButton);
	userButtons->addWidget(showHtmlButton);

	userLayout->addLayout(userButtons);
}

void GUI::populateList()
{
	if (allEventsModel)
		delete allEventsModel;
	allEventsModel = new EventTableModel(this->serv.getEvents(), this);
	allEventsTable->setModel(allEventsModel);
	allEventsTable->resizeColumnsToContents();
}

void GUI::populateUserList()
{
	if (userEvents->count() > 0)
		userEvents->clear();
	vector<Event> events = this->serv.getUserEvents();
	for (const Event& e : events) {
		userEvents->addItem(QString::fromStdString(e.getTitle() + " | " + e.getDescription()));
	}
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);
	QObject::connect(this->copyButton, &QPushButton::clicked, this, &GUI::copyButtonHandler);
	QObject::connect(this->showButton, &QPushButton::clicked, this, &GUI::addShowButtonHandler);
	QObject::connect(this->showCsvButton, &QPushButton::clicked, this, &GUI::showCsvButtonHandler);
	QObject::connect(this->showHtmlButton, &QPushButton::clicked, this, &GUI::showHtmlButtonHandler);
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &GUI::filterButtonHandler);
	QObject::connect(this->removeFromUserButton, &QPushButton::clicked, this, &GUI::removeFromUserButtonHandler);
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::undoButtonHandler);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::redoButtonHandler);

	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &GUI::undoButtonHandler);

	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &GUI::redoButtonHandler);

	QObject::connect(this, &GUI::undoTriggered, this, &GUI::onUndo);
	QObject::connect(this, &GUI::redoTriggered, this, &GUI::onRedo);
}

void GUI::addButtonHandler()
{
	QString title = lineTitle->text();
	QString description = lineDescription->text();
	QString dateTime = lineDateTime->text();
	QString numberOfPeople = lineNumberOfPeople->text();
	QString link = lineLink->text();

	if (numberOfPeople.toInt() < 0) {
		QMessageBox::warning(this, "Warning", "Number of people must be a positive number!");
		return;
	}

	try {
		this->serv.addEvent(title.toStdString(), description.toStdString(), dateTime.toStdString(), numberOfPeople.toInt(), link.toStdString());
		this->populateList();
	}
	catch (const std::exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::deleteButtonHandler()
{
	// Get the selected item
	QModelIndexList selectedRows = allEventsTable->selectionModel()->selectedRows();
	if (selectedRows.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No event selected!");
		return;
	}
	int row = selectedRows.first().row();
	const Event& event = allEventsModel->getEventAt(row); // You need to add this method to your model
	QString title = QString::fromStdString(event.getTitle());

	try {
		this->serv.deleteEvent(title.toStdString());
		this->populateList();
	}
	catch (const std::exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::updateButtonHandler()
{
	// Get the selected item
	QModelIndexList selectedRows = allEventsTable->selectionModel()->selectedRows();
	if (selectedRows.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No event selected!");
		return;
	}
	int row = selectedRows.first().row();
	const Event& event = allEventsModel->getEventAt(row); // You need to add this method to your model
	QString oldTitle = QString::fromStdString(event.getTitle());

	// Get new values from the input fields
	QString title = lineTitle->text();
	QString description = lineDescription->text();
	QString dateTime = lineDateTime->text();
	QString numberOfPeople = lineNumberOfPeople->text();
	QString link = lineLink->text();

	if (numberOfPeople.toInt() < 0) {
		QMessageBox::warning(this, "Warning", "Number of people must be a positive number!");
		return;
	}

	try {
		this->serv.updateEvent(
			oldTitle.toStdString(),
			title.toStdString(),
			description.toStdString(),
			dateTime.toStdString(),
			numberOfPeople.toInt(),
			link.toStdString()
		);
		this->populateList();
	}
	catch (const std::exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::copyButtonHandler()
{
	// Get the selected item
	QModelIndexList selectedRows = allEventsTable->selectionModel()->selectedRows();
	if (selectedRows.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No event selected!");
		return;
	}
	int row = selectedRows.first().row();
	const Event& event1 = allEventsModel->getEventAt(row);
	QString title = QString::fromStdString(event1.getTitle());
	std::string titleString = title.toStdString();
	const Event event = this->serv.getEventByTitle(titleString);
	try {
		this->serv.addEventToUserRepo(event);
		// increment the number of people
		this->serv.incrementNumberOfPeople(titleString, 1);
		this->populateUserList();
	}
	catch (const std::exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::addShowButtonHandler()
{
	// Get the selected item
	QModelIndexList selectedRows = allEventsTable->selectionModel()->selectedRows();
	if (selectedRows.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No event selected!");
		return;
	}
	int row = selectedRows.first().row();
	const Event& event1 = allEventsModel->getEventAt(row); // You need to add this method to your model
	QString title = QString::fromStdString(event1.getTitle());
	// go to the link
	std::string titleString = title.toStdString();
	const Event event = this->serv.getEventByTitle(titleString);
	std::string link = event.getLink();
	std::string command = "start " + link;
	system(command.c_str());
}

void GUI::showCsvButtonHandler()
{
	Repo* repo = new CSVFileRepo{ "Database.csv" };
	Repo* userRepo = new CSVFileRepo{ "Database.csv" };
	userRepo->clearEvents();
	Service service{ repo, userRepo };
	// add the data to the userRepo
	for (const Event& e : this->serv.getUserEvents()) {
		service.addEventToUserRepo(e);
	}
	// open the file in the chosen format
	service.openFileInChosenFormat();
}

void GUI::showHtmlButtonHandler()
{
	// create a new HTML Repo and service and then call the openFileInChosenFormat method
	Repo* repo = new HTMLRepo{ "Database.csv" };
	Repo* userRepo = new HTMLRepo{ "Database.csv" };
	userRepo->clearEvents();
	Service service{ repo, userRepo };
	// add the data to the userRepo
	for (const Event& e : this->serv.getUserEvents()) {
		service.addEventToUserRepo(e);
	}
	// open the file in the chosen format
	service.openFileInChosenFormat();

}

void GUI::filterButtonHandler()
{
	// Get the filter criteria from the user (the month of the events to be filtered)
	bool ok;
	QString month = QInputDialog::getText(this, "Filter Events", "Enter the month (1-12) (0 for all):", QLineEdit::Normal, "", &ok);
	if (!ok || month.isEmpty()) {
		return; // User canceled or didn't enter anything
	}
	int monthInt = month.toInt();
	if (monthInt < 0 || monthInt > 12) {
		QMessageBox::warning(this, "Warning", "Invalid month! Please enter a number between 1 and 12 (or 0 for all).");
		return;
	}
	// Filter the events based on the month
	if (monthInt == 0) {
		this->populateList();
	}
	else {
		vector<Event> filteredEvents = this->serv.getEventsForMonth(monthInt);
		delete allEventsModel; // Clear the previous model
		if (allEventsModel)
			delete allEventsModel;
		allEventsModel = new EventTableModel(filteredEvents, this);
		allEventsTable->setModel(allEventsModel);
		allEventsTable->resizeColumnsToContents();

	}
}

void GUI::removeFromUserButtonHandler()
{
	// Get the selected item
	QModelIndexList selectedRows = allEventsTable->selectionModel()->selectedRows();
	if (selectedRows.isEmpty()) {
		QMessageBox::warning(this, "Warning", "No event selected!");
		return;
	}
	int row = selectedRows.first().row();
	const Event& event = allEventsModel->getEventAt(row); // You need to add this method to your model
	QString title = QString::fromStdString(event.getTitle());
	std::string titleString = title.toStdString();
	try {
		// decrement the number of people
		this->serv.incrementNumberOfPeople(titleString, -1);
		this->serv.deleteEventFromUserRepo(titleString);
		this->populateUserList();
	}
	catch (const std::exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::undoButtonHandler()
{
	emit undoTriggered(); // Emit the signal to indicate undo action
}
void GUI::redoButtonHandler()
{
	emit redoTriggered(); // Emit the signal to indicate redo action
}

void GUI::onUndo()
{
	// Handle the undo action here
	try {
		this->serv.undo();
		this->populateList();
		this->populateUserList(); // Update user list as well
	}
	catch (const std::runtime_error& e) {
		QMessageBox::warning(this, "Undo Error", QString::fromStdString(e.what()));
		return;
	}
}

void GUI::onRedo()
{
	try {
		this->serv.redo();
		this->populateList();
		this->populateUserList(); // Update user list as well
	}
	catch (const std::runtime_error& e) {
		QMessageBox::warning(this, "Redo Error", QString::fromStdString(e.what()));
		return;
	}
}
