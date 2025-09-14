#include <iostream>
#include "UI.h"
#include "NeonatalUnit.h"
#include "Surgery.h"

void addTestData(Controller& controller) {
	controller.addDepartment(new NeonatalUnit("Neonatal Unit A", 5, 9.23));
	controller.addDepartment(new NeonatalUnit("Neonatal Unit B", 3, 8.05));
	controller.addDepartment(new NeonatalUnit("Neonatal Unit C", 4, 7.5));
	controller.addDepartment(new Surgery("Surgery A", 4, 10));
	controller.addDepartment(new Surgery("Surgery B", 5, 3));
	controller.addDepartment(new Surgery("Surgery C", 2, 5));
}

int main() {
	{
		Controller controller;
		addTestData(controller);
		UI ui(controller);
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}