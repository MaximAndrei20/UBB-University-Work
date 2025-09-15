#include "PersonsWindow.h"
#include <QMessageBox>

PersonsWindow::PersonsWindow(Service& service, Person* person, QWidget *parent)
	: QWidget(parent), service(service), person(person)
{
	ui.setupUi(this);
	// set the window title to the person's name
	setWindowTitle(QString::fromStdString(person->getName()));
	//set label to its location
	ui.locationLabel->setText(QString::fromStdString("Location: " 
		+ std::to_string(person->getLocation().first) + ", " 
		+ std::to_string(person->getLocation().second)));
	//if is organizer add lineedits to add events
	if (person->isOrganiser()) {
		eventNameEdit = new QLineEdit(this);
		eventNameEdit->setPlaceholderText("Event Name");
		eventDescriptionEdit = new QLineEdit(this);
		eventDescriptionEdit->setPlaceholderText("Event Description");
		eventLatitudeEdit = new QLineEdit(this);
		eventLatitudeEdit->setPlaceholderText("Event Latitude");
		eventLongitudeEdit = new QLineEdit(this);
		eventLongitudeEdit->setPlaceholderText("Event Longitude");
		eventDateEdit = new QLineEdit(this);
		eventDateEdit->setPlaceholderText("Event Date (DD/MM)");
		ui.verticalLayout->addWidget(eventNameEdit);
		ui.verticalLayout->addWidget(eventDescriptionEdit);
		ui.verticalLayout->addWidget(eventLatitudeEdit);
		ui.verticalLayout->addWidget(eventLongitudeEdit);
		ui.verticalLayout->addWidget(eventDateEdit);

		addEventButton = new QPushButton("Add Event", this);
		ui.verticalLayout->addWidget(addEventButton);
		eventParticipantsLabel = new QLabel(this);
		eventParticipantsLabel->setText("Event Participants: ");
		eventDescriptionOrganizersLabel = new QLabel(this);
		eventDescriptionOrganizersLabel->setText("Description: ");
		ui.verticalLayout->addWidget(eventParticipantsLabel);
		ui.verticalLayout->addWidget(eventDescriptionOrganizersLabel);

		changeDescription = new QLineEdit(this);
		changeDescription->setPlaceholderText("Change Event Description");
		changeDescriptionButton = new QPushButton("Change Description/Date", this);
		changeDate = new QLineEdit(this);
		changeDate->setPlaceholderText("Change Event Date (DD/MM)");
		ui.verticalLayout->addWidget(changeDescription);
		ui.verticalLayout->addWidget(changeDate);
		ui.verticalLayout->addWidget(changeDescriptionButton);

		connect(changeDescriptionButton, &QPushButton::clicked, this, &PersonsWindow::onChangeDescriptionButtonClicked);


		connect(addEventButton, &QPushButton::clicked, this, &PersonsWindow::onAddButtonClicked);
		connect(ui.listWidget, &QListWidget::itemClicked, this, &PersonsWindow::onOrganizerEventSelected);
	}
	else {
		goingButton = new QPushButton("Going", this);
		ui.verticalLayout->addWidget(goingButton);
		eventDescriptionLabel = new QLabel(this);
		eventDescriptionLabel->setText("Description: ");
		ui.verticalLayout->addWidget(eventDescriptionLabel);


		connect(ui.listWidget, &QListWidget::itemClicked, this, &PersonsWindow::onEventSelected);
		connect(goingButton, &QPushButton::clicked, this, &PersonsWindow::onGoingButtonClicked);
	}
			


	connect(ui.nearEventsCheckBox, &QCheckBox::checkStateChanged, this, &PersonsWindow::onCheckBoxStateChanged);


	populateList();
}

PersonsWindow::~PersonsWindow()
{}

void PersonsWindow::update()
{
	populateList();
}

void PersonsWindow::populateList()
{
	// clear the list widget
	ui.listWidget->clear();
	std::vector<Event> events{};
	if (ui.nearEventsCheckBox->isChecked()) {
		ui.listWidget->clear();
		for (const auto& event : service.getEvents()) {
			double distance = std::sqrt(std::pow(event.getLocation().first - person->getLocation().first, 2) +
				std::pow(event.getLocation().second - person->getLocation().second, 2));
			if (distance <= 5.0) {
				events.push_back(event);
			}
		}
	}
	else {
		ui.listWidget->clear();
		for (const auto& event : service.getEvents()) {
			events.push_back(event);
		}
	}
	std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
		// DD/MM format
		int dayA = std::stoi(a.getDate().substr(0, 2));
		int monthA = std::stoi(a.getDate().substr(3, 2));
		int dayB = std::stoi(b.getDate().substr(0, 2));
		int monthB = std::stoi(b.getDate().substr(3, 2));
		if (monthA != monthB) {
			return monthA < monthB; 
		}
		return dayA < dayB;
		});
	for (auto event : events) {
		QString itemText = QString::fromStdString(event.getName() +
			" (" + std::to_string(event.getLocation().first) + ", " +
			std::to_string(event.getLocation().second) + ")") +
			" (date: " + QString::fromStdString(event.getDate()) + ")";
		ui.listWidget->addItem(itemText);
		//if user is organiser and event is organised by user, set item background to green
		if (person->isOrganiser() && event.getOrganiser() == person->getName()) {
			QListWidgetItem* item = ui.listWidget->item(ui.listWidget->count() - 1);
			item->setBackground(Qt::green);
		}

	}
}

