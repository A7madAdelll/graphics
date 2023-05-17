#include <Windows.h>
#include "Impofunctions.h"
#include <algorithm>
#include "math.h"
void DDALine(HDC hdc,int x1,int y1,int x2,int y2,COLORREF c){
    int dx = x2-x1;
    int dy=y2-y1;
    if(abs(dx) > abs(dy)) {
        if (x1 > y2)
            swap(x1, y1, x2, y2);
        int x = x1;
        double y = y1;
        SetPixel(hdc, x1, y1, c);
        double m = (double) dy / dx;
        while (x < x2) {
            x++;
            y += m;
            SetPixel(hdc, x, Round(y), c);
        }
    }
    else{
        if(y1>y2)
            swap(x1,y1,x2,y2);
        int y = y1;
        double x = x1;
        SetPixel(hdc, x1, y1, c);
        double mi = (double) dx / dy;
        while (y < y2) {
            y++;
            x += mi;
            SetPixel(hdc, Round(x), y, c);
        }
    }
}

void midpoint_line(HDC hdc,int x0, int y0, int x1, int y1,COLORREF c)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int x = x0;
    int y = y0;

    while (true) {
        SetPixel( hdc ,x, y,c); // Draw a pixel at (x, y)

        if (x == x1 && y == y1) break; // Exit loop when end point is reached

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}
void parametric_line (HDC hdc,int x0, int y0, int x1, int y1,COLORREF c){
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float xi = dx / steps;
    float yi = dy / steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++) {
        SetPixel(hdc,(int)x, (int)y,c); // Draw a pixel at (x, y)
        x += xi;
        y += yi;
    }
}