#include <Windows.h>
#include "Impofunctions.h"


void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc - y, yc - x, color);
    SetPixel(hdc, xc + y, yc - x, color);
}


void DrawCircleCartesian(HDC hdc, int xc, int yc, int R, COLORREF color)	//Direct Cartesian method
{
    OutputDebugStringA("Cartesian Circle");
    int x = 0, y = R;
    Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    while (x < y)
    {
        x++;
        y = Round(sqrt((R * R) - (x * x)));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}


void DrawCircleDPolar(HDC hdc, int xc, int yc, int R, COLORREF color) //Direct Polar method
{
    OutputDebugStringA("Direct Polar Cirlce");

    int x = R, y = 0;
    double t = 0;
    double dt = 1.0 / R;
    Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    while (x > y)
    {
        t += dt;
        x = Round(R * cos(t));
        y = Round(R * sin(t));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}


void DrawCircleIPolar(HDC hdc, int xc, int yc, int R, COLORREF color) //Iterative Polar
{
    OutputDebugStringA("Iterative Polar");

    double x = R, y = 0;
    double dt = 1.0 / R;
    double cdt = cos(dt);
    double sdt = sin(dt);
    Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    while (x > y)
    {
        double x1 = x * cdt - y * sdt;
        y = x * sdt + y * cdt;
        x = x1;
        Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    }
}


void DrawCircleMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    OutputDebugStringA("Midpoint cirlce");

    double d = 1.0 - R;
    int x = -1 * R, y = 0;
    Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    while (-x > y)
    {
        if (d > 0)
        {
            d += (2.0 * x) + (2.0 * y) + 5.0;
            x++;
        }
        else
        {
            d += (2.0 * y) + 2.0;
        }
        y++;
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}


void DrawCircleMMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color)
{

    double d = 1.0 - R;
    double d1 = -2.0 * R - 1.0;
    double d2 = 2.0;
    double x = -1 * R, y = 0;
    Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    while (x < y)
    {
        if (d > 0)
        {
            d += d1;
            d1 += 4;
            d2 += 2;
            x++;
        }
        else
        {
            d += d2;
            d1 += 2;
            d2 += 2;
        }
        y--;
        Draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    }
}

