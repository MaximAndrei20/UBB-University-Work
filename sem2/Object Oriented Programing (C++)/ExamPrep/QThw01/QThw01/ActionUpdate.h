#pragma once
#include "Action.h"
#include "Event.h"
#include "Repo.h"
class ActionUpdate :
    public Action
{
private:
	Event oldEvent;
	Event newEvent;
	Repo& repo;
public:
	ActionUpdate(const Event& oldEvent, const Event& newEvent, Repo& repo)
		: oldEvent{ oldEvent }, newEvent{ newEvent }, repo{ repo } {
	}
	~ActionUpdate() override = default;
	void executeUndo() override;
	void executeRedo() override;
};

