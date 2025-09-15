#pragma once
#include "HospitalDepartment.h"


class NeonatalUnit : public HospitalDepartment
{
public:
	NeonatalUnit(std::string name, int doctors, double averageGrade) {
		hospitalName = name;
		numberOfDoctors = doctors;
		this->averageGrade = averageGrade;
	}
	~NeonatalUnit() override = default;
	double averageGrade;
	bool isEfficient() override;
	std::string toString() override;
};

