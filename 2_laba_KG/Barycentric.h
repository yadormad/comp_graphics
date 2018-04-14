
#include <vector>
#include <iostream>
#include "Triangle.h"

class Barycentric {

private:
	Triangle triangle;
public:
	Barycentric(Triangle _triangle);
	bool belongs(double x, double y, double& z_buf);
	Point2D3D getNorm(double x, double y);
};