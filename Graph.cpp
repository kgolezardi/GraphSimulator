
#include "Graph.h"
#include "Graphics.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

const int SCR_WIDTH = 1000;
const int SCR_HEIGHT = 700;
const int COLOR_NORMAL[4] = {0, 255, 0, 255};
const int COLOR_BOLD[4] = {0, 150, 0, 255};
const int COLOR_SELECT[4] = {255, 0, 0, 255};
const int COLOR_HELP[4] = {0, 0, 0, 255};
const int COLOR_TEXT[4] = {0, 0, 0, 255};
const int COLOR_LINE[2][4] = {{255, 0, 0, 255}, {0, 0, 255, 255}};
const int RADIUS = 20;
const int ARROW_SIZE = 10;
const double ARROW_DEGREE = 0.5;
bool __RUNNING = true;
int __SELECTED1 = -1, __SELECTED2 = -1;

char *helpText;

GraphPoint operator +(const GraphPoint &a, const GraphPoint &b)
{
    return make_pair(a.first + b.first, a.second + b.second);
}

GraphPoint operator -(const GraphPoint &a, const GraphPoint &b)
{
    return make_pair(a.first - b.first, a.second - b.second);
}

double distance(int dx, int dy)
{
    return sqrt(dx * dx + dy * dy);
}

double distance(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2, dy = y1 - y2;
    return distance(dx, dy);
}

GraphPoint rotate(GraphPoint point, double deg)
{
    int x = point.first, y = point.second;
    int resx = x * cos(deg) - y * sin(deg);
    int resy = x * sin(deg) + y * cos(deg);
    return make_pair(resx, resy);
}

GraphPoint rotate(GraphPoint src, GraphPoint point, double deg)
{
    GraphPoint res = rotate(point - src, deg);
    return res + src;
}

Graph::Graph()
{
    initGraph(SCR_WIDTH, SCR_HEIGHT);
    setOnlineDrawing(false);
    __RUNNING = true;
}

Graph::~Graph()
{
    closeGraph();
}

void Graph::stopAll()
{
    __RUNNING = false;
}

void Graph::setBold(int vertex, bool value)
{
    bold[vertex] = value;
}

void Graph::getVertices()
{
    helpText = "Please place the nodes! If finished, press RETURN!";
    display();
    
    SDL_Event event;
    while (__RUNNING)
        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                stopAll();
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                newNode(event.button.x, event.button.y);
            else if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.sym == SDLK_RETURN)
                    break;
}

int Graph::selectNode()
{
    SDL_Event event;
    while (__RUNNING)
        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
            {
                stopAll();
                return -1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x, y = event.button.y;
                for (int i = 0; i < size; i++)
                    if (distance(x, y, node[i].first, node[i].second) < RADIUS)
                        return i;
            }
            else if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.sym == SDLK_RETURN)
                    return -1;
}

int Graph::getEdgeType()
{
    SDL_Event event;
    while (__RUNNING)
        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
            {
                stopAll();
                return -1;
            }
            else if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.sym == SDLK_UP)
                    return 0;
                else if (event.key.keysym.sym == SDLK_DOWN)
                    return 1;
    
}

void Graph::getBolds()
{
    helpText = "Please select the nodes you want to make bold! If finished, press RETURN!";
    display();
    while (__RUNNING)
    {   
        int x = selectNode();
        if (x == -1)
            break;
        setBold(x, true);
        display();
    }
}

void Graph::getEdges()
{
    while (__RUNNING)
    {
        helpText = "Select the first and second node! If you're done, press RETURN";
        display();
        
        int a = selectNode();
        if (a == -1)
            break;
        __SELECTED1 = a;
        display();
        int b = selectNode();
        if (b == -1)
        {
            __SELECTED1 = -1;
            break;
        }
        __SELECTED2 = b;
        
        helpText = "Press UP or DOWN for type 1 or 2 (HIGH and LOW priority)";
        display();
        
        int type = getEdgeType();
        if (type == -1)
            break;
        mat[type][a][b] = 1;
        __SELECTED1 = -1;
        __SELECTED2 = -1;
    }
    
    helpText = "";
    display();
}

