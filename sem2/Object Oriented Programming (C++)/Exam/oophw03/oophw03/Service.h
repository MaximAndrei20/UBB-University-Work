#pragma once
#include "Repo.h"
#include "CSVFileRepo.h"
#include "HTMLRepo.h"

class Service
{
private:
	Repo* repo;
	Repo* userRepo;
public:
	// Default constructor
	Service(Repo* repo = nullptr, Repo* userRepo = nullptr);
	// Assignment Operator
	Service& operator=(const Service& s);

	void setRepos(Repo* repo, Repo* userRepo);
	// adds an event to the repository
	// params title: the title of the event to be added
	// params description: the description of the event to be added
	// params dateTime: the date and time of the event to be added
	// params numberOfPeople: the number of people for the event to be added
	// params link: the link for the event to be added
	void addEvent(const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link);
	
	// adds an event to the user repository
	// params e: the event to be added
	void addEventToUserRepo(const Event& e);
	
	// deletes an event from the user repository
	// params title: the title of the event to be deleted
	void deleteEventFromUserRepo(const std::string& title);
	
	// deletes an event from the repository
	// params title: the title of the event to be deleted
	void deleteEvent(const std::string& title);

	// updates an event in the repository
	// params oldTitle: the title of the event to be updated
	// params title: the new title of the event
	// params description: the new description of the event
	// params dateTime: the new date and time of the event
	// params numberOfPeople: the new number of people for the event
	// params link: the new link for the event
	void updateEvent(const std::string& oldTitle, const std::string& title, const std::string& description, const std::string& dateTime, int numberOfPeople, const std::string& link);
	
	// returns the events from the repository
	std::vector<Event> getEvents() const;
	
	// returns the events from the user repository
	std::vector<Event> getUserEvents() const;
	
	// returns the events for a specific month
	// params month: the month for which to get the events
	std::vector<Event> getEventsForMonth(int month);
	
	// returns the number of events in the repository
	int getNumberOfEvents() const;
	
	// returns the number of events in the user repository
	int getUserNumberOfEvents() const;
	
	void openFileInChosenFormat();

	void writetofile();
	void loadInitialData();
};

