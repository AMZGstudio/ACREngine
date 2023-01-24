#include "State.hpp"

States::States(std::string stateName) : states()
{
	currState = stateName;
	surface = createArea(Width(Screen), Height(Screen), Default, Default);
	setDefaultDrawArea(&surface);
}

void States::runState()
{
	states[currState]->runState(currState);
}

void States::setState(std::string name)
{
	currState = name;
}

void States::addState(std::string name, State* state)
{
	states[name] = state;
}

Area& States::getArea()
{
	return surface;
}
