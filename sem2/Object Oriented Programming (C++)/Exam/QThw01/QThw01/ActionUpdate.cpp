#include "ActionUpdate.h"

void ActionUpdate::executeUndo()
{
	this->repo.updateEvent(this->newEvent.getTitle(), this->oldEvent.getTitle(), this->oldEvent.getDescription(), this->oldEvent.getDateTime(), this->oldEvent.getNumberOfPeople(), this->oldEvent.getLink());
}
void ActionUpdate::executeRedo()
{
	this->repo.updateEvent(this->oldEvent.getTitle(), this->newEvent.getTitle(), this->newEvent.getDescription(), this->newEvent.getDateTime(), this->newEvent.getNumberOfPeople(), this->newEvent.getLink());
}
