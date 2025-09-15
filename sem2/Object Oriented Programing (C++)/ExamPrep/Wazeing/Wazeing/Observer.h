#pragma once
class Observer
{
public:
	virtual ~Observer() = default;
	// Called when the subject notifies the observer of a change
	virtual void update() = 0;
};

