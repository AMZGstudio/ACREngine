#pragma once
#include <vector>
#include "../ACRE Files/ACREngine.h"

class State
{
public:
	virtual void runState() = 0;
};

class States
{
private:
	// vector of functions
	std::vector<State*> states;
	Area surface;

public:
	States();
	void runState(int stateIndex);
	void addState(State* state);
};