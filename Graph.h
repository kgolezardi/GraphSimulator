
#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

const int GRAPH_MAX_SIZE = 100;
extern bool __RUNNING;

typedef pair<int, int> GraphPoint;

class Graph
{
    public:
        int mat[2][GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];
        int size;
        bool bold[GRAPH_MAX_SIZE];
        void setBold(int vertex, bool value);
        void make();
        void display();
        void display(vector <string> text);
        Graph();
        ~Graph();
    private:
        void drawGraph();
        int selectNode();
        void stopAll();
        GraphPoint node[GRAPH_MAX_SIZE];
        void newNode(int x, int y);
        void getVertices();
        void getEdges();
        void getBolds();
        int getEdgeType();
};

#endif
