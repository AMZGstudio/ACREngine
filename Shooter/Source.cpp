#define SHOW_FPS
#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#include "Game.h"
#include "State.h"

int main()
{
	States states;
	initalize("Shooter Game!", 300, 200, 3, 3, Default, Default);

	states.addState((State*)new Game());

	while (true)
	{
		states.runState(0);
		render(true);
	}
	return terminateACRE();
}

