
#include "Graph.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

void handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
        if (event.type == SDL_QUIT)
            __RUNNING = false;
}
//تنمتغغبتغفا

//void make_primitive_graph(int shift)//ino khoobe ezafe koni be codet ke bad az dadan ras ha yalhaye avalie ro khodesh injoori besaze badesh baghiasho khodesh dasti bede
//{
//	for(int i = 0; i < shift; i++)
//		for(int j = i; j < size; j += shift)
//			make_edge(j, (j + shift) % size);
//}

int main()
{
	Graph g;
    g.make();

    int index = 0, status[3] = {};
	string statusText[3] = {"SECOND", "HALF", "FULL"};
    while (__RUNNING)
	{
        handleEvent();
        
		bool boldtmp[GRAPH_MAX_SIZE] = {};
		for(int i = 0; i < g.size; i++)
			if(g.bold[i] == true)
			{
				for(int j = 0; j < g.size; j++)
					if(g.mat[0][i][j])
						boldtmp[j] = true;
				boldtmp[i] = true;
			}
		for(int i = 0; i < g.size; i++)
			if(g.bold[i] == true)
				g.setBold(i, 0);
		for(int i = 0; i < g.size; i++)
			if(boldtmp[i] == true)
				for(int j = 0; j < g.size; j++)
					if(g.mat[1][i][j])
						g.setBold(j, 1);
		index++;
		if(count(g.bold, g.bold + g.size, 1) > 1 && !status[0])
			status[0] = index;
		if(count(g.bold, g.bold + g.size, 1) >= g.size / 2 && !status[1])
			status[1] = index;
		if(count(g.bold, g.bold + g.size, 1) >= g.size && !status[2])
			status[2] = index;

        vector <string> text;
		for (int i = 0; i < 3; i++)
		{
            stringstream sout;
			sout << statusText[i];
			sout << ": ";
			if (status[i])
				sout << status[i];
			else
				sout << "NOT YET!";

            text.push_back(sout.str().c_str());
		}

		g.display(text);
        SDL_Delay(1000);
	}
}
