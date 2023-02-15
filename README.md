![ACREngine LogoCropped](https://user-images.githubusercontent.com/99887800/171085888-6702a6a6-8ec6-4ea1-8826-92683f1c3e60.png)
# ACREngine 
![](https://img.shields.io/badge/License-BSD-blue) ![](https://img.shields.io/badge/Language-C++-Green) ![](https://img.shields.io/badge/Language-C-Green)

ACREngine or AMZG Console Render Engine is a C & C++ Game/Render engine that uses the windows console. It was designed with simplicity in mind, and is very easy to get started with. ACRE is very modular, and (on its own) is just a single header file! In addition, ACRE has expansion packs for additional features.


# When to use it?
This game engine can be used for a variety of things. You can make fully fledged games that look like normal games, or you can make ascii art games. You can use ACRE as just a means to add colors to the console, or you can use it as a method to print to the console very fast. All of these things, in a simple library, allowing you to focus on the project, and not the engine! Whether a beginner or advanced programmer, creating a game couldn't be easier!

# Features
    ✅ Fullscreen onsole applications.
    ✅ resizable console window.
    ✅ user input handling.
    ✅ extremely simple API (with no boiler plate).
    ✅ no dlls, libs, etc. ACRE is a single file. 
    ✅ easy to use drawing routines. 
    ✅ custom image formats.
    ✅ text drawing routines (with different fonts as well).
    ✅ both compatible with C, and C++.
    ✅ compiles with MSVC, and gcc/g++

# How do I get started?
there are two methods to set everything up. You can use the included premake build method, that will setup a visual studio for you, or you can setup your project manually, and include ACRE yourself. If you are using visual studio the first method is recommended. 

## Premake mMthod (recommended)

:arrow_right: Clone the repository (or download zip): 
`git clone `

➡️ Run:
`setup.bat`

➡️ open the `ACREngine.sln` file with Visual Studio. 

➡️ That's it! write whatever code you would like in the default application.
_Note: you are given sample code to get started._

## DIY Method

if using visual studio, you must create a windows application project, and then include the header file named `"ACREngine.h"` found in the acre files folder.

# Compilation
Visual Studio: just hit build.
MinGW (gcc/g++): ______

# Disclaimer
ACREngine gives you control over everything, and therefore you are responsible for initializing the console, creating a main loop, etc. ACRE is "barebones" on its own, and therefore doesn't come with physics, state machine, etc. Therefore ACRE one of the extensions (ACRE_Gameplay.h) adds things like the state machine, advanced render, etc. 

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
# Games made in ACRE

Zombie shooter:

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
