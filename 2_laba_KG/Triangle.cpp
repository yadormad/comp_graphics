#include "StdAfx.h"
#include "Triangle.h"


Triangle::Triangle(void)
{
}

Triangle::Triangle(Point2D3D a_, Point2D3D b_, Point2D3D c_, Point2D3D an_, Point2D3D bn_, Point2D3D cn_, Point2D3D at_, Point2D3D bt_, Point2D3D ct_)
{
	a = a_;
	b = b_;
	c = c_;
	an = an_;
	bn = bn_;
	cn = cn_;
	at = an_;
	bt = bn_;
	ct = cn_;
}

Triangle::Triangle(Point2D3D a_, Point2D3D b_, Point2D3D c_)
{
	a = a_;
	b = b_;
	c = c_;
}

Point2D3D * Triangle::pointsAsArr()
{
	Point2D3D pointArr[3];
	pointArr[0] = a;
	pointArr[1] = b;
	pointArr[2] = c;
	return pointArr;
}

void Triangle::getRect(int & minX, int & minY, int & maxX, int & maxY)
{
	Point2D3D* pointArr = pointsAsArr();
	for (int i = 0; i < 3; i++)
	{
		if (pointArr[i].x() < minX) {
			minX = pointArr[i].x();
		}
		if (pointArr[i].x() > maxX) {
			maxX = pointArr[i].x();
		}
		if (pointArr[i].y() < minY) {
			minY = pointArr[i].y();
		}
		if (pointArr[i].y() > maxY) {
			maxY = pointArr[i].y();
		}
	}
}

Triangle Triangle::transform(Matr matr, Matr inv)
{
	Triangle resTriangle;
	resTriangle.a = matr ^ a;
	resTriangle.b = matr ^ b;
	resTriangle.c = matr ^ c;
	an.normalize();
	bn.normalize();
	cn.normalize();
	resTriangle.an = inv^an;	
	resTriangle.bn = inv^bn;
	resTriangle.cn = inv^cn;
	resTriangle.at = at;
	resTriangle.bt = bt;
	resTriangle.ct = ct;
	return resTriangle;
}


Triangle::~Triangle(void)
{
}
