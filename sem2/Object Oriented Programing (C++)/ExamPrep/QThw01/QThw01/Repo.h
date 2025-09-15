#pragma once
#include <vector>
#include "Event.h"

class Repo {
protected:
	std::vector<Event> events;
public:
	virtual ~Repo() = default;
	virtual void addEventToData(const Event e);
	virtual void deleteEvent(const std::string title);
	virtual void updateEvent(const std::string& oldTitle, const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link);
	virtual void clearEvents();
	virtual std::vector<Event> getEvents() const;
	virtual std::vector<Event> getEventsForMonth(int month);
	virtual int getNumberOfEvents() const;
	virtual void loadInitialData(const std::string& fileName);
	virtual void writeToFile(std::string filename);
	virtual Event getEventByTitle(const std::string& title) const;
};

