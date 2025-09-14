#include "Repository.h"
#include <fstream>

void Repository::loadPersons()
{
	//format: name|latitude|longitude|organiser
	std::ifstream file(personsFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open persons file");
	}
	std::string line;
	while (std::getline(file, line)) {
		size_t pos = 0;
		std::string name;
		double latitude, longitude;
		bool organiser;
		pos = line.find('|');
		name = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find('|');
		latitude = std::stod(line.substr(0, pos));
		line.erase(0, pos + 1);
		pos = line.find('|');
		longitude = std::stod(line.substr(0, pos));
		line.erase(0, pos + 1);
		organiser = (line == "1");
		persons.emplace_back(name, std::make_pair(latitude, longitude), organiser);
	}
}

void Repository::loadEvents() {
	//format: organiser|name|description|latitude|longitude|date
	std::ifstream file(eventsFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open events file");
	}
	std::string line;
	while (std::getline(file, line)) {
		size_t pos = 0;
		std::string organiser, name, description;
		double latitude, longitude;
		pos = line.find('|');
		organiser = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find('|');
		name = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find('|');
		description = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find('|');
		latitude = std::stod(line.substr(0, pos));
		line.erase(0, pos + 1);
		pos = line.find('|');
		longitude = std::stod(line.substr(0, pos));
		line.erase(0, pos + 1);
		std::string date = line;
		events.emplace_back(organiser, name, description, std::make_pair(latitude, longitude), date);
	}
}

void Repository::savePersons()
{
	std::ofstream file(personsFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open persons file for writing");
	}
	for (const auto& person : persons) {
		file << person.getName() << "|"
			<< person.getLocation().first << "|"
			<< person.getLocation().second << "|"
			<< (person.isOrganiser() ? "1" : "0") << "\n";
	}
}

void Repository::saveEvents()
{
	std::ofstream file(eventsFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open events file for writing");
	}
	for (const auto& event : events) {
		file << event.getOrganiser() << "|"
			<< event.getName() << "|"
			<< event.getDescription() << "|"
			<< event.getLocation().first << "|"
			<< event.getLocation().second << "|"
			<< event.getDate() << "\n";
	}
}

void Repository::saveEventParticipants() {
	std::ofstream file(eventParticipantsFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open event participants file for writing");
	}
	for (const auto& pair : eventParticipants) {
		file << pair.first.getName() << "|" << pair.second << "\n";
	}
}

void Repository::loadEventParticipants() {
	//format: event_name|participant_name
	std::ifstream file(eventParticipantsFileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open event participants file");
	}
	std::string line;
	while (std::getline(file, line)) {
		size_t pos = line.find('|');
		if (pos == std::string::npos) continue; // Skip malformed lines
		std::string eventName = line.substr(0, pos);
		std::string participantName = line.substr(pos + 1);
		for (const auto& event : events) {
			if (event.getName() == eventName) {
				eventParticipants.emplace_back(event, participantName);
				break;
			}
		}
	}
}