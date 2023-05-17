double max(double X,double Y)
{
    if(X > Y)
        return X;
    else
        return Y;
}
void Draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + x, yc - y, color);
}
void DrawEllipseDirect(HDC hdc, int xc, int yc, double A, double B, COLORREF color)
{
    OutputDebugStringA("Ellipse Direct");

    double x = 0, y = A;
    while (y >= 0)
    {
        x++;
        y = sqrt(B * B * (1 - ((x * x) / (A * A))));
        Draw4Points(hdc, xc, yc, round(x), round(y), color);
    }

    x = B, y = 0;
    while (x >= 0)
    {
        y++;
        x = sqrt(A * A * (1 - ((y * y) / (B * B))));
        Draw4Points(hdc, xc, yc, round(x), round(y), color);
    }
}

void DrawEllipseIterative(HDC hdc, int xc, int yc, double A, double B, COLORREF color)
{
    OutputDebugStringA("Ellipse Iterative");

    double x = A, y = 0;
    double dt = 1.0 / max(A, B);
    double cdt = cos(dt);
    double sdt = sin(dt);

    while (x > 0)
    {
        double x1 = x * cdt - (A / B) * y * sdt;
        y = y * cdt + (B / A) * x * sdt;
        x = x1;
        Draw4Points(hdc, xc, yc, Round(x), Round(y), color);
    }
}

void DrawEllipseMidPoint(HDC hdc, int xc, int yc, double rx, double ry, COLORREF color)
{
    OutputDebugStringA("Ellipse Midpoint");

    double dx, dy, d1, d2, x, y;
    x = 0.0;
    y = ry;

    //d of first region
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    //first region
    while (dx < dy)
    {

        Draw4Points(hdc, xc, yc, x, y, color);
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    //d of sec region
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);
    //Plotting points of second region
    while (y >= 0)
    {
        Draw4Points(hdc, xc, yc, x, y, color);

        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}