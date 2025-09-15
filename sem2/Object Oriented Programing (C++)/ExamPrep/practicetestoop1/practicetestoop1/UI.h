#pragma once
#include "Service.h"
class UI
{
private:
	Service& service;
public:
	UI(Service& service) : service{ service } {}
	void run();
	void printMenu();
	void addTestData();
	bool comparator(const Car& c1, const Car& c2);
};

