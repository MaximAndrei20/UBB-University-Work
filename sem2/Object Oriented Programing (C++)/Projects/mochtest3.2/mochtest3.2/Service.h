#pragma once
#include "Repository.h"
class Service
{
private:
	Repository& repository;
public:
	Service(Repository& repo) : repository(repo) {}
	void addEquation(const Equation& equation) {
		repository.addEquation(equation);
	}
	std::vector<Equation> getEquations() const {
		return repository.getEquations();
	}
	void modify(int index, double a, double b, double c);
};

