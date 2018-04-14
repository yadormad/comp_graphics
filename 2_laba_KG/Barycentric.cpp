#include "StdAfx.h"
#include "Barycentric.h"

Barycentric::Barycentric(Triangle _triangle)
{
	triangle = _triangle;
}

bool Barycentric::belongs(double x, double y, double & z_buf)
{
	double lambda_0 = ((y - triangle.c.y()) * (triangle.b.x() - triangle.c.x()) - (x - triangle.c.x()) * (triangle.b.y() - triangle.c.y())) /
		((triangle.a.y() - triangle.c.y()) * (triangle.b.x() - triangle.c.x()) - (triangle.a.x() - triangle.c.x()) * (triangle.b.y() - triangle.c.y()));
	double lambda_1 = ((y - triangle.a.y()) * (triangle.c.x() - triangle.a.x()) - (x - triangle.a.x()) * (triangle.c.y() - triangle.a.y())) /
		((triangle.b.y() - triangle.a.y()) * (triangle.c.x() - triangle.a.x()) - (triangle.b.x() - triangle.a.x()) * (triangle.c.y() - triangle.a.y()));
	double lambda_2 = ((y - triangle.b.y()) * (triangle.a.x() - triangle.b.x()) - (x - triangle.b.x()) * (triangle.a.y() - triangle.b.y())) /
		((triangle.c.y() - triangle.b.y()) * (triangle.a.x() - triangle.b.x()) - (triangle.c.x() - triangle.b.x()) * (triangle.a.y() - triangle.b.y()));

	if (lambda_0 < 0 || lambda_1 < 0 || lambda_2 < 0)
	{
		return false;
	}
	double z = lambda_0 * triangle.a.z() + lambda_1 * triangle.b.z() + lambda_2 * triangle.c.z();
	if (z_buf < z)
	{
		z_buf = z;
		return true;
	}
	else
	{
		return false;
	}
}

Point2D3D Barycentric::getNorm(double x, double y)
{
	double lambda_0 = ((y - triangle.c.y()) * (triangle.b.x() - triangle.c.x()) - (x - triangle.c.x()) * (triangle.b.y() - triangle.c.y())) /
		((triangle.a.y() - triangle.c.y()) * (triangle.b.x() - triangle.c.x()) - (triangle.a.x() - triangle.c.x()) * (triangle.b.y() - triangle.c.y()));
	double lambda_1 = ((y - triangle.a.y()) * (triangle.c.x() - triangle.a.x()) - (x - triangle.a.x()) * (triangle.c.y() - triangle.a.y())) /
		((triangle.b.y() - triangle.a.y()) * (triangle.c.x() - triangle.a.x()) - (triangle.b.x() - triangle.a.x()) * (triangle.c.y() - triangle.a.y()));
	double lambda_2 = ((y - triangle.b.y()) * (triangle.a.x() - triangle.b.x()) - (x - triangle.b.x()) * (triangle.a.y() - triangle.b.y())) /
		((triangle.c.y() - triangle.b.y()) * (triangle.a.x() - triangle.b.x()) - (triangle.c.x() - triangle.b.x()) * (triangle.a.y() - triangle.b.y()));

	double xn = lambda_0 * triangle.an.x() + lambda_1 * triangle.bn.x() + lambda_2 * triangle.cn.x();
	double yn = lambda_0 * triangle.an.y() + lambda_1 * triangle.bn.y() + lambda_2 * triangle.cn.y();
	double zn = lambda_0 * triangle.an.z() + lambda_1 * triangle.bn.z() + lambda_2 * triangle.cn.z();
	Point2D3D res(xn, yn, zn);
	res.normalize();
	return res;
}
