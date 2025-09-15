#pragma once
#include "HospitalDepartment.h"
#include <vector>
#include <string>
class Controller
{
private:
	std::vector<HospitalDepartment*> departments;
public:
	Controller();
	~Controller();
	void addDepartment(HospitalDepartment* department);
	std::vector<HospitalDepartment*> getAllDepartments();
	std::vector<HospitalDepartment*> getAllEfficientDepartments();

	void writeToFile(std::string filename);
};

