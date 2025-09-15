#include "ActionDelete.h"

void ActionDelete::executeUndo()
{
	this->repo.addEventToData(this->event);
}
void ActionDelete::executeRedo()
{
	this->repo.deleteEvent(this->event.getTitle());
}
