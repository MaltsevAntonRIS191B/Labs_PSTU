#include "Graph.h"
using namespace std;

Graph graph;

vector<pair<int, int>> al;
vector<int> al2;

bool flag = false;


int Radius;

vertCoord cor[11];





void makeGraph()
{
	flag = false;
	int v, e, V1, t, w;
	cout << "Kоличество вершин в графе: "; cin >> v;
	cout << "Kоличество ребер в графе: "; cin >> e;
	for (int i = 1; i <= v; i++) {

		graph.NewVertex(i);
	}
	for (int i = 0; i < e; i++)
	{
		cout << "Исходная вершина: "; cin >> V1;
		cout << "Конечная вершина: "; cin >> t;
		cout << "Вес ребра: "; cin >> w;
		graph.NewEdge(V1, t, w);
	}
	cout << endl;

}









Graph::Graph()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Matrix[i][j] = 0;
		}

	}
}

Graph::~Graph()
{ }

int Graph::GetVertPos(const int& vertex)
{
	for (size_t i = 0; i < vect.size(); i++)
	{
		if (vect[i] == vertex)
			return i;
	}
	return -1;
}

void Graph::NewVertex(const int& vertex)
{
	if (!Full())
		vect.push_back(vertex);
	else
	{
		cout << "Ошибка " << endl;
		return;
	}
}

void Graph::NewEdge(const int& vertex1, const int& vertex2, int weight)
{
	if (weight < 1)
	{
		cout << "\nОшибка\n";
		return;
	}
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))						//если вершины есть в графе
	{
		int vertPos1 = GetVertPos(vertex1);												//находим позиции вершин
		int vertPos2 = GetVertPos(vertex2);
		if (Matrix[vertPos1][vertPos2] != 0 && Matrix[vertPos2][vertPos1] != 0)	//если между ними уже есть ребро
		{
			cout << "Ошибка" << endl;
			return;
		}
		else																			//иначе добавляем ребро
		{
			Matrix[vertPos1][vertPos2] = weight;
		}
	}
	else
	{
		cout << "Ошибка " << endl;
		return;
	}
}

int Graph::Geted()
{
	int edges = 0;
	for (int i = 0; i < vect.size(); i++)
		for (int j = 0; j < vect.size(); j++)
			if (Matrix[i][j] > 0)
				edges++;
	return edges;
}

int** New_Matrix()
{
	int n = graph.GetAmountVerts();
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int elem = graph.getMatrixEl(i, j);
			if (elem == 0 or i == j)
				matrix[i][j] = -1;
			else
				matrix[i][j] = elem;
		}
	}
	cout << "Начальная матрица: \n";
	Print_Matrix(matrix);
	return matrix;
}

int* min(int* line, int n)
{
	int min = 1000000;
	for (int j = 0; j < n; j++)
		if (line[j] >= 0 && line[j] < min)
			min = line[j];
	for (int j = 0; j < n; j++)
		if (line[j] >= 0)
			line[j] -= min;
	return line;
}

void Print_Matrix(int** matrix)
{
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(4) << matrix[i][j];
		cout << endl;
	}
}

int** Reduct_Matrix(int** oldmatrix)
{
	int** matrix = oldmatrix;
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
		matrix[i] = min(matrix[i], n);
	for (int i = 0; i < n; i++)
	{
		int min = 1000000;
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0 && matrix[j][i] < min)
				min = matrix[j][i];
		}
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0)
				matrix[j][i] -= min;
		}
	}
	cout << "\nРедуцированная матрица: \n";
	Print_Matrix(matrix);
	return matrix;
}

int** Matrix2(int** oldmatrix)
{
	int n = graph.GetAmountVerts();
	int** matrix = Reduct_Matrix(oldmatrix);
	int max = -1;
	int line = 0, column = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				int minLine = 1000000;
				int minColumn = 1000000;
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] != -1 && k != j && matrix[i][k] < minLine)
						minLine = matrix[i][k];
				}
				for (int k = 0; k < n; k++)
				{
					if (matrix[k][j] != -1 && k != i && matrix[k][j] < minColumn)
						minColumn = matrix[k][j];
				}
				if (max < minColumn + minLine)
				{
					max = minColumn + minLine;
					line = i;
					column = j;
				}
			}
		}
	}

	pair<int, int> p;
	p.first = line + 1;
	p.second = column + 1;
	al.push_back(p);

	matrix[line][column] = -1;
	matrix[column][line] = -1;

	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = -1;
		matrix[i][column] = -1;
	}
	cout << endl;
	cout << "Матрица после удаления 0 с наибольшей оценкой: \n";
	Print_Matrix(matrix);
	cout << "\nПромежуточные отрезки путей: ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i].first << " -> " << al[i].second << "   ";
	cout << endl;
	return matrix;
}

void Print_Result()
{
	int second = al[0].second;
	int i = 2;
	al2.push_back(al[0].first);
	al2.push_back(al[0].second);
	while (i != graph.GetAmountVerts() + 1)
		for (int j = 1; j < graph.GetAmountVerts(); j++)
			if (al[j].first == second)
			{
				second = al[j].second;
				al2.push_back(second);
				i++;
			}
	cout << "Ответ: ";
	for (int i = 0; i < al2.size(); i++)
	{
		cout << al2[i];
		if (i != al2.size() - 1)
			cout << " -> ";
	}
	int sum = 0;
	for (int i = 0; i < al.size(); i++)
	{
		int line = al[i].first - 1;
		int column = al[i].second - 1;
		sum += graph.getMatrixEl(line, column);
	}
	cout << "\nS = " << sum << endl;;
}


