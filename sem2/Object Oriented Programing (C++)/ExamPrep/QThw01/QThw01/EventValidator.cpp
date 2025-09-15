#include "EventValidator.h"

void EventValidator::validateEvent(const Event& e)
{
	EventValidator::validateTitle(e.getTitle());
	EventValidator::validateDescription(e);
	EventValidator::validateDateTime(e);
	EventValidator::validateNumberOfPeople(e.getNumberOfPeople());
	EventValidator::validateLink(e.getLink());
}

void EventValidator::validateTitle(const std::string& title)
{
	if (title.empty())
		throw EventException("Title cannot be empty");
}

void EventValidator::validateDescription(const Event& e)
{
	if (e.getDescription().empty())
		throw EventException("Description cannot be empty");
}

void EventValidator::validateDateTime(const Event& e)
{
	// Must be of form YYYY-MM-DD HH:MM:SS
	if (e.getDateTime().empty())
		throw EventException("Date and time cannot be empty");
	if (e.getDateTime().length() != 19)
		throw EventException("Date and time must be of form YYYY-MM-DD HH:MM:SS");
	if (e.getDateTime()[4] != '-' || e.getDateTime()[7] != '-' || e.getDateTime()[10] != ' ' || e.getDateTime()[13] != ':' || e.getDateTime()[16]!=':')
		throw EventException("Date and time must be of form YYYY-MM-DD HH:MM:SS");
	//validate year:
	int year = std::stoi(e.getDateTime().substr(0, 4));
	if (year < 1900 || year > 2100)
		throw EventException("Year must be between 1900 and 2100");
	//validate month:
	int month = std::stoi(e.getDateTime().substr(5, 2));
	if (month < 1 || month > 12)
		throw EventException("Month must be between 1 and 12");
	//validate day:
	int day = std::stoi(e.getDateTime().substr(8, 2));
	if (day < 1 || day > 31)
		throw EventException("Day must be between 1 and 31");
	//validate hour:
	int hour = std::stoi(e.getDateTime().substr(11, 2));
	if (hour < 0 || hour > 23)
		throw EventException("Hour must be between 0 and 23");
	//validate minute:
	int minute = std::stoi(e.getDateTime().substr(14, 2));
	if (minute < 0 || minute > 59)
		throw EventException("Minute must be between 0 and 59");
	//validate second:
	int second = std::stoi(e.getDateTime().substr(17, 2));
	if (second < 0 || second > 59)
		throw EventException("Second must be between 0 and 59");

}

void EventValidator::validateNumberOfPeople(int numberOfPeople)
{
	if (numberOfPeople < 0)
		throw EventException("Number of people cannot be negative");
}

void EventValidator::validateLink(const std::string& link)
{
	/// form: www.something.com
	if (link.empty())
		throw EventException("Link cannot be empty");
	if (link.find(".com") == std::string::npos)
		throw EventException("Link must end with .com");

}
