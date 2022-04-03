# ConsoleEngine
A simple, but powerful engine, that you can create games in, or any simple GUI. It is written in C, and is very easy to understand. its not the fastest in the world, but its a great Engine to start with! It uses ASNI escapse sequences, meaning it is compatible with pretty much every platform.

# What is it?
This is a single header file, you drop it into your project and get started. it is entirely made in the console/terminal, meaning everything is drawn out of text, and ANSI escape codes, allowing for colors.

# How to use this?
Step 1) put this header in your code.
Step 2) Call initalize(ScreenWidth, ScreenHeight, DefaultForegorund, DefaultBackground) with your desired info.
Step 3) Draw to the screen. You can use drawSquare, drawLine, drawText, and drawChar. (documentation for each function further down)
Step 4) render the screen, with the function render().

Thats it!

# Code Preview
How to draw a red square to the screen:
```
#include "ConsoleEngine.h"
#include <conio.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 30

int main()
{
    // we initalize the screen with its width, its height, and then the foreground color and background color.
    // the foreground color is the color of the text, and the background color is the background of the text.
    initalize(SCREEN_WIDTH, SCREEN_HEIGHT, Default, Default);

    // Draw a square on the screen, the inputs are: x, y, (top left of the square), then x, y, (bottom right of the square)
    // And then the color foreground, and color background, the color of the text doesnt matter in this case, so we leave it
    // at Default, and we want the background to be red, so its like the pixel is set to Red.
    drawSquare(4, 4, 40, 20, Default, Red);

    //render the screen, (write to output buffer).
    render();

    //get a userInput, so it doesnt terminate immediatly.
    getch();
    return 0;
}
```
![image](https://user-images.githubusercontent.com/99887800/161416383-3151046c-66b7-4ce3-b98a-2e32597d536e.png)

