#include "Repository.h"
#include <fstream>

void Repository::readFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	Equation eq;
	while (file >> eq) {
		equations.push_back(eq);
	}
}

void Repository::modify(int index, double a, double b, double c)
{
	equations[index].setA( a == -999 ? equations[index].getA() : a);
	equations[index].setB( b == -999 ? equations[index].getB() : b);
	equations[index].setC( c == -999 ? equations[index].getC() : c);
}
