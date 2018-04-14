#include "stdafx.h"
#include "ProjMatrix.h"

#define _USE_MATH_DEFINES
#include <math.h>


ProjMatrix::ProjMatrix(int img_size,
	int z_size,
	double *obj_ang,
	double *obj_off, 
	Point2D3D eye, 
	Point2D3D centr)
{
	for (int i = 0; i < 3; i++)
	{
		obj_ang[i] = obj_ang[i] * M_PI / 180;
	}

	Matr rx, ry, rz, cam, view, model;
	rx.rx(obj_ang[0]);
	ry.ry(obj_ang[1]);
	rz.rz(obj_ang[2]);
	cam.cam(img_size, z_size);
	view.view(eye, centr);

	model = rx ^ ry ^ rz;
	model.shift(obj_off);
	projMatr = cam ^ view ^ model;

	/*projMatr = (rx^ry) ^ rz;
	projMatr.shift(obj_off);
	projMatr = (projMatr ^ view) ^ cam;*/
	invMatr = projMatr.trans().inv();
}
Triangle ProjMatrix::transform(Triangle triangle)
{
	Triangle res;
	res = triangle.transform(projMatr, invMatr);
	return res;
}
