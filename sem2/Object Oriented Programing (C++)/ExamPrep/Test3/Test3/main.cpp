#include "Test3.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	Repository repository;
	repository.readFromFile();
	Service service(repository);
    GUI window(service);
    window.show();
    return app.exec();
}
