#define ACRE_FULLSCREEN
#define ACRE_ALLOW_RESIZE

#define ACRE_START 
#include "../acre files/ACREngine.h"

#define ACRE_FONTS
#include "../ACRE Files/ACRE_Fonts.h"

void start()
{
    initialize("Command Prompt", Default, Default, Default, Default, Default, Default);
    
    char text[100] = { 0 };
    bool on = true;
    float level = 0;

    while (true)
    {
        level += timePerSec(1);
        if (level >= 0.5)
            level = 0, on = !on;

        drawText(0, 0, "Microsoft Windows [Version 10.0.22623.1325]\n(c) Microsoft Corporation. All rights reserved.", DefaultFont, White);
        drawText(0, 3, "C:\\Users\\test0>", DefaultFont, White);

        textBoxInput(text, 100);
        drawText(16, 3, text, DefaultFont, Red);

        if (on)
        sysDrawPoint(16 + strlen(text), 3, Screen, Default, Default, Grey);

        render(true);
    }
    terminateACRE();
}
