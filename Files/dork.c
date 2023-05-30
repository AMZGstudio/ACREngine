#define ACRE_START
#define SHOW_FPS
#define FONT_WIDTH 700
#include "ACREwindow.h"
#include "ACREngine.h"

int main()
{
	initalize("Dork Demo", 130, 60, 8, 10, Default, Default);

	while (true)
	{
		drawText(center(stringLength("DORK V3.3", EightBit), Screen, X)+1, 18, "DORK V3.3", EightBit, DarkGrey);
		drawText(center(stringLength("DORK V3.3", EightBit), Screen, X), 17, "DORK V3.3", EightBit, Default);
		
		drawLine(Centered, 27, stringLength("DORK V3.3", EightBit), 27, DarkGrey);
		sysDrawText(Centered, Centered, Screen, " Start Game ", Default, Black, White);

		render(true);
	}
	return terminate();
}