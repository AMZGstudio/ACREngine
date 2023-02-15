#define ACRE_START // only do this in the main file.
#include "../acre files/ACREngine.h"

void start()
{
    // we create the screen, with the window title, dimensions, the text foreground, and background color. over here, its black text on a white background.
    initialize("Demo Game", 200, 100, 4, 4, Black, White); // TIP: write Default, for default foreground and background.

    // circle coordinates.
    float x = 20, y = 20;

    // keep on running the game loop, as long as the escape key is not pressed.
    while (key(Esc).pressed == false)
    {
        // draw a circle on the screen, with the coordinates of x and y, and the radius of 15.
        // drawCircle(x, y, 15, Blue);

        // check if any of the WASD keys are pressed, and move the x and y of the circle accordingly.
        // timePerSec adds the correct amount to the coordinates, to make them move 40 units every second.
        if (key(W).held) y -= timePerSec(40);
        if (key(S).held) y += timePerSec(40);
        if (key(A).held) x -= timePerSec(40);
        if (key(D).held) x += timePerSec(40);

        // render to screen, true tells it to clear the screen after rendering.
        render(true);
    }

    //close the API, (stops memory from leaking)
    terminateACRE();
}