#include <math.h>

#pragma once

class Point2D3D
{
	public:
	double x;
	double y;
	double z;
public:
	Point2D3D();
	Point2D3D(double x_, double y_, double z_){
	    x=x_;
		y=y_;
		z=z_;
	};
	Point2D3D(int x_,int y_,int z_){
	    x=x_;
		y=y_;
		z=z_;
	};
	Point2D3D(int x_,int y_){
	    x=x;
		y=y;
		z=0;
	};
	Point2D3D(double x_, double y_){
	    x=x_;
		y=y_;
		z=0;
	};

	void normalize() {
		double norm = sqrt(x * x + y * y + z * z);
		x /= norm;
		y /= norm;
		z /= norm;
	}

	friend Point2D3D operator-(Point2D3D left, Point2D3D right) {
		Point2D3D res(left.x - right.x, left.y - right.y, left.z - right.z);
		return res;
	}

	friend  Point2D3D operator^(Point2D3D left, Point2D3D right) {
		Point2D3D res(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
		return res;
	}

	friend double operator*(Point2D3D left, Point2D3D right) {
		double res = left.x*right.x + left.y*right.y + left.z*right.z;
		return res;
	}

	~Point2D3D(void);
};

