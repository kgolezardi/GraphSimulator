#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <SDL2/SDL.h>

void initGraph(int width, int height);
void closeGraph();

void setOnlineDrawing(bool online);

void resetScreen();
void updateScreen(bool check = false);

void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

void pixel(Sint16 x, Sint16 y);

void line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2);
void line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width);

void rectangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2);
void bar(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2);

void circle(Sint16 x, Sint16 y, Sint16 rad);
void filledCircle(Sint16 x, Sint16 y, Sint16 rad);

void ellipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry);
void filledEllipse(Sint16 x, Sint16 y, Sint16 rx, Sint16 ry);

void triangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3);
void filledTriangle(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3);

void drawText(Sint16 x, Sint16 y, const char *s);


#endif // __GRAPHICS_H
