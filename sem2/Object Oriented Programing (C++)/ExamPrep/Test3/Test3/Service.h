#pragma once
#include "Repository.h"
class Service
{
private:
	Repository& repository;
public:
	Service(Repository& repository) : repository(repository) {}
	std::vector<Weather> getAllWeathers() const {
		return this->repository.getAllWeathers();
	}
};

