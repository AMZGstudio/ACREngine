#include "State.h"

States::States() : states()
{
	surface = createArea(Width(Screen), Height(Screen), Default, Default);
}

void States::runState(int stateIndex)
{
	states[stateIndex]->runState();
}

void States::addState(State* state)
{
	states.push_back(state);
}
