#include "Collision.hpp"
#include <cmath>

bool Collision::c2cCollide(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
    double d = sqrt((c1x - c2x) * (c1x - c2x)
        + (c1y - c2y) * (c1y - c2y));

    if (d <= c1r - c2r || d <= c2r - c1r || d < c1r + c2r)
        return true;
    
    return false;
}

bool Collision::p2cCollide(float px, float py, float cx, float cy, float cr)
{
    float distance = sqrt(((px-cx) * (px-cx)) + ((py - cy) * (py - cy)));

    if (distance <= cr)
        return true;
    
    return false;
}
