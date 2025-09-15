#include "ActionAdd.h"

void ActionAdd::executeUndo()
{
	this->repo.deleteEvent(this->event.getTitle());
}
void ActionAdd::executeRedo()
{
	this->repo.addEventToData(this->event);
}
