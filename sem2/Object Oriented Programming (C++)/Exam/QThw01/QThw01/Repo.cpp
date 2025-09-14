#include "Repo.h"
#include <algorithm>
#include <fstream>
#include <iterator>

#include <algorithm>

#include <fstream>

#include <iterator>

void Repo::addEventToData(const Event e)
{
	events.push_back(e);
}
void Repo::deleteEvent(const std::string title)
{
	for (auto it = events.begin(); it != events.end(); ++it)
	{
		if (it->getTitle() == title)
		{
			events.erase(it);
			break;
		}
	}
}

void Repo::updateEvent(const std::string& oldTitle, const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link) {
	auto it = std::find_if(events.begin(), events.end(), [&oldTitle](const Event& event) {
		return event.getTitle() == oldTitle;
		});

	if (it != events.end()) {
		it->setTitle(title);
		it->setDescription(description);
		it->setDateTime(dateTime);
		it->setNumberOfPeople(numberOfPeople);
		it->setLink(link);
	}
	else {
		throw std::runtime_error("Event not found!");
	}
}
void Repo::clearEvents()
{
	events.clear();
}
std::vector<Event> Repo::getEvents() const
{
	return events;
}
std::vector<Event> Repo::getEventsForMonth(int month)
{
	std::vector<Event> eventsForMonth;
	std::copy_if(this->events.begin(), this->events.end(), std::back_inserter(eventsForMonth),
		[month](const Event& event) {
			std::string time = std::string(event.getDateTime());
			return (month == 0 || std::stoi(time.substr(5, 2)) == month);
		});

	return eventsForMonth;
}
int Repo::getNumberOfEvents() const
{
	return events.size();
}

void Repo::loadInitialData(const std::string& fileName)
{
	std::fstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + fileName);
	}
	Event event;
	while(file >> event)
	{
		events.push_back(event);
	}
}

void Repo::writeToFile(std::string filename)
{
	std::ofstream file(filename);
	for (auto event : events) {
		file << event << "\n";
	}
}

Event Repo::getEventByTitle(const std::string& title) const
{
    auto it = std::find_if(events.begin(), events.end(),
        [&title](const Event& event) {
            return event.getTitle() == title;
        });
    if (it != events.end()) {
        return *it;
    }
	else {
		throw std::runtime_error("Event not found!");
	}
}
