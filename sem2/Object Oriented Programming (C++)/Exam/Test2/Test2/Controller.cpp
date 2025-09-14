#include "Controller.h"
#include <fstream>
#include <algorithm>

Controller::Controller()
{
}

Controller::~Controller()
{
	for (auto department : departments)
	{
		delete department;
	}
}

void Controller::addDepartment(HospitalDepartment* department)
{
	departments.push_back(department);
}

std::vector<HospitalDepartment*> Controller::getAllDepartments()
{
	return departments;
}

std::vector<HospitalDepartment*> Controller::getAllEfficientDepartments()
{
	std::vector<HospitalDepartment*> efficientDepartments;
	for (auto department : departments)
	{
		if (department->isEfficient())
		{
			efficientDepartments.push_back(department);
		}
	}
	return efficientDepartments;
}

void Controller::writeToFile(std::string filename)
{
	// Sort departments lexicographically by hospital name
	// Also print if department is efficient or not

	std::ofstream file(filename);
	if (!file.is_open())
	{
		return;
	}
	
	std::sort(departments.begin(), departments.end(), [](HospitalDepartment* a, HospitalDepartment* b) {
		return a->getHospitalName() < b->getHospitalName();
		});

	for (auto department : departments)
	{
		file << department->toString();
		if (department->isEfficient())
		{
			file << "Efficient" << std::endl << std::endl;
		}
		else
		{
			file << "Not Efficient" << std::endl << std::endl;
		}
	}
}
