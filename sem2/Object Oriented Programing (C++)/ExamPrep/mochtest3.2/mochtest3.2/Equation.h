#pragma once
#include <utility>
#include <sstream>
class Equation
{
private:
	double a; // Coefficient of x^2
	double b; // Coefficient of x
	double c; // Constant term
public:
	Equation() : a(0), b(0), c(0) {} // Default constructor
	Equation(double a, double b, double c) : a(a), b(b), c(c) {}
	double getA() const { return a; }
	double getB() const { return b; }
	double getC() const { return c; }
	void setA(double value) { a = value; }
	void setB(double value) { b = value; }
	void setC(double value) { c = value; }
	std::pair<std::pair<double, double>, std::pair<double,double>> computeSolutions();
	std::string toString() const;

	friend std::istream& operator>>(std::istream& is, Equation& eq) {
		// format: a, b, c
		char comma;
		is >> eq.a >> comma >> eq.b >> comma >> eq.c;
		return is;
	}
};

