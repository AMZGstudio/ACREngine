#include "ACREngine.h"

int main()
{
    // we create the screen, with the window title, dimensions, the text foreground, and background color. over here, its black text on a white background.
    initalize("Demo Text", 200, 100, 6, 6, Black, White); // TIP: write Default, for default foreground and background.

    //square coordinates.
    int x = 1, y = 1;
     
    // keep on running the game loop, as long as the escape key is not pressed.
    while (key(EscapeKey).pressed == false)
    {
        // draw a rectangle starting from x, and y, to x and y + 10, meaking the square 10 units wide.
        drawRectFilled(x, y, x + 10, y + 10, Blue);

        // check if any of the WASD keys are pressed, and move the x and y of the square accordingly.

        if (key(W).held) y--;
        if (key(S).held) y++;
        if (key(A).held) x--;
        if (key(D).held) x++;

        // render to screen, true means to clear the screen after rendering.
        render(true);
    }

    //close the API, (stops memory from leaking)
    return terminate();
}