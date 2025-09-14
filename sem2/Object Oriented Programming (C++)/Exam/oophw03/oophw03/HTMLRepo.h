#pragma once
#include "FileRepo.h"
class HTMLRepo : public FileRepo
{
private:
	void head();
	void body();
	void end();
public:
	HTMLRepo() = default;
	HTMLRepo(const std::string fileName);
	void openFileInChosenFormat() override;
};

