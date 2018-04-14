#pragma once
#include "Triangle.h"
class ProjMatrix
{
private:
	Matr projMatr;
	Matr invMatr;
public:
	ProjMatrix(int img_size,
		int z_size,
		double *obj_ang,
		double *obj_off,
		Point2D3D eye,
		Point2D3D centr);
	Triangle transform(Triangle triangle);
};


