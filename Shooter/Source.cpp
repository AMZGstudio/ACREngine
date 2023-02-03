
#define SHOW_FPS
#define ALL_FONTS
#define ACRE_FULLSCREEN

#include "Audio.h"

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"

#define ACRE_GAMEPLAY
#include "../ACRE Files/ACRE_Gameplay.h"

#include "Board.hpp"
#include "Creds.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Over.hpp"

int main()
{
	initialize("Shooter Game!", 300, 200, 5, 5, Default, Default);

	aud.start();
	aud.addSound("firing", "../Sound Effects/bullet.wav");
	aud.addSound("music", "../Sound Effects/music.wav");
	aud.addSound("reload", "../Sound Effects/reload.wav");
	aud.addSound("empty", "../Sound Effects/empty_gun.wav");
	
	acre::Renderer renderer;
	acre::States states("menu");

	states.addState("board", (acre::State*)new Board(&renderer));
	states.addState("creds", (acre::State*)new Creds(&renderer));
	states.addState("menu", (acre::State*)new Menu(&renderer));
	states.addState("game", (acre::State*)new Game(&renderer));
	states.addState("over", (acre::State*)new Over(&renderer));

	while (states.isRunning())
	{
		renderer.clear();
		states.runState();
		renderer.draw();
		renderer.render();
	}
	
	return terminateACRE();
}

/*
TODO:

DONE: Add restart button in escape menu
DONE: make menu's work on hover, and only click once
DONE: Allow renderer class to be a global variable, without it breaking things

Add shaking to the screen.

add a message in the center of the screen, saying what wave it is.

make waves longer.

add zombie death sound effect, and zombie scream sound effect.

Make ACRE_GAMEPLAY work across multiple files.


*/

