#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <ctime>
#include "UI.h"
#include <windows.h>

// Function to convert std::string to std::wstring
std::wstring stringToWString(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

void UI::run()
{
	while (true) {
		std::string fileType;
		std::cout << "Choose file type (1 - CSV, 2 - HTML): ";
		std::cin >> fileType;
		if (fileType == "1")
		{
			this->service.setRepos(new CSVFileRepo("DataBase.csv"), new CSVFileRepo("DataBase.csv"));
			this->service.loadInitialData();
			break;
		}
		else if (fileType == "2")
		{
			this->service.setRepos(new HTMLRepo("DataBase.csv"), new HTMLRepo("DataBase.csv"));
			this->service.loadInitialData();
			break;
		}
		else if (fileType == "0")
			return;
		else
			std::cout << "Invalid file type!\n";
	}

	while (true)
	{
		std::string mode;
		std::cout << "Choose mode (1 - administrator, 2 - user, 0 - exit): ";
		std::cin >> mode;
		if (mode == "1")
		{
			bool running = true;
			while (running) {
				this->printAdminMenu();
				std::string command;

				std::cout << "Enter command: ";
				std::cin >> command;
				if (command == "0")
					running = false;
				else if (command == "1")
				{
					// display events
					std::vector<Event> events = this->service.getEvents();
					std::cout << "\n";
					for (auto event : events)
					{
						std::cout << event.toString() << "\n\n";
					}
				}
				else if (command == "2") {
					// add event


					std::string title, description, link, dateTime;
					int numberOfPeople;
					std::cout << "Title: ";
					std::cin.ignore(); // Ignore any leftover newline character in the input buffer
					std::getline(std::cin, title);
					std::cout << "Description: ";

					std::getline(std::cin, description);
					std::cout << "Date and time (YYYY-MM-DD HH:MM:SS): ";
					std::string dateTimeStr;
					std::getline(std::cin, dateTime);
					std::cout << "Number of people: ";
					std::cin >> numberOfPeople;
					std::cout << "Link: ";
					std::cin >> link;
					try {
						this->service.addEvent(title, description, dateTime, numberOfPeople, link);
					}
					catch (const std::exception& e) {
						std::cout << "\n" << e.what() << "\n\n";
						continue;
					}
				}
				else if (command == "3")
				{
					// delete event
					std::string title;
					std::cout << "Title: ";
					std::cin.ignore(); // Ignore any leftover newline character in the input buffer
					std::getline(std::cin, title);
					try {
						this->service.deleteEvent(title);
					}
					catch (const std::exception& e) {
						std::cout << "\n" << e.what() << "\n\n";
						continue;
					}
					std::cout << "\nEvent deleted successfully!\n\n";
				}
				else if (command == "4")
				{
					// update event
					std::string oldTitle;
					std::cout << "Enter the title of the event to update: ";
					std::cin.ignore(); // Ignore any leftover newline character in the input buffer
					std::getline(std::cin, oldTitle);

					std::string title, description, link, dateTime;
					int numberOfPeople;
					std::cout << "Title: ";
					std::getline(std::cin, title);
					std::cout << "Description: ";
					std::getline(std::cin, description);
					std::cout << "Date and time (YYYY-MM-DD HH:MM:SS): ";
					std::getline(std::cin, dateTime);

					std::cout << "Number of people: ";
					std::cin >> numberOfPeople;
					std::cout << "Link: ";
					std::cin >> link;

					try {
						this->service.updateEvent(oldTitle, title, description, dateTime, numberOfPeople, link);
					}
					catch (const std::exception& e) {
						std::cout << "\n" << e.what() << "\n\n";
						continue;
					}
					std::cout << "\nEvent updated successfully!\n\n";
				}
				else
				{
					std::cout << "Invalid command!\n";
				}
			}
		}
		else if (mode == "2")
		{
			// user mode
			bool running = true;
			while (running) {
				this->printUserMenu();
				std::string command;
				std::cout << "Enter command: ";
				std::cin >> command;
				if (command == "0") {
					running = false;
					break;
				}
				else if (command == "1")
				{
					// see events for a given month, sorted
					std::string month;
					std::cout << "Enter month (1-12 / 0 for all): ";
					std::cin >> month;
					int monthInt = 0;
					try {
						monthInt = std::stoi(month);
						if (monthInt < 0 || monthInt > 12)
							throw std::exception("Invalid month");
					}
					catch (const std::exception& e) {
						std::cout << "\n" << e.what() << "\n\n";
						continue;
					}
					std::vector<Event> events = this->service.getEventsForMonth(monthInt); 
					if (events.size() == 0)
					{
						std::cout << "No events found for the given month!\n";
						continue;
					}
					if (events.size() == this->service.getUserNumberOfEvents())
					{
						std::cout << "\nNo more events to display!\n";
						continue;
					}
					auto it = events.begin();
					while (it != events.end())
					{
						if (events.size() == this->service.getUserNumberOfEvents())
						{
							std::cout << "\nNo more events to display!\n";
							break;
						}
						std::vector<Event> userEvents = this->service.getUserEvents();
						bool found = false;
						for (auto event2 : userEvents)
						{
							if (it->getTitle() == event2.getTitle())
							{
								if (it + 1 == events.end())
									it = events.begin() - 1;
								++it;
								found = true;
								continue;
							}
						}
						if (found)
							continue;
						std::cout << it->toString() << "\n\n";
						// dysplay it->getLink() in browser
						std::string link = it->getLink();
						std::wstring wLink = stringToWString(link);
						// Open link in browser
						// ShellExecute(0, 0, wLink.c_str(), 0, 0, SW_SHOW);

						std::string command;
						std::cout << "\nDo you want to add this event to your list? (yes/no/exit): ";
						std::cin >> command;
						std::cout << "\n";
						if (command == "exit")
							break;
						if (command == "yes")
						{
							it->setNumberOfPeople(it->getNumberOfPeople() + 1);
							this->service.updateEvent(it->getTitle(), it->getTitle(), it->getDescription(), it->getDateTime(), it->getNumberOfPeople(), it->getLink());
							Event e{ it->getTitle(), it->getDescription(), it->getDateTime(), it->getNumberOfPeople(), it->getLink() };
							this->service.addEventToUserRepo(e);
						}
						bool final = false;
						if (it + 1 == events.end())
							it = events.begin();
						else
							++it;
					}
				}
				else if (command == "2")
				{
					// see user events
					std::vector<Event> events = this->service.getUserEvents();
					std::cout << "\n";
					for (auto event : events)
					{
						std::cout << event.toString() << "\n\n";
					}
				}
				else if (command == "3")
				{
					// delete event from user list
					std::string title;
					std::cout << "Title: ";
					std::cin.ignore(); // Ignore any leftover newline character in the input buffer
					std::getline(std::cin, title);
					try {
						this->service.deleteEventFromUserRepo(title);
					}
					catch (const std::exception& e) {
						std::cout << "\n" << e.what() << "\n\n";
						continue;
					}
					std::cout << "\nEvent deleted successfully!\n\n";
				}
				else if (command == "4")
				{
					// show user events in the chosen format
					this->service.openFileInChosenFormat();
				}
				else
				{
					std::cout << "Invalid command!\n";
				}
			}
		}
		else if (mode == "0")
		{
			this->writeToFile();
			break;
		}
		else
		{
			std::cout << "Invalid mode!\n";
		}
	}
}

void UI::printAdminMenu()
{
	std::cout << "1. Display events\n";
	std::cout << "2. Add event\n";
	std::cout << "3. Delete event\n";
	std::cout << "4. Update event\n";
	std::cout << "0. Exit\n";
}

void UI::printUserMenu()
{
	std::cout << "1. See all events.\n";
	std::cout << "2. See your events.\n";
	std::cout << "3. Delete an event from your list.\n";
	std::cout << "4. Show your events in the chosen format\n";
	std::cout << "0. Exit\n";
}

void UI::writeToFile()
{
	this->service.writetofile();
}


