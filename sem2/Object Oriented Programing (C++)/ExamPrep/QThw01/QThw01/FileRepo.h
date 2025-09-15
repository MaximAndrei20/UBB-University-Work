#pragma once
#include "Repo.h"
#include <string>
#include <sstream>
#include <exception>
#include <fstream>

class FileRepo :
    public Repo
{
protected:
	std::string fileName;
public:
	FileRepo() = default;
	FileRepo(std::string& fileName) : fileName(fileName) {}
	FileRepo& operator=(const FileRepo& r);
	static std::string toCSV(Event e);
	static Event fromCSV(const std::string& line);
	std::string getFileName() const;
	void setFileName(const std::string& fileName);
	void saveToFile() const;
	void loadFromFile();
	virtual void openFileInChosenFormat() = 0;
};

