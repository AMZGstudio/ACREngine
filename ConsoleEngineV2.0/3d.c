#include "ACREngine.h"
#include <math.h>

typedef struct p3d {
	int x, y, z;
} p3d;

typedef struct triangle {
	p3d p[3];
} triangle;

typedef struct mat4x4 {
	float m[4][4];
} mat4x4;

p3d multilpyMatrixVector(p3d i, mat4x4 m)
{
	p3d o;
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{

		o.x /= w; o.y /= w; o.z /= w;
	}
	o.x = 0;
	o.y = 0;
	o.z = 0;
	return o;
}

int main()
{
	initalize("3D Demo", 256, 240, 3, 3, Default, Default);
	triangle cubeTris[12] = {
		//SOUTH
		{0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,     1.0f, 1.0f, 0.0f },
		{0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,     1.0f, 0.0f, 0.0f },

		//EAST
		{1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,     1.0f, 1.0f, 1.0f },
		{1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f, 1.0f },

		//NORTH
		{1.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f },
		{1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f },

		//WEST
		{0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 1.0f,     1.0f, 1.0f, 0.0f },
		{0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 0.0f },

		//TOP
		{0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f },
		{0.0f, 1.0f, 0.0f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 0.0f },

		//BOTTOM
		{1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f },
		{1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f }
	
	};
	
	//projection matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fFovRad = 1.0f / tanf(fFov * 0.05f / 180.0f * 3.14159f);
	float fAspectRatio = (float)height(Screen) / (float)width(Screen);
	
	mat4x4 matProj;
	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;

	float offset = 0.5f;
	float screenX = 0.2f;

	float fTheta = 0.0f;
	
	while (true)
	{
		if (key(W).held) screenX += 0.03f;
		if (key(Q).held) screenX -= 0.03f;
		//if (key(S).held) fFov -= 0.05f;
		//if (key(A).held) fFov += 0.05f;
		mat4x4 matRotZ, matRotX;
		fTheta += 10.0f;

		//rotation Z
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		//rotation X
		matRotX.m[0][0] = 1;
		matRotX.m[0][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][0] = sinf(fTheta * 0.5f);
		matRotX.m[1][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;

		for (int i = 0; i < 12; i++)
		{
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

			//rotated Z
			triRotatedZ.p[0] = multilpyMatrixVector(cubeTris[i].p[0], matRotZ);
			triRotatedZ.p[1] = multilpyMatrixVector(cubeTris[i].p[1], matRotZ);
			triRotatedZ.p[2] = multilpyMatrixVector(cubeTris[i].p[2], matRotZ);

			//rotated X
			triRotatedZX.p[0] = multilpyMatrixVector(triRotatedZ.p[0], matRotX);
			triRotatedZX.p[1] = multilpyMatrixVector(triRotatedZ.p[1], matRotX);
			triRotatedZX.p[2] = multilpyMatrixVector(triRotatedZ.p[2], matRotX);

			triTranslated = triRotatedZX;
			triTranslated.p[0].z = triRotatedZX.p[0].z + offset;
			triTranslated.p[1].z = triRotatedZX.p[1].z + offset;
			triTranslated.p[2].z = triRotatedZX.p[2].z + offset;

			triProjected.p[0] = multilpyMatrixVector(triTranslated.p[0], matProj);
			triProjected.p[1] = multilpyMatrixVector(triTranslated.p[1], matProj);
			triProjected.p[2] = multilpyMatrixVector(triTranslated.p[2], matProj);
			
			//scale
			triProjected.p[0].x += 1.0f, triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f, triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f, triProjected.p[2].y += 1.0f;

			triProjected.p[0].x *= screenX * (float)width(Screen);
			triProjected.p[0].y *= screenX * (float)height(Screen);
			
			triProjected.p[1].x *= screenX * (float)width(Screen);
			triProjected.p[1].y *= screenX * (float)height(Screen);

			triProjected.p[2].x *= screenX * (float)width(Screen);
			triProjected.p[2].y *= screenX * (float)height(Screen);
			
			drawTriange(
				triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y, White);
		}
		
		render(true);
	}
	return terminate();
}