
#define ALL_FONTS
#define ACRE_SHOW_FPS
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Zombie Shooter, a game made by AMZG, to show off ACREngineV3's
	Abilities. Note, this uses another library by the OLC, for audio.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main()
{
	initialize("Shooter Game!", 300, 140, 5, 5, Default, Default);

	drawText(Centered, Centered, "Loading...", Pzim, White);
	render(true);

	aud.start();
	aud.addSound("firing", "Sound Effects/bullet.wav");
	aud.addSound("music", "Sound Effects/music.wav");
	aud.addSound("reload", "Sound Effects/reload.wav");
	aud.addSound("empty", "Sound Effects/empty_gun.wav");
	aud.addSound("dead", "Sound Effects/dead.wav");
	aud.addSound("background1", "Sound Effects/background1.wav");
	aud.addSound("background2", "Sound Effects/background2.wav");
	aud.addSound("background3", "Sound Effects/background3.wav");
	aud.addSound("background4", "Sound Effects/background4.wav");
	aud.addSound("background5", "Sound Effects/background5.wav");
	
	acre::Renderer renderer;
	acre::States states("menu");

	states.addState("board", (acre::State*)new Board(&renderer));
	states.addState("creds", (acre::State*)new Creds(&renderer));
	states.addState("menu", (acre::State*)new Menu(&renderer));
	states.addState("game", (acre::State*)new Game(&renderer));
	states.addState("over", (acre::State*)new Over(&renderer));

	while (states.isRunning())
	{
		renderer.reset();
		states.runState();
		renderer.draw();
		renderer.render();
	}
	
	terminateACRE();
}