#pragma once
#include "Point2D3D.h"
#include "Matr.h"
class Triangle
{
public:
	Point2D3D a;
	Point2D3D b;
	Point2D3D c;
	Point2D3D an;
	Point2D3D bn;
	Point2D3D cn;
	Point2D3D at;
	Point2D3D bt;
	Point2D3D ct;
public:
	Triangle(void);
	Triangle(Point2D3D a_,Point2D3D b_,Point2D3D c_, Point2D3D an_,	Point2D3D bn_, Point2D3D cn_, Point2D3D at_, Point2D3D bt_, Point2D3D ct_);

	Triangle(Point2D3D a_, Point2D3D b_, Point2D3D c_);
	Point2D3D* pointsAsArr();
	void getRect(int& minX, int& minY, int& maxX, int& maxY);
	Triangle transform(Matr matr, Matr inv);

	~Triangle(void);
};

