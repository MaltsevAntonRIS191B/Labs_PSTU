
#pragma once
#include <iostream>
#include <glut.h>


#include <vector>
#include <string>
#include <iomanip>

using namespace std;


extern int WinW;
extern int WinH;
struct vertCoord
{
	int x, y;
};

class Graph
{
private:
	vector<int> vect;
	int Matrix[10][10];
public:
	Graph();
	~Graph();

	bool Empty() { if (vect.size() != 0) return false; else return true; }
	bool Full() { return (vect.size() == 10); }


	int getMatrixEl(int i, int j) { return Matrix[i][j]; }

	int GetAmountVerts() { return vect.size(); }
	int GetVertPos(const int& vertex);
	int Geted();   //matrix el

	void NewVertex(const int& vertex);
	void NewEdge(const int& vertex1, const int& vertex2, int weigth);

	void drawGraph();
};


extern Graph graph;
//////////////functions
void makeGraph();
void Vertex(int n);
void mouseClick(int button, int state, int x, int y);
void reshape(int w, int h);
void display();
void displaynew();
void Print_Matrix(int** matrix);






