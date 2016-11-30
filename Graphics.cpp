
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Graphics.h"

SDL_Window *__WINDOW = NULL;
SDL_Renderer *__RENDERER = NULL;
bool __ONLINE_DRAW = true;
Uint8 __RCOLOR, __GCOLOR, __BCOLOR, __ACOLOR;
Uint32 __COLOR32;

void initGraph(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	__WINDOW = SDL_CreateWindow("Kiarash - The dog noob", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    __RENDERER = SDL_CreateRenderer(__WINDOW, -1, SDL_RENDERER_ACCELERATED);
}

void closeGraph()
{
	SDL_DestroyWindow(__WINDOW);
	SDL_Quit();
}

void setOnlineDrawing(bool online)
{
	__ONLINE_DRAW = online;
}

void resetScreen()
{
    SDL_SetRenderDrawColor(__RENDERER, 255, 255, 255, 255);
    SDL_RenderClear(__RENDERER);
}

void updateScreen(bool check)
{
    if (check && !__ONLINE_DRAW)
        return;
    SDL_RenderPresent(__RENDERER);
}

void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	__RCOLOR = r;
	__GCOLOR = g;
	__BCOLOR = b;
	__ACOLOR = a;
    __COLOR32 = (Uint32)a * (1 << 24) + (Uint32)b * (1 << 16) + (Uint32)g * (1 << 8) + (Uint32)r;
}

void pixel(Sint16 x, Sint16 y)
{
    pixelColor(__RENDERER, x, y, __COLOR32);
    updateScreen(true);
}

void line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2)
{
    lineColor(__RENDERER, x1, y1, x2, y2, __COLOR32);
    updateScreen(true);
}

void line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width)
{
    thickLineColor(__RENDERER, x1, y1, x2, y2, width, __COLOR32);
    updateScreen(true);
}

void rectangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2)
{
    rectangleColor(__RENDERER, x1, y1, x2, y2, __COLOR32);
    updateScreen(true);
}

void bar(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2)
{
    boxColor(__RENDERER, x1, y1, x2, y2, __COLOR32);
    updateScreen(true);
}

void circle(Sint16 x, Sint16 y, Sint16 rad)
{
    circleColor(__RENDERER, x, y, rad, __COLOR32);
    updateScreen(true);
}

void filledCircle(Sint16 x, Sint16 y, Sint16 rad)
{
    filledCircleColor(__RENDERER, x, y, rad, __COLOR32);
    updateScreen(true);
}

void ellipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry)
{
    ellipseColor(__RENDERER, x, y, rx, ry, __COLOR32);
    updateScreen(true);
}

void filledEllipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry)
{
    filledEllipseColor(__RENDERER, x, y, rx, ry, __COLOR32);
    updateScreen(true);
}

void drawText(Sint16 x, Sint16 y, const char *s)
{
    stringColor(__RENDERER, x, y, s, __COLOR32);
}

void triangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3)
{
    trigonColor(__RENDERER, x1, y1, x2, y2, x3, y3, __COLOR32);
    updateScreen(true);
}

void filledTriangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3)
{
    filledTrigonColor(__RENDERER, x1, y1, x2, y2, x3, y3, __COLOR32);
    updateScreen(true);
}
