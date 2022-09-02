#define ACRE_START
#include "../ACREngine.h"

#define ACRE_TRANSFORM
#include "../ACRE_Transform.h"

int main()
{
	Area a = loadSprite("../Sprites/oldMan.acre");

	flipArea(a);
	
	makeSprite(a, "../Sprites/oldManRight.acre");
}

