#include "Point2D3D.h"
#pragma once
class Matr
{
private:
	double** matrix;
public:
	Matr();
	double** getAsArr();
	void hollow();
	void rx(double angle);
	void ry(double angle);
	void rz(double angle);
	void shift(double* t);
	void cam(int img_size, int z_size);
	void view(Point2D3D eye, Point2D3D centr);
	double det();
	Matr trans();
	Matr minor();
	double getIJMinor(int i, int j);
	Matr inv();
	friend Matr operator^(Matr left, Matr right);
	friend Matr operator*(double left, Matr right);
	friend Point2D3D operator^(Matr left, Point2D3D right);
	~Matr();
};

