![ACREngine LogoCropped](https://user-images.githubusercontent.com/99887800/171085888-6702a6a6-8ec6-4ea1-8826-92683f1c3e60.png)
# ACREngine
A simple and easy to use game/render engine for C and C++. ACRE runs entirely in the console/terminal, and doesn't rely on any additional dependencies. ACRE is a very modular game engine. Its a single header file, with extension files as well. usage of the engine is as simple as possible, while also containing advanced features! rendering at high resolutions provides high FPS, and at lower resolutions, fps can be in the thousands. Whether a beginner or advanced programmer, creating a game couldn't be easier!

# What is it?
its a game engine, but not exculsively, it can be used for normal console applications, with more features then you would get by just printing to the screen. ACRE uses the windows default libraries, to render text to the screen, and uses ANSI escape sequences to put colors on the screen. Tt's got dozens of drawing functions that are easy to use, as well as more advanced ones. This allows you to focus on the game, and not the engine behind it!
Check out the wiki, which explains fundemental concepts, that this game engine uses.

# How to use this?

Step 1) include this header in your code.
Step 2) initalize the screen.
Step 3) draw things to the screen memory.
Step 4) render to the console screen, with the function: render().

Thats it!
Note: you usually would create a game loop.

# Code Preview
How to make a controlable square on the screen:
```C

#define ACRE_START // only do this in the main file.
#include "../ACRE Files/ACREngine.h"

int main()
{
    // we create the screen, with the window title, dimensions, the text foreground, and background color. over here, its black text on a white background.
    initialize("Demo Game", 200, 100, 4, 4, Black, White); // TIP: write Default, for default foreground and background.

    // circle coordinates.
    float x = 20, y = 20;

    // keep on running the game loop, as long as the escape key is not pressed.
    while (key(Esc).pressed == false)
    {
        // draw a circle on the screen, with the coordinates of x and y, and the radius of 15.
        drawCircle(x, y, 15, Blue);

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
```
# Things Created With The Engine

(Note all of these run smoothly)

Tetris:
[tetris](https://user-images.githubusercontent.com/99887800/180656074-cdce0a86-dcd6-4bed-8709-dcf9b06bd744.png)

Flappy Bird:
[flappyBird](https://user-images.githubusercontent.com/99887800/179171151-97c7386d-76d5-45dc-aa6a-cf3b0ad2a965.png)

Minesweeper:
[minesweeper](https://user-images.githubusercontent.com/99887800/179171143-468a4a0f-2260-4fe8-9ba0-d6014bb82ed0.png)

Sprite Editor:
[acrepainter](https://user-images.githubusercontent.com/99887800/179171091-4f64226d-1316-4d9f-bc12-0f3cf54687c0.png)

Pong:
[pong](https://user-images.githubusercontent.com/99887800/179171109-8e0b2815-bb96-48ef-b9b6-510c2842ee9a.png)

Snake:
[snake](https://user-images.githubusercontent.com/99887800/179171118-9d3b6317-b7f7-4cce-ac9b-b62a08141fd2.png)

Life:
[gameoflife](https://user-images.githubusercontent.com/99887800/179171127-ddb3a1ab-fa65-4cdf-960f-8ab6e34e433e.png)
