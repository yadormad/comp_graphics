#include <math.h>

#pragma once

class Point2D3D
{
	private:
		double dot[3];
public:
	Point2D3D();
	Point2D3D(double x_, double y_, double z_);
	Point2D3D(int x_,int y_,int z_);
	Point2D3D(int x_,int y_);
	Point2D3D(double x_, double y_);

	double* getDot();

	double x();
	double y();
	double z();

	void setX(double x);
	void setY(double y);
	void setZ(double z);

	void normalize();

	friend Point2D3D operator-(Point2D3D left, Point2D3D right);

	friend  Point2D3D operator^(Point2D3D left, Point2D3D right);

	friend double operator*(Point2D3D left, Point2D3D right);

	~Point2D3D(void);
};

