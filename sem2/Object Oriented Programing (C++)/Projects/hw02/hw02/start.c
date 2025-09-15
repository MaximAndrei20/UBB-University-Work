/*
The company “Home SmartApps” have decided to design a new intelligent refrigerator. Besides the hardware, they need a software application to manage the refrigerator. Each Product that the fridge can store has a name, a category (one of dairy, sweets, meat or fruit), a quantity and an expiration date. The software application will provide the following functionalities:
(a) Add, delete or update a product. A product is uniquely identified by name and category. If a product that already exists is added, its quantity will be updated (the new quantity is added to the existing one).
(b) Display all products whose name contains a given string (if the string is empty, all products from the refrigerator are considered), and show them sorted ascending by the existing quantity.
(c) Display all products of a given category (if the category is empty, all types of food will be considered) whose expiration dates are close (expire in the following X days, where the value of X is user-provided).
(d) Provide multiple undo and redo functionality. Each step will undo/redo the previous operation performed by the user.
*/

#include "Product.h"
#include "Service.h"
#include "Repository.h"
#include "UI.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

void addData(UI* ui)
{
	addProduct(ui->service, "Milk", "Dairy", 10, "20.03.2025");
	addProduct(ui->service, "Cheese", "Dairy", 5, "21.03.2025");
	addProduct(ui->service, "Cheese", "Dairy", 8, "25.03.2025");
	addProduct(ui->service, "Yogurt", "Dairy", 7, "27.03.2026");
	addProduct(ui->service, "Apple", "Fruit", 10, "30.03.2027");
	addProduct(ui->service, "Banana", "Fruit", 5, "02.04.2030");
	addProduct(ui->service, "Orange", "Fruit", 7, "19.04.2019");
	addProduct(ui->service, "Chocolate", "Sweets", 10, "12.05.2025");
	addProduct(ui->service, "Candy", "Sweets", 5, "12.09.2029");
	addProduct(ui->service, "Cake", "Sweets", 7, "12.01.2030");
	addProduct(ui->service, "Chicken", "Meat", 10, "12.04.2050");
	addProduct(ui->service, "Pork", "Meat", 5, "12.10.2021");
	addProduct(ui->service, "Beef", "Meat", 7, "12.11.2023");
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	testFunctionalities();

	Repository* repo = createRepository();
	Service* service = createService(repo);
	UI* ui = createUI(service);
	
	addData(ui);
	startUI(ui);

	destroyUI(ui);
	destroyService(service);
	destroyRepository(repo);

	_CrtDumpMemoryLeaks();
	return 0;
}