void ButtonTask()
{

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2i(50, WinH - WinH / 7 - 20);
	glVertex2i(50, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - WinH / 7 - 20);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(50, WinH - WinH / 7 - 20);
	glVertex2i(50, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 7));
	glVertex2i(WinW / 7, WinH - WinH / 7 - 20);
	glEnd();
	string name = "        Salesman";
	glRasterPos2i(WinW / 19, 0.77 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, name[i]);
}

void Text(int text, int x1, int y1)
{
	glColor3f(0.0, 0.0, 0.0);
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(text);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void LineTo(int text, int x0, int y0, int x1, int y1) //ребро ориентированного взвешенного графа
{
	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	Text(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + Radius * vx;
	y1 = y1 + Radius * vy;

	glColor3i(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
	glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	glEnd();
}
void LineDown(int text, int x0, int y0, int x1, int y1) //ребро ориентированного взвешенного графа
{
	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	Text(text, (x0 + x1) / 2 - 10, (y0 + y1) / 2 - 10);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + Radius * vx;
	y1 = y1 + Radius * vy;

	glColor3i(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
	glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	glEnd();
}


void setCoords(int i, int n)
{
	int R_;
	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		Radius = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - Radius - 10;
	}
	else
	{
		Radius = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - Radius - 10;
	}
	float theta = 2.0f * 3.1415926f * i / n;
	int y1 = R_ * cos(theta) + y0;
	int x1 = R_ * sin(theta) + x0;
	cor[i].x = x1;
	cor[i].y = y1;
}

bool Salesman_Check(int** matrix)
{
	if (graph.Empty())
		return false;
	for (int i = 0; i < graph.GetAmountVerts(); i++)
	{
		int cnt = 0;
		for (int j = 0; j < graph.GetAmountVerts(); j++)
		{
			if (matrix[i][j] > 0)
				cnt++;
		}
		if (cnt < 1)
			return false;
	}
	return true;
}

void mouseClick(int button, int state, int x, int y)
{

	if (x >= 50 and x <= (WinW / 7) and y >= ((WinH / 7) + 20) and y <= 2 * (WinH / 7))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			al2.clear();
			al.clear();
			cout << "\nЗадача Коммивояжера:\n";
			int** matrix = New_Matrix();
			bool checker = Salesman_Check(matrix);
			if (!checker)
			{
				cout << "\nОшибка\n\n";
				return;
			}
			int n = graph.GetAmountVerts();
			while (al.size() < n)
				matrix = Matrix2(matrix);
			cout << endl;
			Print_Result();
			return;
		}
	}

}

void reshape(int w, int h)
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}






void Circle(int x, int y, int R, int text)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();
	Text(text, x, y);
	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}

	glEnd();
}




void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	ButtonTask();

	Circle(400, 100, 50, 1);//1
	Circle(700, 500, 50, 2);//2
	Circle(150, 400, 50, 3);//3
	Circle(50, 175, 50, 4);//4
	Circle(300, 600, 50, 5);//5
	Circle(800, 200, 50, 6);//6

	LineTo(12, 410, 150, 660, 475);
	LineDown(24, 660, 475, 410, 150);
	//1-2
	LineTo(34, 450, 110, 750, 210);
	LineDown(68, 750, 210, 450, 110);
	//1-6
	LineTo(18, 400, 150, 150, 350);
	LineDown(36, 150, 350, 400, 150);
	//1-3
	LineTo(5, 350, 100, 100, 175);
	LineDown(10, 100, 175, 350, 100);
	//1-4
	LineTo(3, 130, 350, 50, 220);
	LineDown(6, 50, 220, 130, 350);
	//3-4
	LineTo(21, 150, 450, 300, 550);
	LineDown(42, 300, 550, 150, 450);
	//3-5
	LineTo(16, 200, 400, 700, 450);
	LineDown(32, 700, 450, 200, 400);
	//3-2
	LineTo(53, 350, 600, 700, 550);
	LineDown(106, 700, 550, 350, 600);
	//5-2
	LineTo(45, 800, 250, 750, 500);
	LineDown(90, 750, 500, 800, 250);
	//6-2
	glutSwapBuffers();
}




void Graph::drawGraph()
{
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
	{
		if (!flag)
			setCoords(i, n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a = Matrix[i][j];
			if (a != 0)
				LineTo(a, cor[i].x, cor[i].y, cor[j].x, cor[j].y);
			if (a == Matrix[j][i] && a != 0)
				LineTo(a, cor[j].x, cor[j].y, cor[i].x, cor[i].y);
		}
	}
	Vertex(n);
	glutPostRedisplay();
}
void Vertex(int n)
{
	for (int i = 0; i < n; i++)
	{

		Circle(cor[i].x, cor[i].y, Radius, i + 1);

	}

}

void displaynew()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	ButtonTask();
	graph.drawGraph();
	glutSwapBuffers();
}