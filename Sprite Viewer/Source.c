// causes "deprecation" issues, without this
#define _CRT_SECURE_NO_WARNINGS 1

// Allow the console to be resized
#define ACRE_ALLOW_RESIZE

#define ACRE_START
#include "../ACRE Files/ACREngine.h"

// Include all of the different ACRE Extensions
#define ACRE_TRANSFORM
#include "../ACRE Files/ACRE_Transform.h"

#define ACRE_GUI
#include "../ACRE Files/ACRE_Gui.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"


#define SPRITE_PATH "../ACRE Sprites/"
#define FILE_NAME "harry.acre"

int main()
{
	bool darkMode = true;

	// start ACRE engine
	initialize("New Version!", 190, 105, 6, 6, Default, VeryDarkGrey);

	// ~~~~~~~~~~~ Create Resources ~~~~~~~~~~~~~ //
	Window* w = createWindow(2, 2, 45, 60, "Sprite Controls", true);

	// ~~~~~~~~~~~~ Create Buttons ~~~~~~~~~~~~~~ //
	Option* b1 = createButton(w, Centered, 3,     w->width - 4, 8,  "Zoom In");
	Option* b2 = createButton(w, Centered, 10,    w->width - 4, 15, "Zoom Out");
	Option* b3 = createButton(w, w->width/2+1,18, w->width - 2, 23, "Change Color");

	// ~~~~~~~~ Create Text and Sliders ~~~~~~~~~ //
	Option* text = createTextBox(w, 3, 18, "Zoom Scale: ", DefaultFont);
	Option* slider1 = createSlider(w, Centered, 30, w->width - 4, 34, 0);	
	Option* slider2 = createSlider(w, Centered, 36, w->width - 4, 40, 0);
	
	// ~~~~~~~~ Create Transformed Area ~~~~~~~~~ //
	Area spr = loadSprite(SPRITE_PATH FILE_NAME);
	AreaTrans at = createAT(spr, Centered, Centered);


	// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~ //
	while (!key(Esc).pressed)
	{	
		// make the transformed area's zoom pivot around the center of the screen.
		setPivotAT(&at, Width(Screen) / 2, Height(Screen) / 2, true);
		
		// set the zoom of the transformed area, to be the value of the slider
		setZoomAT(&at, slider1->sliderVal);

		// calculate the window, and only if we weren't using the window
		// should we calculate the transformed area. (we dont want it to move while using the window)
		if (!calculateWindow(w))
		{
			calculateAT(&at);
			slider1->sliderVal = at.zoom;
		}

		// do calculations for buttons and sliders. (meaning let them check if they were pressed, etc.)
		calculateButton(b1);
		calculateButton(b2);
		calculateButton(b3);
		calculateSlider(slider1);
		calculateSlider(slider2);

		if (b1->held) 
			slider1->sliderVal += slider1->sliderVal < 100 ? timePerSec(10) : 0;
		
		if (b2->held) 
			slider1->sliderVal -= slider1->sliderVal > 1 ? timePerSec(10) : 0;
		
		if (b3->pressed)
		{
			defaultBackColor = darkMode ? Color(200,200,200) : VeryDarkGrey;
			darkMode = !darkMode;
		}

		at.opacity = map(slider2->sliderVal, 100, 1, 0, 1);

		drawAT(&at);
		drawWindow(w, darkMode);
		drawButton(b1, darkMode);
		drawButton(b2, darkMode);
		drawButton(b3, darkMode);
		drawTextBox(text, darkMode);
		drawSlider(slider1, darkMode);
		drawSlider(slider2, darkMode);

		sprintf_s(text->title, TEXT_SIZE, "File name:\n%s\n\nZoom scale: %.2f\nOpacity: %.3f\n\nFPS: %.2f", FILE_NAME, at.zoom, at.opacity, fps );
	
		render(true);
	}

	deleteArea(&spr);
	terminateACRE();
}