#include "Graph.h"
#include <iostream>
using namespace std;

int WinW = 900;
int WinH = 900;




int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru");
    glutInit(&argc, argv);

    cout << " мой вариант -нажмите 1,новый граф -2\n";
    int p;
    cin >> p;
    if (p == 1) {

        graph.NewVertex(1);
        graph.NewVertex(2);
        graph.NewVertex(3);
        graph.NewVertex(4);
        graph.NewVertex(5);
        graph.NewVertex(6);

        graph.NewEdge(1, 2, 12);
        graph.NewEdge(1, 4, 5);
        graph.NewEdge(1, 6, 34);
        graph.NewEdge(1, 3, 18);
        graph.NewEdge(4, 3, 3);
        graph.NewEdge(3, 2, 16);
        graph.NewEdge(6, 2, 45);
        graph.NewEdge(5, 2, 53);
        graph.NewEdge(3, 5, 21);
        graph.NewEdge(2, 1, 24);
        graph.NewEdge(4, 1, 10);
        graph.NewEdge(6, 1, 68);
        graph.NewEdge(3, 1, 36);
        graph.NewEdge(3, 4, 6);
        graph.NewEdge(5, 3, 42);
        graph.NewEdge(2, 3, 32);
        graph.NewEdge(2, 6, 90);
        graph.NewEdge(2, 5, 106);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(WinW, WinH);
        glutCreateWindow(" My Graph");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutMouseFunc(mouseClick);
        glutMainLoop();
    }
    if (p == 2)
    {
        makeGraph();
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(WinW, WinH);
        glutCreateWindow(" New Graph");
        glutDisplayFunc(displaynew);
        glutReshapeFunc(reshape);
        glutMouseFunc(mouseClick);
        glutMainLoop();

    }
}





