#include "stdafx.h"
#include "ObjParser.h"

void ObjParser::getPointsFromFile(string str1)
{
	string line;
	ifstream fin;
	fin.open(str1);
	vector <Point2D3D> vectorPoints_v;
	vector <Point2D3D> vectorPoints_vt;
	vector <Point2D3D> vectorPoints_vn;
	Point2D3D point;
	Triangle triangle;

	int j = 0;
	string cur = "";


	while (getline(fin, line)) {
		if (line[0] == 'v') {
			if (line[1] == ' ') {
				j = 2;
				while (line[j] == ' ') {
					j++;
				}
				cur = "";
				while (line[j] != ' ') {
					cur += line[j];
					j++;
				}
				point.setX(stod(cur));
				j++;
				cur = "";
				while (line[j] != ' ') {
					cur += line[j];
					j++;
				}
				point.setY(stod(cur));
				j++;
				cur = "";
				while (j<line.size()) {
					cur += line[j];
					j++;
				}
				point.setZ(stod(cur));
				vectorPoints_v.push_back(point);
			}
			if (line[1] == 't') {
				j = 2;
				while (line[j] == ' ') {
					j++;
				}
				cur = "";
				while (line[j] != ' ') {
					cur += line[j];
					j++;
				}
				point.setX(stod(cur));
				j++;
				cur = "";
				while (line[j] != ' ') {
					cur += line[j];
					j++;
				}
				point.setY(stod(cur));
				j++;
				cur = "";
				while (j<line.size()) {
					cur += line[j];
					j++;
				}
				point.setZ(stod(cur));
				vectorPoints_vt.push_back(point);
			}
			if (line[1] == 'n') {
				j = 2;
				while (line[j] == ' ') {
					j++;
				}
				cur = "";
				while (line[j] != ' ') {
					cur += line[j];
					j++;
				}
				point.setX(stod(cur));
				j++;
				cur = "";
				while (line[j] != ' ') {
					cur += line[j];
					j++;
				}
				point.setY(stod(cur));
				j++;
				cur = "";
				while (j<line.size()) {
					cur += line[j];
					j++;
				}
				point.setZ(stod(cur));
				vectorPoints_vn.push_back(point);
			}
		}
		if (line[0] == 'f') {
			j = 1;
			while (line[j] == ' ') {
				j++;
			}

			//read a v
			cur = "";
			while (line[j] != '/') {
				cur += line[j];
				j++;
			}
			triangle.a = vectorPoints_v[stod(cur) - 1];
			j++;
			//read a vt
			cur = "";
			while (line[j] != '/') {
				cur += line[j];
				j++;
			}
			triangle.at = vectorPoints_vt[stod(cur) - 1];
			j++;
			//read a vn
			cur = "";
			while (line[j] != ' ') {
				cur += line[j];
				j++;
			}
			triangle.an = vectorPoints_vn[stod(cur) - 1];
			j++;

			//read b v
			cur = "";
			while (line[j] != '/') {
				cur += line[j];
				j++;
			}
			triangle.b = vectorPoints_v[stod(cur) - 1];
			j++;
			//read b vt
			cur = "";
			while (line[j] != '/') {
				cur += line[j];
				j++;
			}
			triangle.bt = vectorPoints_vt[stod(cur) - 1];
			j++;
			//read b vn
			cur = "";
			while (line[j] != ' ') {
				cur += line[j];
				j++;
			}
			triangle.bn = vectorPoints_vn[stod(cur) - 1];
			j++;

			//read c v
			cur = "";
			while (line[j] != '/') {
				cur += line[j];
				j++;
			}
			triangle.c = vectorPoints_v[stod(cur) - 1];
			j++;
			//read c vt
			cur = "";
			while (line[j] != '/') {
				cur += line[j];
				j++;
			}
			triangle.ct = vectorPoints_vt[stod(cur) - 1];
			j++;
			//read c vn
			cur = "";
			while (line[j] != '\0') {
				cur += line[j];
				j++;
			}
			triangle.cn = vectorPoints_vn[stod(cur) - 1];
			triangles.push_back(triangle);
		}
	}
}

Triangle operator^(Matr matr, Triangle triag)
{
	return Triangle();
}
