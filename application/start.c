#define ACRE_START 
#include "../acre files/ACREngine.h"

#define ACRE_TRANSFORM
#include "../acre files/ACRE_Transform.h"

#define ACRE_FONTS
#include "../acre files/ACRE_Fonts.h"

void start()
{
    initialize("Demo", 200, 100, 6, 6, Default, White);
    AreaTrans at = createAT(loadSprite("../hb.acre"), Centered, Centered);

    while (true)
    {   
        calculateAT(&at);
        drawAT(&at);
        render(true);
    }
    terminateACRE();
}