void PersonsWindow::onAddButtonClicked()
{

	if (eventNameEdit->text().isEmpty() || eventDescriptionEdit->text().isEmpty() ||
		eventLatitudeEdit->text().isEmpty() || eventLongitudeEdit->text().isEmpty() ||
		eventDateEdit->text().isEmpty()) {
		QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
		return;
	}
	try {
		std::string name = eventNameEdit->text().toStdString();
		std::string description = eventDescriptionEdit->text().toStdString();
		double latitude = std::stod(eventLatitudeEdit->text().toStdString());
		double longitude = std::stod(eventLongitudeEdit->text().toStdString());
		std::string date = eventDateEdit->text().toStdString();
		service.addEvent(person->getName(), name, description,
			std::make_pair(latitude, longitude), date);
		service.notifyObservers();
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
	}
}

void PersonsWindow::onEventSelected()
{
	if (ui.listWidget->currentItem() == nullptr) {
		return; // No item selected
	}



	QString selectedItemText = ui.listWidget->currentItem()->text();
	std::string eventName = selectedItemText.split('(')[0].trimmed().toStdString();

	//show events description
	Event selectedEvent;
	for (const auto& event : service.getEvents()) {
		if (event.getName() == eventName) {
			selectedEvent = event;
			break;
		}
	}
	if (selectedEvent.getName().empty()) {
		QMessageBox::warning(this, "Error", "Event not found.");
		return;
	}
	eventDescriptionLabel->setText(QString::fromStdString("Description: " + selectedEvent.getDescription()));



	std::vector<std::string> participantsToSelectedEvent = service.getPersonsAttendingEvent(eventName);
	if (std::find(participantsToSelectedEvent.begin(), participantsToSelectedEvent.end(), person->getName()) != participantsToSelectedEvent.end()) {
		goingButton->setEnabled(false);
		return;
	}
	else {
		goingButton->setEnabled(true);
	}
	
}

void PersonsWindow::onGoingButtonClicked()
{
	try {
		QString selectedItemText = ui.listWidget->currentItem()->text();
		std::string eventName = selectedItemText.split('(')[0].trimmed().toStdString();
		service.attendEvent(person->getName(), eventName);
		service.notifyObservers();
		QMessageBox::information(this, "Success", "You are now attending the event.");
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
	}
}

void PersonsWindow::onOrganizerEventSelected()
{
	QString selectedItemText = ui.listWidget->currentItem()->text();
	std::string eventName = selectedItemText.split('(')[0].trimmed().toStdString();

	//show events description
	Event selectedEvent;
	for (const auto& event : service.getEvents()) {
		if (event.getName() == eventName) {
			selectedEvent = event;
			break;
		}
	}
	if (selectedEvent.getName().empty()) {
		QMessageBox::warning(this, "Error", "Event not found.");
		return;
	}
	eventDescriptionOrganizersLabel->setText(QString::fromStdString("Description: " + selectedEvent.getDescription()));


	std::vector<std::string> participantsToSelectedEvent = service.getPersonsAttendingEvent(eventName);
	if (participantsToSelectedEvent.empty()) {
		eventParticipantsLabel->setText("Event Participants: None");
	}
	else {
		QString participantsText = "Event Participants: ";
		for (const auto& participant : participantsToSelectedEvent) {
			participantsText += QString::fromStdString(participant) + ", ";
		}
		// Remove the last comma and space
		participantsText.chop(2);
		eventParticipantsLabel->setText(participantsText);
	}
}

void PersonsWindow::onChangeDescriptionButtonClicked()
{
	QString selectedItemText = ui.listWidget->currentItem()->text();
	std::string eventName = selectedItemText.split('(')[0].trimmed().toStdString();
	for (auto& event : service.getEvents()) {
		if (event.getName() == eventName) {
			if (changeDescription->text().isEmpty() && changeDate->text().isEmpty()) {
				break;
			}
			event.setDescription(changeDescription->text().toStdString());
			service.notifyObservers();
			break;
		}
	}

	std::string date = selectedItemText.split('(')[1].split(')')[0].trimmed().toStdString();
	//change date
	if (!changeDate->text().isEmpty()) {
		for (auto& event : service.getEvents()) {
			if (event.getName() == eventName) {
				if (changeDate->text().isEmpty()) {
					break;
				}
				event.setDate(changeDate->text().toStdString());
				service.notifyObservers();
				break;
			}
		}
	}
	
}

