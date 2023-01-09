#pragma once
#include <vector>
#include "../ACRE Files/ACREngine.h"

enum all_states { menu, game };

class State
{
public:
	virtual int runState() = 0;
};

class States
{
private:
	// vector of functions
	std::vector<State*> states;
	Area surface;
	int stateIndex;

public:
	States(int stateIndex);
	int runState();
	void setState(int index);
	void addState(State* state);
	Area& getArea();
};