#include "mochtest32.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	Repository repository;
	repository.readFromFile("data.txt");
	Service service(repository);
	GUI gui(service);
	gui.show();

    return app.exec();
}
