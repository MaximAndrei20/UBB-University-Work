#pragma once
#include <string>
class HospitalDepartment
{
protected:
	std::string hospitalName;
	int numberOfDoctors = 0;
public:
	virtual ~HospitalDepartment() = default;
	virtual bool isEfficient() = 0;
	virtual std::string toString() {
		return "Hospital Name: " + hospitalName + "\nNumber of Doctors: " + std::to_string(numberOfDoctors);
	}
	std::string getHospitalName() {
		return hospitalName;
	}
};

