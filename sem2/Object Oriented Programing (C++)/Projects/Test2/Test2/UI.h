#pragma once
#include "Controller.h"
#include <iostream>

class UI
{
private:
	Controller& controller;
public:
	UI(Controller& controller) : controller(controller) {}
	void run();
	void printMenu();
	void addDepartment();
	void showAllDepartments();
	void showEfficientDepartments();
	void writeToFile();
};

