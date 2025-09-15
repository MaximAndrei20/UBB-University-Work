#include <QtWidgets/QApplication>
#include "Service.h"
#include "PersonsWindow.h"
#include "PopularEventsWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	std::string personsFileName = "persons.txt";
	std::string eventsFileName = "events.txt";
	Repository repository(personsFileName,eventsFileName);
	Service service(repository);
	for (auto& person : service.getPersons()) {
		PersonsWindow* window = new PersonsWindow(service, &person);
		service.addObserver(window);
		window->show();
	}
	PopularEventsWindow* popularEventsWindow = new PopularEventsWindow(service);
	service.addObserver(popularEventsWindow);
	popularEventsWindow->show();
    return app.exec();
}
