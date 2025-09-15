#pragma once
#include "Action.h"
#include "Event.h"
#include "Repo.h"
class ActionAdd :
    public Action
{
private:
	Event event;
	Repo& repo;
public:
	ActionAdd(const Event& event, Repo& repo) : event{ event }, repo{ repo } {}
	~ActionAdd() override = default;
	void executeUndo() override;
	void executeRedo() override;
};

