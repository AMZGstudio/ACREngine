#include "State.hpp"

States::States(int stateIndex) : states()
{
	this->stateIndex = stateIndex;
	surface = createArea(Width(Screen), Height(Screen), Default, Default);
	setDefaultDrawArea(&surface);
}

int States::runState()
{
	return states[stateIndex]->runState();
}

void States::setState(int index)
{
	stateIndex = index;
}

void States::addState(State* state)
{
	states.push_back(state);
}

Area& States::getArea()
{
	return surface;
}
