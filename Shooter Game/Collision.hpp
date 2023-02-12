#pragma once
class Collision
{
public:
	static bool c2cCollide(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);
	static bool p2cCollide(float px, float py, float cx, float cy, float cr);
};

