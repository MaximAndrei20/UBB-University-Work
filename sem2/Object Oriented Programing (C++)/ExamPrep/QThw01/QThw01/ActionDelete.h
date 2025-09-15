#pragma once
#include "Action.h"
#include "Event.h"
#include "Repo.h"
class ActionDelete :
    public Action
{
private:
	Event event;
	Repo& repo;
public:
	ActionDelete(const Event& event, Repo& repo) : event{ event }, repo{ repo } {}
	~ActionDelete() override = default;
	void executeUndo() override;
	void executeRedo() override;
};

