#define SHOW_FPS
#define SPRITE_PATH "../ACRE Sprites/"
#define FILE_NAME "harry.acre"

#include <math.h>
#include <time.h>

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"

#define ACRE_GUI
#include "../ACRE Files/ACRE_Gui.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

int main()
{
	// start ACRE engine
	initalize("New Version!", 190, 105, 6, 6, Default, VeryDarkGrey);

	Window* w = createWindow(2, 2, 45, 60, "Sprite Controls", true);

	Option* b1 = createButton(w, Centered, 4, w->width - 4, 9, "Zoom In");
	Option* b2 = createButton(w, Centered, 11, w->width - 4, 16, "Zoom Out");

	Option* text = createTextBox(w, 5, 18, "Zoom Scale: ", DefaultFont);
	Option* slider = createSlider(w, Centered, 30, w->width - 4, 34, 0);	
	
	Area spr = loadSprite(SPRITE_PATH FILE_NAME);
	AreaTrans at = createAT(spr, Width(Screen) / 2 - Width(spr) / 2, Height(Screen) / 2 - Height(spr) / 2);
	
	while (!key(Esc).pressed)
	{	
		calculateSlider(slider);
		if (!calculateWindow(w))
			calculateAT(&at);

		if (calculateButton(b1))
			slider->sliderVal += slider->sliderVal < 100 ? timePerSec(10) : 0;
		if (calculateButton(b2))
			slider->sliderVal -= slider->sliderVal > 1 ? timePerSec(10) : 0;

		drawAT(at);
		drawWindow(w, false);
		drawButton(b1, false);
		drawButton(b2, false);
		drawSlider(slider, false);
		drawTextBox(text, false);

		changeZoom(&at, Width(Screen)/2, Height(Screen)/2, map(slider->sliderVal, 0, 100, 1, 100), false);
		sprintf_s(text->title, TEXT_SIZE, "Zoom scale: %.2f\n\nFile name:\n%s\n\nFPS: %.2f", at.zoom, FILE_NAME, fps);
	
		render(true);
	}
	deleteArea(spr);

	return terminateACRE();
}