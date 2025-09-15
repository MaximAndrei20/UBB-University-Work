#include "Equation.h"
#include <cmath>

std::pair<std::pair<double, double>, std::pair<double,double>> Equation::computeSolutions()
{
    std::pair<double, double> x1, x2;
    double delta = b * b - 4 * a * c;
    if (delta < 0) {
        delta = -delta;
		x1.first = -b / (2 * a);
		x1.second = sqrt(delta) / (2 * a);

		x2.first = -b / (2 * a);
		x2.second = -sqrt(delta) / (2 * a);
	}
	else {
		x1.first = (-b + sqrt(delta)) / (2 * a);
		x1.second = 0; 
		// No imaginary part for real solutions
		x2.first = (-b - sqrt(delta)) / (2 * a);
		x2.second = 0;

	}
	return std::make_pair(x1, x2);
}

std::string Equation::toString() const
{
	std::string str;
	if (a != 0) {
		str += std::to_string(a) + "*x^2";
	}
	if (b != 0) {
		if (!str.empty()) str += " + ";
		str += std::to_string(b) + "*x";
	}
	if (c != 0) {
		if (!str.empty()) str += " + ";
		str += std::to_string(c);
	}
	return str;
}
