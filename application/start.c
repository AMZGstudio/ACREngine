#include <stdio.h>
#include <Windows.h>

#define ACRE_START
#include "../acre files/ACREngine.h"


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    AllocConsole();

    HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    char* t = "Hello!";
    DWORD numWritten;
    
    initialize("Hello", 200, 100, 4, 4, Default, Pink);

    while (1)
    {


        render(true);
    }
    
    Sleep(10000);
    return 0;
}
