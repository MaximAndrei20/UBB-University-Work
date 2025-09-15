#include "Service.h"
#include "ActionAdd.h"
#include "ActionDelete.h"
#include "ActionUpdate.h"

Service::Service(Repo* repo, Repo* userRepo)
{
	this->repo = repo;
	this->userRepo = userRepo;
}

Service& Service::operator=(const Service& s)
{
	this->repo = s.repo;
	this->userRepo = s.userRepo;
	return *this;
}

void Service::setRepos(Repo* repo, Repo* userRepo)
{
	this->repo = repo;
	this->userRepo = userRepo;
}

void Service::addEvent(const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link)
{
	Event e{ title, description, dateTime, numberOfPeople, link };
	EventValidator::validateEvent(e);
	// Check if the event already exists in the repository
	auto events = this->repo->getEvents();
	auto it = std::find_if(events.begin(), events.end(), [&title](const Event& event) {
		return event.getTitle() == title;
		});
	if (it != events.end()) {
		throw std::runtime_error("Event with this title already exists!");
	}
	this->repo->addEventToData(e);

	Action* action = new ActionAdd(e, *this->repo);
	this->undoStack.push(action);
}

void Service::addEventToUserRepo(const Event& e)
{
	auto events = this->userRepo->getEvents();
	auto it = std::find_if(events.begin(), events.end(), [&e](const Event& event) {
		return event.getTitle() == e.getTitle();
		});
	if (it != events.end()) {
		throw std::runtime_error("Event with this title already exists in user repository!");
	}
	this->userRepo->addEventToData(e);
	Action* action = new ActionAdd(e, *this->userRepo);
	this->undoStack.push(action);
}

void Service::deleteEventFromUserRepo(const std::string& title)
{
	Action* action = new ActionDelete(this->userRepo->getEventByTitle(title), *this->userRepo);
	try {
		this->userRepo->deleteEvent(title);
		this->undoStack.push(action);
	}
	catch (const std::runtime_error& e) {
		delete action; // Clean up the action if deletion fails
		throw; // Re-throw the exception to be handled by the caller
	}
}

void Service::deleteEvent(const std::string& title)
{
	Event event = this->repo->getEventByTitle(title);
	Action* action = new ActionDelete(event, *this->repo);
	try {
		this->repo->deleteEvent(title);
		this->undoStack.push(action);
	}
	catch (const std::runtime_error& e) {
		delete action; // Clean up the action if deletion fails
		throw; // Re-throw the exception to be handled by the caller
	}
}

void Service::updateEvent(const std::string& oldTitle, const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link)
{
	Event e{ title, description, dateTime, numberOfPeople, link };
	EventValidator::validateEvent(e);

	// Check if the event with the old title exists
	Event oldEvent = this->repo->getEventByTitle(oldTitle);
	if (oldEvent.getTitle().empty()) {
		throw std::runtime_error("Event with the old title does not exist!");
	}
	// Check if the new title already exists
	auto events = this->repo->getEvents();
	auto it = std::find_if(events.begin(), events.end(), [&title, &oldTitle](const Event& event) {
		return event.getTitle() == title && event.getTitle() != oldTitle;
		});
	if (it != events.end()) {
		throw std::runtime_error("Event with this title already exists!");
	}

	Action* action = new ActionUpdate(oldEvent, e, *this->repo);
	this->undoStack.push(action);

	this->repo->deleteEvent(oldTitle);
	this->repo->addEventToData(e);

}

std::vector<Event> Service::getEvents() const
{
	return this->repo->getEvents();
}

std::vector<Event> Service::getUserEvents() const
{
	return this->userRepo->getEvents();
}

std::vector<Event> Service::getEventsForMonth(int month)
{
	if(month == 0)
		return this->repo->getEvents();
	else return this->repo->getEventsForMonth(month);
}

int Service::getNumberOfEvents() const
{
	return this->repo->getNumberOfEvents();
}

int Service::getUserNumberOfEvents() const
{
	return this->userRepo->getNumberOfEvents();
}

Event Service::getEventByTitle(const std::string& title) const
{
	std::string titleCopy = title;
	return this->repo->getEventByTitle(titleCopy);
}

void Service::openFileInChosenFormat()
{
	// Open the file in the chosen format
	
	FileRepo* fileRepo = dynamic_cast<FileRepo*>(this->userRepo);
	fileRepo->openFileInChosenFormat();
}

void Service::incrementNumberOfPeople(std::string title, int count) {
	Event event = this->repo->getEventByTitle(title);
	int newNumberOfPeople = event.getNumberOfPeople() + count;
	event.setNumberOfPeople(newNumberOfPeople);

	std::string oldTitle = title;
	std::string newTitle = event.getTitle();
	std::string description = event.getDescription();
	std::string dateTime = event.getDateTime();
	std::string link = event.getLink();

	this->repo->updateEvent(oldTitle, newTitle, description, dateTime, newNumberOfPeople, link);
	this->userRepo->updateEvent(oldTitle, newTitle, description, dateTime, newNumberOfPeople, link);
}

void Service::undo()
{
	if (!this->undoStack.empty()) {
		Action* action = this->undoStack.top();
		action->executeUndo();
		this->undoStack.pop();
		this->redoStack.push(action);
	}
	else {
		throw std::runtime_error("No actions to undo!");
	}
}

void Service::redo()
{
	if (!this->redoStack.empty()) {
		Action* action = this->redoStack.top();
		action->executeRedo();
		this->redoStack.pop();
		this->undoStack.push(action);
	}
	else {
		throw std::runtime_error("No actions to redo!");
	}
}

void Service::writetofile()
{
	FileRepo* fileRepo = dynamic_cast<FileRepo*>(this->repo);
	fileRepo->setFileName("Database.csv");
	fileRepo->writeToFile("Database.csv");
}

void Service::loadInitialData()
{
	this->repo->loadInitialData("Database.csv");
}

