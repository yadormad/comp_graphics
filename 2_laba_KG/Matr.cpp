#include "stdafx.h"
#include <math.h>
#include "Matr.h"
#include <iostream>

using namespace std;

Matr::Matr()
{
	matrix = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		matrix[i] = new double[4];
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
			if (j == i)
			{
				matrix[i][j] = 1;
			}
		}
	}
}

double ** Matr::getAsArr()
{
	return matrix;
}

void Matr::hollow()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void Matr::rx(double angle)
{
	matrix[1][1] = cos(angle);
	matrix[2][2] = matrix[1][1];
	matrix[1][2] = -sin(angle);
	matrix[2][1] = -matrix[1][2];
}

void Matr::ry(double angle)
{
	matrix[0][0] = cos(angle);
	matrix[2][2] = matrix[0][0];
	matrix[0][2] = sin(angle);
	matrix[2][0] = -matrix[0][2];
}

void Matr::rz(double angle)
{
	matrix[0][0] = cos(angle);
	matrix[1][1] = matrix[0][0];
	matrix[0][1] = -sin(angle);
	matrix[1][0] = -matrix[0][1];
}

void Matr::shift(double* t)
{
	for (int i = 0; i < 3; i++)
	{
		matrix[i][3] = t[i];
	}
}

void Matr::cam(int img_size, int z_size)
{
	matrix[0][0] = img_size / 2;
	matrix[1][1] = img_size / 2;
	matrix[2][2] = z_size / 2;
	matrix[0][3] = img_size / 2;
	matrix[1][3] = img_size / 2;
	matrix[2][3] = z_size / 2;
}

void Matr::view(Point2D3D eye, Point2D3D centr)
{
	Point2D3D up(0.0, 1.0, 0.0);
	Point2D3D z = (eye - centr);
	z.normalize();
	Point2D3D x = up ^ z;
	x.normalize();
	Point2D3D y = z ^ x;
	y.normalize();

	Matr minv;
	Matr tr;
	
	minv.matrix[0][0] = x.x();
	minv.matrix[0][1] = x.y();
	minv.matrix[0][2] = x.z();
	minv.matrix[1][0] = y.x();
	minv.matrix[1][1] = y.y();
	minv.matrix[1][2] = y.z();
	minv.matrix[2][0] = z.x();
	minv.matrix[2][1] = z.y();
	minv.matrix[2][2] = z.z();
	tr.matrix[0][3] = -centr.x();
	tr.matrix[1][3] = -centr.y();
	tr.matrix[2][3] = -centr.z();
	Matr res = minv ^ tr;
	this->matrix = res.matrix;
}

double Matr::det()
{
	double **tmp = new double*[4];
	for (int i = 0; i < 4; i++)
	{
		tmp[i] = new double[4];
		for (int j = 0; j < 4; j++)
		{
			tmp[i][j] = matrix[i][j];
		}
	}

	for (int k = 0; k < 3; k++)
	{
		for (int i = k + 1; i < 4; i++)
		{
			if (tmp[i][k] != 0)
			{
				for (int j = 0; j < 4; j++)
				{
					tmp[i][j] -= tmp[k][j] * tmp[i][k] / tmp[k][k];
				}
			}
		}
	}
	double det = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) {
			cout << tmp[i][j] << '\t';
		}
		cout << '\n';
		det *= tmp[i][i];
	}

	for (int i = 0; i < 4; i++)
		delete[] tmp[i];
	delete[] tmp;

	return det;
}

Matr Matr::trans()
{
	Matr res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.matrix[i][j] = matrix[j][i];
		}
	}
	return res;
}

double Matr::getIJMinor(int i, int j)
{
	Matr min;
	for (int m = 0; m < 4; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			if (m != i && n != j) 
			{
				min.matrix[m][n] = this->matrix[m][n];
			}
		}
	}
	double res = min.det()*pow(-1.0, i + j);
	return res;
}

Matr Matr::minor()
{
	Matr res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.matrix[i][j] = this->getIJMinor(i, j);
		}
	}
	res.trans();
	return res;
}

Matr Matr::inv()
{
	Matr inv;
	Matr source = this->trans();
	for (int k = 0; k < 3; k++)
	{
		for (int i = k + 1; i < 4; i++)
		{
			if (source.matrix[i][k] != 0)
			{
				for (int j = 0; j < 4; j++)
				{
					source.matrix[i][j] -= source.matrix[k][j] * source.matrix[i][k] / source.matrix[k][k];
					inv.matrix[i][j] -= source.matrix[k][j] * source.matrix[i][k] / source.matrix[k][k];
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			source.matrix[i][j] /= source.matrix[i][i];
			inv.matrix[i][j] /= source.matrix[i][i];
		}
	}
	source = source.trans();
	inv = inv.trans();
	for (int k = 0; k < 3; k++)
	{
		for (int i = k + 1; i < 4; i++)
		{
			if (source.matrix[i][k] != 0)
			{
				for (int j = 0; j < 4; j++)
				{
					source.matrix[i][j] -= source.matrix[k][j] * source.matrix[i][k] / source.matrix[k][k];
					inv.matrix[i][j] -= source.matrix[k][j] * source.matrix[i][k] / source.matrix[k][k];
				}
			}
		}
	}
	inv = inv.trans();
	return inv;
}

Matr::~Matr()
{
}

Matr operator^(Matr left, Matr right)
{
	Matr res;
	res.hollow();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				res.matrix[i][j] += left.matrix[i][k] * right.matrix[k][j];
			}
		}
	}
	return res;
}

Matr operator*(double left, Matr right)
{
	Matr res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.matrix[i][j] = right.matrix[i][j] * left;
		}
	}
	return res;
}

Point2D3D operator^(Matr left, Point2D3D right)
{
	double dot[4];
	for (int i = 0; i < 4; i++)
	{
		dot[i] = 0;
		for (int j = 0; j < 3; j++)
		{
			dot[i] += left.matrix[i][j] * right.getDot()[j];
		}
		dot[i] += left.matrix[i][3];
	}
	return Point2D3D(dot[0]/dot[3], dot[1] / dot[3], dot[2] / dot[3]);
}
