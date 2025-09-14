#pragma once
#include "HospitalDepartment.h"
class Surgery : public HospitalDepartment
{
private:
	int numberOfPatients;
public:
	Surgery(std::string name, int doctors, int patients) {
		hospitalName = name;
		numberOfDoctors = doctors;
		numberOfPatients = patients;
	}
	~Surgery() override = default;
	bool isEfficient() override;
	std::string toString() override;
};

