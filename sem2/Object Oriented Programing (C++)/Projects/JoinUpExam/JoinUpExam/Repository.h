#pragma once
#include "Person.h"
#include "Event.h"
#include <vector>
#include <unordered_map>
#include <stdexcept>
class Repository
{
private:
	std::vector<Person> persons;
	std::vector<Event> events;
	std::vector<std::pair<Event, std::string> > eventParticipants; // Event and list of participants
	std::string personsFileName;
	std::string eventsFileName;
	std::string eventParticipantsFileName = "event_participants.txt"; // Default file name for event participants
public:
	Repository(std::string& personsFileName, std::string& eventsFileName)
		: personsFileName(personsFileName), eventsFileName(eventsFileName) {
		loadPersons();
		loadEvents();
		loadEventParticipants();
	}

	void loadPersons();
	void loadEvents();
	void loadEventParticipants();
	void saveEventParticipants();

	void attendEvent(const std::string& personName, const std::string& eventName) {
		for (auto& event : events) {
			if (event.getName() == eventName) {
				eventParticipants.push_back({ event,  personName  });
				return;
			}
		}
		throw std::runtime_error("Event not found.");
	}

	void getEventParticipants(const std::string& eventName, std::vector<std::string>& participants) {
		for (const auto& pair : eventParticipants) {
			if (pair.first.getName() == eventName) {
				participants.push_back(pair.second);
			}
		}
	}

	void savePersons();
	void saveEvents();


	void addPerson(const Person& person) {
		persons.push_back(person);
	}
	void addEvent(const Event& event) {
		events.push_back(event);
	}
	std::vector<Person>& getPersons() {
		return persons;
	}
	std::vector<Event>& getEvents() {
		return events;
	}
	void clear() {
		persons.clear();
		events.clear();
	}
};

