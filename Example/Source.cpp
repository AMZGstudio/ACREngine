//#define SHOW_FPS
//#define ACRE_START // only do this in the main file.
//
//#include "../ACRE Files/ACREngine.h"
//
//class Object {
//
//public: // everything here we can use directly
//	float x, y;
//
//	Object() // constructor, it initalizes the things in the class
//	{
//		x = Width(Screen) / 2.0f;
//		y = Height(Screen) / 2.0f;
//	}
//
//	void drawObject()
//	{
//		drawRectFilled(x, y, x + 10, y + 10, Blue);
//	}
//};
//
//int main()
//{
//    // we create the screen, with the window title, dimensions, the text foreground, and background color. over here, its black text on a white background.
//    initalize("Demo Text", 200, 100, 5, 5, Black, White); // TIP: write Default, for default foreground and background.
//    
//	Object square;
//
//    // keep on running the game loop, as long as the escape key is not pressed.
//    while (key(Esc).pressed == false)
//    {
//		square.drawObject();
//      
//        // check if any of the WASD keys are pressed, and move the x and y of the square accordingly.
//        // timerPerSec adds the correct amount to the coordinates, to make them move 40 units every second.
//        if (key(W).held) square.y -= timePerSec(40);
//        if (key(S).held) square.y += timePerSec(40);
//        if (key(A).held) square.x -= timePerSec(40);
//        if (key(D).held) square.x += timePerSec(40);
//
//        // render to screen, true means to clear the screen after rendering.
//        render(true);
//    }
//
//    //close the API, (stops memory from leaking)
//    return terminateACRE();
//}
//









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
	bool darkMode = true;
	// start ACRE engine
	initalize("New Version!", 190, 105, 6, 6, Default, VeryDarkGrey);

	Window* w = createWindow(2, 2, 45, 60, "Sprite Controls", true);

	Option* b1 = createButton(w, Centered, 4, w->width - 4, 9, "Zoom In");
	Option* b2 = createButton(w, Centered, 11, w->width - 4, 16, "Zoom Out");
	Option* b3 = createButton(w, w->width/2+1, 18, w->width - 2, 23, "Change Color");

	Option* text = createTextBox(w, 5, 18, "Zoom Scale: ", DefaultFont);
	Option* slider = createSlider(w, Centered, 30, w->width - 4, 34, 0);	
	
	Area spr = loadSprite(SPRITE_PATH FILE_NAME);
	AreaTrans at = createAT(spr, Width(Screen) / 2 - Width(spr) / 2, Height(Screen) / 2 - Height(spr) / 2);
	
	while (!key(Esc).pressed)
	{	
		if (!calculateWindow(w))
			calculateAT(&at);

		calculateButton(b1);
		calculateButton(b2);
		calculateButton(b3);
		calculateSlider(slider);

		if (b1->held) slider->sliderVal += slider->sliderVal < 100 ? timePerSec(10) : 0;
		if (b2->held) slider->sliderVal -= slider->sliderVal > 1 ? timePerSec(10) : 0;
		if (b3->pressed)
		{
			defaultBackColor = darkMode ? Color(200,200,200) : VeryDarkGrey;
			darkMode = !darkMode;
		}

		drawAT(at);
		drawWindow(w, darkMode);
		drawButton(b1, darkMode);
		drawButton(b2, darkMode);
		drawButton(b3, darkMode);
		drawTextBox(text, darkMode);
		drawSlider(slider, darkMode);

		changeZoom(&at, Width(Screen)/2, Height(Screen)/2, map(slider->sliderVal, 0, 100, 1, 100), false);
		sprintf_s(text->title, TEXT_SIZE, "Zoom scale: %.2f\n\nFile name:\n%s\n\nFPS: %.2f", at.zoom, FILE_NAME, fps);
	
		render(true);
	}
	deleteArea(spr);
	
	terminateACRE();
}