#pragma once
#include "FileRepo.h"
class CSVFileRepo : public FileRepo
{
private:
public:
	CSVFileRepo(std::string fileName);
	CSVFileRepo() = default;

	void openFileInChosenFormat() override;
};

