# ConsoleEngine
A easy to use, game engine, that runs entirely in the console! its a single header file, which makes it very convenient to implement! the usage of the engine is as simple as possible, while also containing some advanced features! rendering is fast enough for real time games, at higher resolutions. if you are a beginner, or more advanced programmer, and you want to create a game, without having to learn complex graphics libraries, this is the perfect fit!

# What is it?
its a game engine, that uses the windows default libraries, to render text to the screen, and uses ANSI escape sequences to put colors on the screen. its got a whole lot of function that are easy to use, so you can worry about the game, and not the engine.

# How to use this?
Step 1) include this header in your code.
Step 2) Call (initalize(ScreenWidth, ScreenHeight, DefaultForegorund, DefaultBackground) with your desired info.)
Step 3) Draw to the screen. with any of the drawing functions.
Step 4) render to the screen, with the function: render(false).

Thats it!

# Code Preview
How to make a controlable square on the screen:
```C
#include "ConsoleEngine.h"

int main()
{
    // we create the screen, with the window title, the text foreground, and background color. over here, its white text on a cyan background.
    initalize("Demo", White, Cyan); // TIP: write None, for default foreground and background.
    
    //square coordinates.
    int x = 1, y = 1;
    
    // keep on running the game loop, as long as the escape key is not pressed.
    while(key(EscapeKey).pressed == false)
    {
        // draw a rectangle starting from x, and y, to x and y + 10, meaking the square 10 units wide.
        drawFilledRect(x, y, x+10, y+10, Default, Red);
        
        // check if any of the WASD keys are pressed, and move the x and y of the square accordingly.
        
        if(key(W).held) y--;
        if(key(S).held) y++;
        if(key(A).held) x--;
        if(key(D).held) x++;
        
        // render to screen, true means to clear the screen after rendering.
        render(true); 
    }
    
    //close the API, (stops memory from leaking)
    return terminate();
}
```
