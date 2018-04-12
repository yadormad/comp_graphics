#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

 class ObjParser
{
public:
	    vector <Point2D3D> points_v;
		vector <Point2D3D> points_vt;
		vector <Point2D3D> points_vn;
		list <Triangle> triangles;
public:
	void getPointsFromFile(string str1){
	string line;
		ifstream fin;
		fin.open(str1);
		vector <Point2D3D> vectorPoints_v;
		vector <Point2D3D> vectorPoints_vt;
		vector <Point2D3D> vectorPoints_vn;
		list <Triangle> list_triangles;
		Point2D3D point, point1, point2, point3;
		Triangle triangle;

		int j=0;
		string cur="",cur1="",cur2="",cur3="";
		
		
		while(getline(fin,line)){
			if(line[0]=='v'){
				if(line[1]==' '){
					j=2;
					while (line[j] == ' ') {
						j++;
					}
					cur="";
					while(line[j]!=' '){
						cur+=line[j];
						j++;
					}
					point.x=stod(cur);
					j++;
					cur="";
					while(line[j]!=' '){
						cur+=line[j];
						j++;
					}
					point.y=stod(cur);
					j++;
					cur="";
					while(j<line.size()){
						cur+=line[j];
						j++;
					}
					point.z=stod(cur);
					vectorPoints_v.push_back(point);
				}
				if(line[1]=='t'){
					j=2;
					while (line[j] == ' ') {
						j++;
					}
					cur="";
					while(line[j]!=' '){
						cur+=line[j];
						j++;
					}
					point.x=stod(cur);
					j++;
					cur="";
					while(line[j]!=' '){
						cur+=line[j];
						j++;
					}
					point.y=stod(cur);
					j++;
					cur="";
					while(j<line.size()){
						cur+=line[j];
						j++;
					}
					point.z=stod(cur);
					vectorPoints_vt.push_back(point);
				}
				if(line[1]=='n'){
					j=2;
					while (line[j] == ' ') {
						j++;
					}
					cur="";
					while(line[j]!=' '){
						cur+=line[j];
						j++;
					}
					point.x=stod(cur);
					j++;
					cur="";
					while(line[j]!=' '){
						cur+=line[j];
						j++;
					}
					point.y=stod(cur);
					j++;
					cur="";
					while(j<line.size()){
						cur+=line[j];
						j++;
					}
					point.z=stod(cur);
					vectorPoints_vn.push_back(point);
				}
			}
			if(line[0]=='f'){
				j = 1;
				while (line[j] == ' ') {
					j++;
				}
				cur="";
				while (line[j] != '/') {
					cur += line[j];
					j++;
				}
				triangle.a = vectorPoints_v[stod(cur)-1];
				while (line[j] != ' ') {
					j++;
				}
				j++;
				cur = "";
				while (line[j] != '/') {
					cur += line[j];
					j++;
				}
				triangle.b = vectorPoints_v[stod(cur)-1];
				while (line[j] != ' ') {
					j++;
				}
				j++;
				cur = "";
				while (line[j] != '/') {
					cur += line[j];
					j++;
				}
				triangle.c = vectorPoints_v[stod(cur)-1];
				list_triangles.push_back(triangle);
			}
			
			
		}
		points_v=vectorPoints_v;
		points_vt=vectorPoints_vt;
		points_vn=vectorPoints_vn;
		triangles= list_triangles;
        
	}
	
};