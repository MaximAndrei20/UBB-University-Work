#include "Surgery.h"

bool Surgery::isEfficient()
{
    return numberOfPatients / numberOfDoctors >= 2;
}

std::string Surgery::toString()
{
	std::string result;
	result += "Type: Surgery\n" + HospitalDepartment::toString();
	result += "\nNumber of Patients: " + std::to_string(numberOfPatients) + "\n";
	return result;
}
