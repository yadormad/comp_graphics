#include "StdAfx.h"
#include "Point2D3D.h"


Point2D3D::Point2D3D(void)
{
	dot[0] = 0;
	dot[1] = 0;
	dot[2] = 0;
}

Point2D3D::Point2D3D(double x_, double y_, double z_)
{
	dot[0] = x_;
	dot[1] = y_;
	dot[2] = z_;
}

Point2D3D::Point2D3D(int x_, int y_, int z_)
{
	dot[0] = x_;
	dot[1] = y_;
	dot[2] = z_;
}

Point2D3D::Point2D3D(int x_, int y_)
{
	dot[0] = x_;
	dot[1] = y_;
	dot[2] = 0;
}

Point2D3D::Point2D3D(double x_, double y_)
{
	dot[0] = x_;
	dot[1] = y_;
	dot[2] = 0;
}

double * Point2D3D::getDot()
{
	return dot;
}

double Point2D3D::x()
{
	return dot[0];
}

double Point2D3D::y()
{
	return dot[1];
}

double Point2D3D::z()
{
	return dot[2];
}

void Point2D3D::setX(double x)
{
	dot[0] = x;
}

void Point2D3D::setY(double y)
{
	dot[1] = y;
}

void Point2D3D::setZ(double z)
{
	dot[2] = z;
}

void Point2D3D::normalize()
{
	double norm = 0;

	for (int i = 0; i < 3; i++)
	{
		norm += dot[i] * dot[i];
	}

	for (int i = 0; i < 3; i++)
	{
		dot[i] /= sqrt(norm);
	}
}

Point2D3D::~Point2D3D(void)
{
}

Point2D3D operator-(Point2D3D left, Point2D3D right)
{
	Point2D3D res;
	for (int i = 0; i < 3; i++)
	{
		res.dot[i] = left.dot[i] - right.dot[i];
	}
	return res;
}

Point2D3D operator^(Point2D3D left, Point2D3D right)
{
	Point2D3D res(left.y() * right.z() - left.z() * right.y(), left.z() * right.x() - left.x() * right.z(), left.x() * right.y() - left.y() * right.x());
	return res;
}

double operator*(Point2D3D left, Point2D3D right)
{
	double res = 0;
	for (int i = 0; i < 3; i++)
	{
		res += left.dot[i] * right.dot[i];
	}
	return res;
}
