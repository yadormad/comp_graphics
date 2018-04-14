#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "Triangle.h"
using namespace std;

 class ObjParser
{
public:
		list <Triangle> triangles;
public:
	void getPointsFromFile(string str1);
};