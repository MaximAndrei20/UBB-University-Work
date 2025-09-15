#include "NeonatalUnit.h"

bool NeonatalUnit::isEfficient()
{
	return averageGrade > 8.5;
}

std::string NeonatalUnit::toString()
{
	std::string result;
	result += "Type: Neonatal\n" + HospitalDepartment::toString();
	result += "\nAverage Grade: " + std::to_string(averageGrade) + "\n";
	return result;
}
