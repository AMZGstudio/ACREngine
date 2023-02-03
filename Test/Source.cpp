#define SHOW_FPS
#define ALL_FONTS

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"



int main()
{
	initialize("Shooter Game!", 300, 200, 3, 3, Default, Default);

	Area a = createArea(50, 50, Default, White);
	AreaTrans at1 = createAT(a, Centered, Centered);
	AreaTrans at2 = createAT(a, Centered, Centered);

	sysDrawCircle(25, 25, a, 20, Default, true, Default, Red);
	
	while (true)
	{
		calculateAT(&at1);

		if (key(Up).held) at1.opacity += timePerSec(0.5);
		if (key(Down).held) at1.opacity -= timePerSec(0.5);

		drawAT(&at2);
		drawAT(&at1);
		
		render(true);
	}
	return terminateACRE();
}

