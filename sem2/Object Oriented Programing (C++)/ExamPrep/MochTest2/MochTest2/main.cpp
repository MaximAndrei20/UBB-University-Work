#include <iostream>
#include "UI.h"

int main() {
	{
		Service service;
		UI ui(service);
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}