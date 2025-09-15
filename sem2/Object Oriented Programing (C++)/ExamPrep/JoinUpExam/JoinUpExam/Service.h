#pragma once
#include "Subject.h"
#include "Repository.h"
#include <stdexcept>
class Service :
    public Subject
{
private:
	Repository& repository;
public:
	Service(Repository& repo) : repository(repo) {}
	void addPerson(const Person& person) {
		repository.addPerson(person);
	}
	void addEvent(const Event& event) {
		repository.addEvent(event);
	}
	void addEvent(const std::string& organiser, const std::string& name, const std::string& description,
		const std::pair<double, double>& location, const std::string& date) {
		Event event(organiser, name, description, location, date);
		std::vector<Event> events = repository.getEvents();
		//operation fails if event with the same name and location already exists
		for (const auto& existingEvent : events) {
			if (existingEvent.getName() == name && existingEvent.getLocation() == location) {
				throw std::runtime_error("Event with the same name and location already exists.");
			}
		}
		repository.addEvent(event);
	}

	std::vector<std::string> getPersonsAttendingEvent(const std::string& eventName) {
		std::vector<std::string> participants;
		repository.getEventParticipants(eventName, participants);
		return participants;
	}

	void attendEvent(const std::string& personName, const std::string& eventName) {
		repository.attendEvent(personName, eventName);
		notifyObservers();
	}

	std::vector<Person>& getPersons() {
		return repository.getPersons();
	}
	std::vector<Event>& getEvents() {
		return repository.getEvents();
	}
	void clear() {
		repository.clear();
	}

	~Service() {
		repository.savePersons();
		repository.saveEvents();
		repository.saveEventParticipants();
	}
};

