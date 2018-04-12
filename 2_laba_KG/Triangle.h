#pragma once
#include "Point2D3D.h"
class Triangle
{
public:
	Point2D3D a;
	Point2D3D b;
	Point2D3D c;
	Point2D3D an;
	Point2D3D bn;
	Point2D3D cn;
public:
	Triangle(void);
	Triangle(Point2D3D a_,Point2D3D b_,Point2D3D c_, Point2D3D an_,	Point2D3D bn_, Point2D3D cn_){
		a=a_;
		b=b_;
		c=c_;
		an = an_;
		bn = bn_;
		cn = cn_;
	};

	Triangle(Point2D3D a_, Point2D3D b_, Point2D3D c_) {
		a = a_;
		b = b_;
		c = c_;
	};

	~Triangle(void);
};

