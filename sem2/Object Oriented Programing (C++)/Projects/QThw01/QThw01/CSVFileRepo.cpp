#include "CSVFileRepo.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Service.h"
#include <algorithm>


CSVFileRepo::CSVFileRepo(std::string fileName)
{
	this->fileName = fileName;
	this->loadFromFile();
}

void CSVFileRepo::openFileInChosenFormat()
{
    // create a new file and open it in excel
    std::string newFileName = "excel.csv";

    // First write all data to the file
    {
        std::ofstream file(newFileName);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + newFileName);
        }
        for (const auto& event : this->events) {
            file << event << "\n";
        }
        // file will be automatically closed when going out of scope
    }

    // Now open the file with Excel
    std::string command = "start excel.exe ./" + newFileName;
    int result = std::system(command.c_str());

    if (result != 0) {
        throw std::runtime_error("Failed to open file in Excel: " + newFileName);
    }
	
}