void Graph::make()
{
    getVertices();
    cout << "Got all the vertices!" << endl;
    
    getBolds();
    cout << "Got all the bold vertices!" << endl;
    
    getEdges();
    cout << "Got all the Edges" << endl;
}

void Graph::newNode(int x, int y)
{
    node[size] = make_pair(x, y);
    bold[size] = false;
    size++;
    display();
}

void Graph::display(vector <string> text)
{

    resetScreen();
    drawGraph();

    setColor(COLOR_HELP[0], COLOR_HELP[1], COLOR_HELP[2], COLOR_HELP[3]);

    for (int i = 0; i < text.size(); i++)
        drawText(5, 5 + i * 10, text[i].c_str());

    updateScreen();
}

void Graph::display()
{

    resetScreen();
    drawGraph();
    updateScreen();
}

void Graph::drawGraph()
{
    // HELP TEXT
    setColor(COLOR_HELP[0], COLOR_HELP[1], COLOR_HELP[2], COLOR_HELP[3]);
    drawText(5, 5, helpText);
    
    // EDGES
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < 2; k++)
                if (mat[k][i][j] && i != j)
                {
                    setColor(COLOR_LINE[k][0], COLOR_LINE[k][1], COLOR_LINE[k][2], COLOR_LINE[k][3]);
                    int x1 = node[i].first, y1 = node[i].second;
                    int x2 = node[j].first, y2 = node[j].second;
                    line(x1, y1, x2, y2);
                    
                    GraphPoint firstPoint, heightPoint, secondPoint, thirdPoint;
                    int dx = x1 - x2, dy = y1 - y2;
                    double dis = distance(dx, dy);
                    firstPoint = make_pair(x2 + dx * (RADIUS / dis), y2 + dy * (RADIUS / dis));
                    heightPoint = make_pair(x2 + dx * ((RADIUS + ARROW_SIZE) / dis), y2 + dy * ((RADIUS + ARROW_SIZE) / dis));
                    secondPoint = rotate(firstPoint, heightPoint, ARROW_DEGREE);
                    thirdPoint = rotate(firstPoint, heightPoint, -ARROW_DEGREE);
                    filledTriangle(firstPoint.first, firstPoint.second, secondPoint.first, secondPoint.second, thirdPoint.first, thirdPoint.second);
                }
    
    // VERTICES
    for (int i = 0; i < size; i++)
    {
        if (bold[i])
            setColor(COLOR_BOLD[0], COLOR_BOLD[1], COLOR_BOLD[2], COLOR_BOLD[3]);
        else
            setColor(COLOR_NORMAL[0], COLOR_NORMAL[1], COLOR_NORMAL[2], COLOR_NORMAL[3]);
        int x = node[i].first, y = node[i].second;
        filledCircle(x, y, RADIUS);
        setColor(COLOR_TEXT[0], COLOR_TEXT[1], COLOR_TEXT[2], COLOR_TEXT[3]);
        stringstream ss;
        ss << i;
        drawText(x, y, ss.str().c_str());
    }
    
    
    // SELECTED
    if (__SELECTED1 != -1)
    {
        setColor(COLOR_SELECT[0], COLOR_SELECT[1], COLOR_SELECT[2], COLOR_SELECT[3]);
        int x = node[__SELECTED1].first, y = node[__SELECTED1].second;
        circle(x, y, RADIUS);
        circle(x, y, RADIUS + 1);
    }
    if (__SELECTED2 != -1)
    {
        setColor(COLOR_SELECT[0], COLOR_SELECT[1], COLOR_SELECT[2], COLOR_SELECT[3]);
        int x = node[__SELECTED2].first, y = node[__SELECTED2].second;
        circle(x, y, RADIUS);
        circle(x, y, RADIUS + 1);
    }
}
