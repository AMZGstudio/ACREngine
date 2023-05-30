#pragma once

struct v2f;

struct v2i {
	int x, y;

	v2i();
	v2i(int x, int y);
	v2i(const v2i& other);

	v2i operator + (const v2i& other) const; 
	v2i operator - (const v2i& other) const; 
	v2i operator * (int c) const; 
	v2i operator / (int c) const; 

	operator v2f();
};

struct v2f {
	double x, y;

	v2f();
	v2f(double x, double y);
	v2f(const v2f& other);

	v2f operator + (const v2f& other) const;
	v2f operator - (const v2f& other) const; 
	v2f operator * (double c) const; 
	v2f operator / (double c) const; 

	operator v2i();
};