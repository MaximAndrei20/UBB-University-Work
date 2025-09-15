#include "PopularEventsWindow.h"
#include <QPainter>

PopularEventsWindow::PopularEventsWindow(Service& service, QWidget *parent)
	: QWidget(parent), service(service)
{
	ui.setupUi(this);
	populateList();
}

PopularEventsWindow::~PopularEventsWindow()
{}

void PopularEventsWindow::update()
{
	populateList();
}

void PopularEventsWindow::populateList()
{
	
}

