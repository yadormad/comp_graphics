#pragma once
#include "Triangle.h"
ref class ProjMatrix
{
private:
	double **obj_matr;
	double **cam_matr;
	double **view_matr;
public:
	ProjMatrix(int img_size,
		int z_size,
		double *obj_ang,
		double *obj_off,
		Point2D3D eye,
		Point2D3D centr);
	void transform(Triangle& triangle);
	void proj(Triangle& triangle, Point2D3D *coords);
};


