#include <QtWidgets/QApplication>
#include "DriverWindow.h" 
#include "MapWindow.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	Repository repository{ "drivers.txt", "reports.txt" };
	Service service(repository);
	
	for (auto& driver : service.getDrivers()) {
		DriverWindow* driverWindow = new DriverWindow(service, &driver);
		service.addObserver(driverWindow);
		driverWindow->show();
	}

	MapWindow* mapWindow = new MapWindow(service);
	service.addObserver(mapWindow);
	mapWindow->show();

	return app.exec();
}
