#define ACRE_START
#define FPS_COUNTS 3
#define ACRE_SHOW_FPS
#include "../acre files/ACREngine.h"

void start()
{
	initialize("Title", 400, 300, 2, 2, Default, Default);

	while (true)
	{
		for (int y = 0; y < Height(Screen); y++)
			for (int x = 0; x < Width(Screen); x++)
				drawPixel(x, y, (x) % 256);


		render(true);
	}
}

/*

Benchmark after updating everything:
	around 2.03 ms with FPS_COUNTS 3

*/












/*#define ACRE_FULLSCREEN
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

void start()
{
	const char* fileName = "../harry.acre";
	bool darkMode = true;

	// start ACRE engine
	initialize("New Version!", 190, 105, 8, 8, Default, VeryDarkGrey);

	// ~~~~~~~~~~~ Create Resources ~~~~~~~~~~~~~ //
	Window* w = createWindow(2, 2, 45, 60, "Sprite Controls");

	// ~~~~~~~~~~~~ Create Buttons ~~~~~~~~~~~~~~ //
	Option* b1 = createButton(w, Centered, 3, w->width - 4, 5, "Zoom In");
	Option* b2 = createButton(w, Centered, 10, w->width - 4, 5, "Zoom Out");
	Option* b3 = createButton(w, w->width / 2 + 1, 18, w->width / 2 - 2, 7, "Change Color");

	// ~~~~~~~~ Create Text and Sliders ~~~~~~~~~ //
	Option* text = createTextBox(w, 3, 18, "Zoom Scale: ", DefaultFont);
	Option* slider1 = createSlider(w, Centered, 30, w->width - 4, 5, 1);
	Option* slider2 = createSlider(w, Centered, 36, w->width - 4, 5, 1);

	// ~~~~~~~~ Create Transformed Area ~~~~~~~~~ //
	Area spr = loadSprite(fileName);
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
		if (calculateButton(b1))
			slider1->sliderVal += slider1->sliderVal < 100 ? timePerSec(10) : 0;
		
		if (calculateButton(b2))
			slider1->sliderVal -= slider1->sliderVal > 1 ? timePerSec(10) : 0;

		calculateButton(b3);
		calculateSlider(slider1);
		calculateSlider(slider2);

		at.opacity = map(slider2->sliderVal, 100, 1, 0, 1);
		if (b3->wasPressed)
		{
			defaultBackColor = darkMode ? Color(200, 200, 200) : VeryDarkGrey;
			darkMode = !darkMode;
		}

		drawAT(&at);
		drawWindowAndContents(w, darkMode);

		sprintf_s(text->title, TEXT_SIZE, "File name:\n%s\n\nZoom scale: %.2f\nOpacity: %.3f\n\nFPS: %.2f", fileName, at.zoom, at.opacity, fps);

		render(true);
	}

	deleteArea(&spr);
	terminateACRE();
}*/