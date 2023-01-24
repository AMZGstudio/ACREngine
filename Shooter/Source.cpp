#define SHOW_FPS
#define ALL_FONTS

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

#include "Game.hpp"
#include "Menu.hpp"
#include "Over.hpp"
#include "State.hpp"


int main()
{
	initialize("Shooter Game!", 300, 200, 3, 3, Default, Default);

	States states("menu");
	states.addState("menu", (State*)new Menu());
	states.addState("game", (State*)new Game());
	states.addState("over", (State*)new Over());

	while (true)
	{
		clear(states.getArea());
		states.runState();

		sysDrawArea(0, 0, Screen, states.getArea());
		render(false);
	}
	return terminateACRE();
}

