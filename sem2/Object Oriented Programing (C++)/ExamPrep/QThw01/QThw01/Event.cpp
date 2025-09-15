#include "Event.h"
#include <sstream>
#include <iomanip>
#include <string>

// Constructor
Event::Event(const std::string& title, const std::string& description, const std::string dateTime, int numberOfPeople, const std::string& link)
    : title(title), description(description), dateTime(dateTime), numberOfPeople(numberOfPeople), link(link) {
}

Event::~Event()
{
}

Event::Event(const Event& e)
{
	this->title = e.title;
	this->description = e.description;
	this->dateTime = e.dateTime;
	this->numberOfPeople = e.numberOfPeople;
	this->link = e.link;
}

Event& Event::operator=(const Event& e)
{
	this->title = e.title;
	this->description = e.description;
	this->dateTime = e.dateTime;
	this->numberOfPeople = e.numberOfPeople;
	this->link = e.link;
	return *this;
}

// Getters and setters
std::string Event::getTitle() const { return title; }
void Event::setTitle(const std::string& title) { this->title = title; }

std::string Event::getDescription() const { return description; }
void Event::setDescription(const std::string& description) { this->description = description; }

std::string Event::getDateTime() const { return dateTime; }
void Event::setDateTime(const std::string& dateTime) { this->dateTime = dateTime; }

int Event::getNumberOfPeople() const { return numberOfPeople; }
void Event::setNumberOfPeople(int numberOfPeople) { this->numberOfPeople = numberOfPeople; }

std::string Event::getLink() const { return link; }
void Event::setLink(const std::string& link) { this->link = link; }

std::string Event::toString() const{
	std::ostringstream oss;
	oss << title << "|" << description << "|" << dateTime << "|" << numberOfPeople << "|" << link;
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Event& e)
{
	os << e.getTitle() << "," << e.getDescription() << "," << e.getDateTime() << "," << e.getNumberOfPeople() << "," << e.getLink();
    return os;
}

std::istream& operator>>(std::istream& is, Event& e)
{
    // Read a line from the input stream
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string title, description, dateTime, link;
        int numberOfPeople;

        // Parse the line using '|' as a delimiter
        if (std::getline(iss, title, ',') &&
            std::getline(iss, description, ',') &&
            std::getline(iss, dateTime, ',') &&
            (iss >> numberOfPeople)) {

            // Now handle the remaining part (link)
            iss.ignore(1, ','); // Skip the '|' after numberOfPeople
            std::getline(iss, link); // Read the rest (even if it contains '|')

            // Trim any trailing whitespace (optional)
            link.erase(link.find_last_not_of(" \n\r\t") + 1);

            // Set the parsed values to the Event object
            e.setTitle(title);
            e.setDescription(description);
            e.setDateTime(dateTime);
            e.setNumberOfPeople(numberOfPeople);
            e.setLink(link);
        }
        else {
            // Handle invalid format by setting the stream to a failed state
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}

