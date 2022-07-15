![ACREngine LogoCropped](https://user-images.githubusercontent.com/99887800/171085888-6702a6a6-8ec6-4ea1-8826-92683f1c3e60.png)
# ACREngine
A easy to use, game engine, that runs entirely in the console! its a single header file, which makes it very convenient to implement! the usage of the engine is as sim
ple as possible, while also containing some advanced features! rendering is fast enough for real time games, at higher resolutions. if you are a beginner, or more advanced programmer, and you want to create a game, without having to learn complex graphics libraries, this is the perfect fit!

# What is it?
its a game engine, that uses the windows default libraries, to render text to the screen, and uses ANSI escape sequences to put colors on the screen. its got a whole lot of function that are easy to use, so you can worry about the game, and not the engine.

# How to use this?
Step 1) include this header in your code.

Step 2) initalize the screen.

Step 3) draw things to the screen.

Step 4) render to the screen, with the function: render(false).

Thats it!
Note: you would probably like to create a game loop.

# Code Preview
How to make a controlable square on the screen:
```C
#define ACRE_START // only do this in the main file.
#include "ACREngine.h"

int main()
{
    // we create the screen, with the window title, dimensions, the text foreground, and background color. over here, its black text on a white background.
    initalize("Demo Text", 200, 100, 6, 6, Black, White); // TIP: write Default, for default foreground and background.

    //square coordinates.
    int x = 1, y = 1;

    // keep on running the game loop, as long as the escape key is not pressed.
    while (key(Esc).pressed == false)
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
```
# Things Created With The Engine

(Note all of these run smoothly)

Flappy Bird:
![flappyBird](https://user-images.githubusercontent.com/99887800/179171151-97c7386d-76d5-45dc-aa6a-cf3b0ad2a965.png)

Minesweeper:
![minesweeper](https://user-images.githubusercontent.com/99887800/179171143-468a4a0f-2260-4fe8-9ba0-d6014bb82ed0.png)

Sprite Editor:
![acrepainter](https://user-images.githubusercontent.com/99887800/179171091-4f64226d-1316-4d9f-bc12-0f3cf54687c0.png)

Pong:
![pong](https://user-images.githubusercontent.com/99887800/179171109-8e0b2815-bb96-48ef-b9b6-510c2842ee9a.png)

Snake:
![snake](https://user-images.githubusercontent.com/99887800/179171118-9d3b6317-b7f7-4cce-ac9b-b62a08141fd2.png)

Life:
![gameoflife](https://user-images.githubusercontent.com/99887800/179171127-ddb3a1ab-fa65-4cdf-960f-8ab6e34e433e.png)
