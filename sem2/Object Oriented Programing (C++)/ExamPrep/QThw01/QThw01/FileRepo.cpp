#include "FileRepo.h"

FileRepo& FileRepo::operator=(const FileRepo& r)
{
	this->fileName = r.fileName;
	this->events = r.events;
	return *this;
}

std::string FileRepo::toCSV(Event e)
{
	std::stringstream ss;
	ss << e.getTitle() << "," << e.getDescription() << "," << e.getDateTime() << "," << e.getNumberOfPeople() << "," << e.getLink();
	return ss.str();
}

Event FileRepo::fromCSV(const std::string& line)
{
	int numberOfPeople = 0;
	std::string title, description, dateTime, link;
	std::stringstream ss(line);
	std::string temp;

	std::getline(ss, title, ',');
	std::getline(ss, description, ',');
	std::getline(ss, dateTime, ',');
	std::getline(ss, temp, ',');
	numberOfPeople = std::stoi(temp);
	std::getline(ss, link);

	Event e{ title, description, dateTime, numberOfPeople, link };
	EventValidator::validateEvent(e);
	
	return e;
}

std::string FileRepo::getFileName() const
{
	return this->fileName;
}

void FileRepo::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
}

void FileRepo::saveToFile() const
{
	std::ofstream file(this->fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + this->fileName);
	}
	for (const auto& event : this->events) {
		file << event << "\n";
	}
}

void FileRepo::loadFromFile()
{
	std::ifstream file(this->fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + this->fileName);
	}
	Event event;
	while (file >> event) {
		EventValidator::validateEvent(event);
		this->events.push_back(event);
	}
}
