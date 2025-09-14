#pragma once
#include <string>
#include <vector>
#include "EventValidator.h"

class Event
{
private:
    std::string title;
    std::string description;
    std::string dateTime;
    int numberOfPeople;
    std::string link;

public:
    // Constructor
    Event(const std::string& title = "", const std::string& description = "", 
        const std::string dateTime = "",
        int numberOfPeople = 0, const std::string& link = "");
    // Destructor
    ~Event();
	// Copy constructor
	Event(const Event& e);
	// Assignment operator
	Event& operator=(const Event& e);
    // Getters and setters
    std::string getTitle() const;
    void setTitle(const std::string& title);

    std::string getDescription() const;
    void setDescription(const std::string& description);

    std::string getDateTime() const;
    void setDateTime(const std::string& dateTime);

    int getNumberOfPeople() const;
    void setNumberOfPeople(int numberOfPeople);

    std::string getLink() const;
    void setLink(const std::string& link);

	std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, const Event& e);
	friend std::istream& operator>>(std::istream& is, Event& e);
};