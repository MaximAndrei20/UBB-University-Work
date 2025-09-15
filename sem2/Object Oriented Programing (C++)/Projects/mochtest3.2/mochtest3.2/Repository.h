#pragma once
#include <vector>
#include <string>
#include "Equation.h"
class Repository
{
private:
	std::vector<Equation> equations; // Vector to store equations
public:
	std::vector<Equation> getEquations() const { return equations; } // Get all equations
	void addEquation(const Equation& equation) { equations.push_back(equation); } // Add an equation
	void readFromFile(const std::string& filename); // Read equations from a file
	void modify(int index, double a, double b, double c);
		
};

