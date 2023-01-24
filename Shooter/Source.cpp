#define SHOW_FPS
#define ALL_FONTS

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

#include "Game.h"
#include "Menu.h"
#include "Over.h"
#include "State.h"


int main()
{
	initalize("Shooter Game!", 300, 200, 3, 3, Default, Default);

	States states(menu);
	states.addState((State*)new Menu());
	states.addState((State*)new Game());
	states.addState((State*)new Over());

	while (true)
	{
		clear(states.getArea());
		states.setState(states.runState());

		sysDrawArea(0, 0, Screen, states.getArea());
		render(false);
	}
	return terminateACRE();
}

