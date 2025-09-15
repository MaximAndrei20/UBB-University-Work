#pragma once
#include "Service.h"
class UI
{
private:
	Service& service;

public:
	UI(Service& service) : service{ service } {}
	void run();
	void printAdminMenu();
	void printUserMenu();
	void writeToFile();
};

