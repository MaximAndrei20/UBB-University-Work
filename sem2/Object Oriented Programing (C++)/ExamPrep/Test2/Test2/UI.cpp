#include "UI.h"
#include "NeonatalUnit.h"
#include "Surgery.h"

void UI::run()
{
	while (true) {
		printMenu();
		std::string option;
		std::cin >> option;
		if (option == "1") {
			addDepartment();
		}
		else if (option == "2") {
			showAllDepartments();
		}
		else if (option == "3") {
			showEfficientDepartments();
		}
		else if (option == "4") {
			writeToFile();
		}
		else if (option == "0") {
			break;
		}
		else {
			std::cout << "Invalid option. Please try again." << std::endl;
		}
	}
}

void UI::printMenu()
{
	std::cout << "1. Add department" << std::endl;
	std::cout << "2. Display all departments" << std::endl;
	std::cout << "3. Display efficient departments" << std::endl;
	std::cout << "4. Write to file (ordered lexicografically)(show if efficient or not)" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void UI::addDepartment()
{
	std::string type;
	std::cout << "Enter the type of the department ( 1-NeonatalUnit / 2-Surgery ): ";
	std::cin >> type;
	std::string name;
	int numberOfDoctors;
	std::cout << "Enter the name of the hospital: ";
	std::cin >> name;
	std::cout << "Enter the number of doctors: ";
	std::cin >> numberOfDoctors;
	if (type == "1") {
		double averageGrade;
		std::cout << "Enter the average grade: ";
		std::cin >> averageGrade;
		controller.addDepartment(new NeonatalUnit(name, numberOfDoctors, averageGrade));
	}
	else if (type == "2") {
		int numberOfPatients;
		std::cout << "Enter the number of patients: ";
		std::cin >> numberOfPatients;
		controller.addDepartment(new Surgery(name, numberOfDoctors, numberOfPatients));
	}
	else {
		std::cout << "Invalid department type." << std::endl;
	}
}
void UI::showAllDepartments()
{
	std::vector<HospitalDepartment*> departments = controller.getAllDepartments();
	for (auto department : departments) {
		std::cout << department->toString() << std::endl;
	}
}

void UI::showEfficientDepartments()
{
	std::vector<HospitalDepartment*> efficientDepartments = controller.getAllEfficientDepartments();
	for (auto department : efficientDepartments) {
		std::cout << department->toString() << std::endl;
	}
}

void UI::writeToFile()
{
	std::string filename;
	std::cout << "Enter the filename: ";
	std::cin >> filename;

	this->controller.writeToFile(filename);
	std::cout << "Data written to file." << std::endl;
}

