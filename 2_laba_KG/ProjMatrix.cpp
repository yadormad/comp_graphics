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
	double rx[3][3];
	double ry[3][3];
	double rz[3][3];
	double tmp[3][3];
	//double obj_matr[3][4];
	//double cam_matr[3][3];

	obj_matr = new double*[3];
	cam_matr = new double*[3];
	view_matr = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		obj_matr[i] = new double[4];
		view_matr[i] = new double[3];
		obj_ang[i] = obj_ang[i] * M_PI / 180;
		for (int j = 0; j < 3; j++)
		{
			rx[i][j] = 0;
			ry[i][j] = 0;
			rz[i][j] = 0;
			tmp[i][j] = 0;
			obj_matr[i][j] = 0;
			view_matr[i][j] = 0;
		}
		obj_matr[i][3] = obj_off[i];
	}

	for (int i = 0; i < 3; i++)
	{
		cam_matr[i] = new double[4];
		for (int j = 0; j < 4; j++)
		{
			cam_matr[i][j] = 0;
		}
	}

	rx[0][0] = 1;
	ry[0][0] = cos(obj_ang[1]);
	rz[0][0] = cos(obj_ang[2]);
	rx[1][1] = cos(obj_ang[0]);
	ry[1][1] = 1;
	rz[1][1] = rz[0][0];
	rx[2][2] = rx[1][1];
	ry[2][2] = ry[0][0];
	rz[2][2] = 1;
	rx[1][2] = sin(obj_ang[0]);
	ry[2][0] = sin(obj_ang[1]);
	rz[0][1] = sin(obj_ang[2]);
	rx[2][1] = -rx[1][2];
	ry[0][2] = -ry[2][0];
	rz[1][0] = -rz[0][1];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++) 
			{
				tmp[i][j] += rx[i][k] * ry[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				obj_matr[i][j] += tmp[i][k] * rz[k][j];
			}
		}
	}
	cam_matr[0][0] = img_size/2;
	cam_matr[1][1] = img_size/2;
	cam_matr[2][2] = z_size / 2;
	cam_matr[0][3] = img_size/2;
	cam_matr[1][3] = img_size/2;
	cam_matr[2][3] = z_size / 2;

	Point2D3D up(0.0, 1.0, 0.0);
	Point2D3D z = (eye - centr);
	z.normalize();
	Point2D3D x = up ^ z;
	x.normalize();
	Point2D3D y = z ^ x;
	y.normalize();

}
void ProjMatrix::transform(Triangle& triangle)
{
	double x = 0;
	double y = 0;
	double z = 0;

	x = obj_matr[0][0] * triangle.a.x + obj_matr[0][1] * triangle.a.y + obj_matr[0][2] * triangle.a.z + obj_matr[0][3];
	y = obj_matr[1][0] * triangle.a.x + obj_matr[1][1] * triangle.a.y + obj_matr[1][2] * triangle.a.z + obj_matr[1][3];
	z = obj_matr[2][0] * triangle.a.x + obj_matr[2][1] * triangle.a.y + obj_matr[2][2] * triangle.a.z + obj_matr[2][3];
	triangle.a.x = x;
	triangle.a.y = y;
	triangle.a.z = z;

	x = obj_matr[0][0] * triangle.b.x + obj_matr[0][1] * triangle.b.y + obj_matr[0][2] * triangle.b.z + obj_matr[0][3];
	y = obj_matr[1][0] * triangle.b.x + obj_matr[1][1] * triangle.b.y + obj_matr[1][2] * triangle.b.z + obj_matr[1][3];
	z = obj_matr[2][0] * triangle.b.x + obj_matr[2][1] * triangle.b.y + obj_matr[2][2] * triangle.b.z + obj_matr[2][3];
	triangle.b.x = x;
	triangle.b.y = y;
	triangle.b.z = z;

	x = obj_matr[0][0] * triangle.c.x + obj_matr[0][1] * triangle.c.y + obj_matr[0][2] * triangle.c.z + obj_matr[0][3];
	y = obj_matr[1][0] * triangle.c.x + obj_matr[1][1] * triangle.c.y + obj_matr[1][2] * triangle.c.z + obj_matr[1][3];
	z = obj_matr[2][0] * triangle.c.x + obj_matr[2][1] * triangle.c.y + obj_matr[2][2] * triangle.c.z + obj_matr[2][3];
	triangle.c.x = x;
	triangle.c.y = y;
	triangle.c.z = z;
}
void ProjMatrix::proj(Triangle& triangle, Point2D3D* coords)
{
	double x, y, z;
	x = cam_matr[0][0] * triangle.a.x + cam_matr[0][1] * triangle.a.y + cam_matr[0][2] * triangle.a.z + cam_matr[0][3];
	y = cam_matr[1][0] * triangle.a.x + cam_matr[1][1] * triangle.a.y + cam_matr[1][2] * triangle.a.z + cam_matr[1][3];
	z = cam_matr[2][0] * triangle.a.x + cam_matr[2][1] * triangle.a.y + cam_matr[2][2] * triangle.a.z + cam_matr[2][3];

	coords[0] = Point2D3D(x, y, z);

	x = cam_matr[0][0] * triangle.b.x + cam_matr[0][1] * triangle.b.y + cam_matr[0][2] * triangle.b.z + cam_matr[0][3];
	y = cam_matr[1][0] * triangle.b.x + cam_matr[1][1] * triangle.b.y + cam_matr[1][2] * triangle.b.z + cam_matr[1][3];
	z = cam_matr[2][0] * triangle.b.x + cam_matr[2][1] * triangle.b.y + cam_matr[2][2] * triangle.b.z + cam_matr[2][3];

	coords[1] = Point2D3D(x, y, z);

	x = cam_matr[0][0] * triangle.c.x + cam_matr[0][1] * triangle.c.y + cam_matr[0][2] * triangle.c.z + cam_matr[0][3];
	y = cam_matr[1][0] * triangle.c.x + cam_matr[1][1] * triangle.c.y + cam_matr[1][2] * triangle.c.z + cam_matr[1][3];
	z = cam_matr[2][0] * triangle.c.x + cam_matr[2][1] * triangle.c.y + cam_matr[2][2] * triangle.c.z + cam_matr[2][3];

	coords[2] = Point2D3D(x, y, z);
}
