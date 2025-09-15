#include "Service.h"

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
	this->repo->addEventToData(e);
}

void Service::addEventToUserRepo(const Event& e)
{
	this->userRepo->addEventToData(e);
}

void Service::deleteEventFromUserRepo(const std::string& title)
{
	this->userRepo->deleteEvent(title);
}

void Service::deleteEvent(const std::string& title)
{
	this->repo->deleteEvent(title);
}

void Service::updateEvent(const std::string& oldTitle, const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link)
{
	Event e{ title, description, dateTime, numberOfPeople, link };
	EventValidator::validateEvent(e);
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

void Service::openFileInChosenFormat()
{
	// Open the file in the chosen format
	
	FileRepo* fileRepo = dynamic_cast<FileRepo*>(this->userRepo);
	fileRepo->openFileInChosenFormat();
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

