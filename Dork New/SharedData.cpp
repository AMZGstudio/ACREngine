#include "SharedData.h"

unsigned int SharedData::getState() const
{
	return state;
}

void SharedData::setState(unsigned int state)
{
	this->state = state;
}

bool SharedData::isRunning() const
{
	return runLoop;
}

void SharedData::setRunning(bool run)
{
	runLoop = run;
}

SharedData::SharedData()
{
	surface = createArea(Width(Screen), Height(Screen), Default, Default);
}
