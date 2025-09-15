#pragma once
#include <string>
#include "Event.h"
#include <stdexcept>

//class Event
//{
//private:
//	std::string title;
//	std::string description;
//	std::string dateTime;
//	int numberOfPeople;
//	std::string link;
#include "Event.h"
#include "EventException.h"

class Event;

class EventValidator
{
public:
	static void validateEvent(const Event& e);
	static void validateTitle(const std::string& title);
	static void validateDescription(const Event& e);
	static void validateDateTime(const Event& e);
	static void validateNumberOfPeople(int numberOfPeople);
	static void validateLink(const std::string& link);
};

