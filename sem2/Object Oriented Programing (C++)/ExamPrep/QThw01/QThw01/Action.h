#pragma once
class Action
{
public:
	virtual ~Action() = default;
	// Method to execute the action
	virtual void executeUndo() = 0;
	// Method to undo the action
	virtual void executeRedo() = 0;
};

