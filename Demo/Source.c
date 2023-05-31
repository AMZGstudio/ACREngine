#define ACRE_START 
#define ACRE_FONTS
#include "../ACREngine.h"
#include "../ACRE_Fonts.h"

int main()
{
	initalize("Demo Text", 100, 50, 6, 6, Black, White);
	Point p1 = { 0,0 }, p2 = { 0,0 }, p3 = { 0,0 };

	while (!key(Esc).pressed)
	{
		// if these keys are pressed, move a point, to the mouse point.
		if (key(W).held) p1.x = Mouse.x, p1.y = Mouse.y;
		if (key(S).held) p2.x = Mouse.x, p2.y = Mouse.y;
		if (key(D).held) p3.x = Mouse.x, p3.y = Mouse.y;

		drawText(Centered, Centered, "Hello World", Pzim, Default);
		drawTriangleFilled(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, Blue);

		render(true);
	}	
	return terminate();
}











/*
Changelog:

	Additions:
	- ACRE now compiles with GNU GCC compiler.
	- added VeryDarkGrey color.
	- opening ACRE file error, now has more info.
	- fonts are now defined with Font data type. allowing for more fonts.
	- added ACRE_Fonts extension, with more fonts to use for ACRE.
	- when specifying font, Default now needs to be DefaultFont.
	- added drawCircleFilled() function.
	- added drawTriangleFilled().

	Fixes:
	- new projects is VS dont need to define _CRT_SECURE_NO_WARNINGS anymore.
	- sysDrawCircle() can now draw filled.
	- sysDrawTriagle() now called sysDrawTriangle()
	- drawTriange() now called drawTriangle()
	- fixed issues when calling initalize again.
	- fixed terminate()

	Enhancements:
	- clearing the screen is now faster.
	- drawInt() is now drawNumber(), and can draw now draw ints, and floats, by specifying numDigits.
	- clearScreen() now faster. (uses memset).
	- foreground and background buffer now use unsigned char's instead of ints.
	- sysDrawTriangle(), Now works when filled.
*/