// 2_laba_KG.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Point2D3D.h"
#include "Triangle.h"
#include <iostream>
#include <clocale>
#include "ObjParser.h"
#include "Barycentric.h"
#include "tgaimage.h"
#include "ProjMatrix.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	double obj_ang[3];
	double obj_off[3];
	double eye[3];
	double centr[3];
	int img_size;
	cout << "Введите размер изображения\n";
	cin >> img_size;

	cout << "Введите углы поворота модели в радианах\n\tВокруг оси x:\n";
	cin >> obj_ang[0];
	cout << "\tВокруг оси y:\n";
	cin >> obj_ang[1];
	cout << "\tВокруг оси z:\n";
	cin >> obj_ang[2];

	cout << "Введите координаты смещения\n\tПо оси x:\n";
	cin >> obj_off[0];
	cout << "\tПо оси y:\n";
	cin >> obj_off[1];
	cout << "\tПо оси z:\n";
	cin >> obj_off[2];

	cout << "Введите координаты камеры\n\tПо оси x:\n";
	cin >> eye[0];
	cout << "\tПо оси y:\n";
	cin >> eye[1];
	cout << "\tПо оси z:\n";
	cin >> eye[2];

	cout << "Введите точку наблюдения\n\tПо оси x:\n";
	cin >> centr[0];
	cout << "\tПо оси y:\n";
	cin >> centr[1];
	cout << "\tПо оси z:\n";
	cin >> centr[2];

	ObjParser pars;
	pars.getPointsFromFile("african_head.obj");
	int width = img_size;
	int height = img_size;
	Point2D3D point_eye(eye[0], eye[1], eye[2]);
	Point2D3D point_centr(centr[0], centr[1], centr[2]);
	ProjMatrix p_matrix(img_size, 255, obj_ang, obj_off, point_eye, point_centr);

	TGAImage image(width, height, TGAImage::RGB);
	list<Triangle> ::iterator it;
	Point2D3D local_coor[3];
	Point2D3D light(0, 0, 1);
	double **z_buffer = new double*[width];
	for (int i = 0; i < width; i++)
	{
		z_buffer[i] = new double[height];
		for (int j = 0; j < height; j++)
		{
			z_buffer[i][j] = -INFINITY;
		}
	}


	for (it = pars.triangles.begin(); it != pars.triangles.end(); it++) {
		
		p_matrix.transform(*it);
		p_matrix.proj(*it, local_coor);
		//local_coor[0] = Point2D3D(((*it).a.x + 1.)*width / 2., ((*it).a.y + 1.)*height / 2., ((*it).a.z + 1.)*height / 2.);
		//local_coor[1] = Point2D3D(((*it).b.x + 1.)*width / 2., ((*it).b.y + 1.)*height / 2., ((*it).b.z + 1.)*height / 2.);
		//local_coor[2] = Point2D3D(((*it).c.x + 1.)*width / 2., ((*it).c.y + 1.)*height / 2., ((*it).c.z + 1.)*height / 2.);
		if (local_coor[0].y > local_coor[2].y) {
			swap(local_coor[0], local_coor[2]);
		}
		if (local_coor[0].y > local_coor[1].y) {
			swap(local_coor[0], local_coor[1]);
		}
		if (local_coor[1].y > local_coor[2].y) {
			swap(local_coor[0], local_coor[2]);
		}
		int minX = INFINITY;
		int minY = INFINITY;
		int maxX = -INFINITY;
		int maxY = -INFINITY;
		for (int i = 0; i < 3; i++) 
		{
			if (local_coor[i].x < minX) {
				minX = local_coor[i].x;
			}
			if (local_coor[i].x > maxX) {
				maxX = local_coor[i].x;
			}
			if (local_coor[i].y < minY) {
				minY = local_coor[i].y;
			}
			if (local_coor[i].y > maxY) {
				maxY = local_coor[i].y;
			}
		}
		Triangle local_triangle(local_coor[0], local_coor[1], local_coor[2]);
		Point2D3D n = ((*it).b - (*it).a)^((*it).c - (*it).a);
		n.normalize();
		double intensivity = n * light;
		if (intensivity > 0) {
			TGAColor color = TGAColor(intensivity * 255, intensivity * 255, intensivity * 255, 255);
			Barycentric bar(local_triangle);
			for (int j = minY; j <= maxY; j++)
			{
				for (int i = minX; i <= maxX; i++)
				{
					if (!(i > width || i < 0 || j > height || j < 0))
					{
						double _z = z_buffer[i][j];
						if (bar.belongs(i, j, _z))
						{
							z_buffer[i][j] = _z;
							image.set(i, j, color);
						}
					}
				}
			}
		}
	}
	image.flip_vertically();
	image.write_tga_file("output.tga");
	cin.get();
	return 0;
}




