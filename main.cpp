#include <Windows.h>
#include <tchar.h>
#include <bits/stdc++.h>
#include "line.h"
#include "circle.h"
#include "Ellipse.h"
#include <math.h>
#include "algorithm"
#include "clip.h"
#define ID_COMBOBOX 101
#define LOAD_ID 0x2
#define Clear_ID 0x6
#define Red_ID 0x3
#define Green_ID 0x4
#define Blue_ID 0x5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hinst;
int command = 0;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HIGHT = 720;
const COLORREF AllColors[3] = { RGB(200,50,50), RGB(0,100,0), RGB(0,0,200) };
COLORREF workingColor = AllColors[0];
//static string a;
//static string b;
static char c;
static char d;
static char e;

int choice;
int twoinputs=0;
int points[8]={0,0,0,0,0,0,0,0};
auto color=RGB(255, 0, 0);
LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{
    const TCHAR* items[] =
            {
                    TEXT("0- Change the background of window to be white"),
                    TEXT("1- DDA Line Algorithm"),
                    TEXT("2- Midpoint Line Algorithm"),
                    TEXT("3- Parametric Line Algorithm"),
                    TEXT("4- Direct Circle Algorithm"),
                    TEXT("5- Polar Circle Algorithm"),
                    TEXT("6- iterative Polar Circle Algorithm"),
                    TEXT("7- Midpoint Circle Algorithm"),
                    TEXT("8- Midpoint Circle Algorithm (Modified)"),
                    TEXT("9- Fill Circle (lines)"),
                    TEXT("10- Fill Circle (circles)"),
                    TEXT("11- Fill Square (Vertical)"),
                    TEXT("12- Fill Rectangle (horizontal)"),
                    TEXT("13- Convex Polygon Fill"),
                    TEXT("14- NON-Convex Polygon Fill"),
                    TEXT("15- Recursive Flood Fill"),
                    TEXT("16- NON-Recursive Flood Fill"),
                    TEXT("17- Cardinal Spline Curve"),
                    TEXT("18- Direct Ellipse Drawing"),
                    TEXT("19- Polar Ellipse Drawing"),
                    TEXT("20- Midpoint Ellipse Drawing"),
                    TEXT("21- Rectangle Clipping (point)"),
                    TEXT("22- Rectangle Clipping (Line)"),
                    TEXT("23- Rectangle Clipping (Polygon)"),
                    TEXT("24- Square Clipping (point)"),
                    TEXT("25- Square Clipping (Line)"),
                    TEXT("26- Circle Clipping (point)"),
                    TEXT("27- Circle Clipping (Line)"),
                    TEXT("28- Draw Square / Rectangle"),
            };

    HDC hdc;
    static HWND hwndCombo;
    static HWND hwndButtonLoad;
    static HWND clearButton;
    static HWND hwnd_SL_Title;
    static HWND hwndColorTile;
    static HWND hwndButtonRed;
    static HWND hwndButtonGreen;
    static HWND hwndButtonBlue;
    static int x,y;


    switch (mcode)
    {


        case WM_CREATE:
        {
            //create combo box
            hwndCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 350, 1100, hwnd, NULL, g_hinst, NULL);
            //populate combo box
            for (int i = 0; i < 29; i++)
                SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)items[i]);


            //Create save-load title
            hwnd_SL_Title = CreateWindow(
                    TEXT("static"),
                    TEXT("Load"),
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                    SCREEN_WIDTH * 0.9,	// x position
                    10,					// y position
                    120,				// Width
                    20,					// Height
                    hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

            //Create Save button



            //Create Load button
            hwndButtonLoad = CreateWindow(
                    TEXT("BUTTON"),
                    TEXT("Load"),		// Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    SCREEN_WIDTH * 0.9,	// x position
                    60,					// y position
                    100,				// Button width
                    20,					// Button height
                    hwnd,				// Parent window
                    (HMENU)LOAD_ID,	// ID
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);


            hwndButtonLoad = CreateWindow(
                    TEXT("BUTTON"),
                    TEXT("Clear"),		// Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    SCREEN_WIDTH * 0.9,	// x position
                    30,					// y position
                    100,				// Button width
                    20,					// Button height
                    hwnd,				// Parent window
                    (HMENU)Clear_ID,	// ID
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);

            //Create color title
            hwndColorTile = CreateWindow(
                    TEXT("static"),
                    TEXT("Choose color"),
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                    SCREEN_WIDTH * 0.9,	// x position
                    150,				// y position
                    120,				// Width
                    20,					// Height
                    hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

            // Button to Set Color to red
            hwndButtonRed = CreateWindow(
                    TEXT("BUTTON"),
                    TEXT("Red"),		// Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    SCREEN_WIDTH * 0.9,	// x position
                    170,				// y position
                    100,				// Button width
                    20,					// Button height
                    hwnd,				// Parent window
                    (HMENU)Red_ID,	// ID
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);


            // Button to Set Color to Green
            hwndButtonGreen = CreateWindow(
                    TEXT("BUTTON"),
                    TEXT("Green"),		// Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    SCREEN_WIDTH * 0.9,	// x position
                    200,				// y position
                    100,				// Button width
                    20,					// Button height
                    hwnd,				// Parent window
                    (HMENU)Green_ID,	// ID
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);


            // Button to Set Color to Green
            hwndButtonBlue = CreateWindow(
                    TEXT("BUTTON"),
                    TEXT("Blue"),		// Button text
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    SCREEN_WIDTH * 0.9,	// x position
                    230,				// y position
                    100,				// Button width
                    20,					// Button height
                    hwnd,				// Parent window
                    (HMENU)Blue_ID,	// ID
                    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);

            break;

        }
        case WM_LBUTTONDOWN:

            x = LOWORD(lp);
            y = HIWORD(lp);



            break;

        case WM_LBUTTONUP:
            hdc = GetDC(hwnd);

          // midpoint_line(hdc, x, y, LOWORD(lp), HIWORD(lp), RGB(255, 0, 0));
            if(choice==1) DDALine(hdc,x,y, LOWORD(lp), HIWORD(lp),color);
            if(choice==2) midpoint_line(hdc,x,y, LOWORD(lp), HIWORD(lp),color);
            if(choice==3) parametric_line(hdc,x,y, LOWORD(lp), HIWORD(lp),color);
            if(choice==4) {
double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleCartesian( hdc,  x,  y,  R,  color);
            }
            if(choice==5) {
                double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleDPolar( hdc,  x,  y,  R,  color);
            }
            if(choice==6) {
                double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleIPolar( hdc,  x,  y,  R,  color);
            }
            if(choice==7) {
                double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleMidpoint( hdc,  x,  y,  R,  color);
            }

            if(choice==8) {
                double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleMMidpoint( hdc,  x,  y,  R,  color);
            }
            if(choice==9) {
                double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleMMidpoint( hdc,  x,  y,  R,  color);
            }
            if(choice==10) {
                double R= sqrt(pow(abs(LOWORD(lp)-x),2)+pow(abs(HIWORD(lp)-y),2));
                DrawCircleMMidpoint( hdc,  x,  y,  R,  color);
            }
            if(choice==25){
if(twoinputs==0){
    points[0]=x;points[1]=y;points[2]=LOWORD(lp);points[3]=HIWORD(lp);
    twoinputs=1;
    for (int i = 0; i < 4; ++i) {
        printf("%d ",points[i]);
    }printf("\n ");

}
else{
   // min(1,3);
    x_min= fmin(x,0+LOWORD(lp));
    y_min= fmin(y,0+HIWORD(lp));
    x_max=fmax(x,0+LOWORD(lp));
    y_max= fmax(y,0+HIWORD(lp));
    printf("%d ",x_min); printf("%d ",y_min); printf("%d ",x_max); printf("%d ",y_max);printf("\n ");
    //parametric_line(hdc,x,y, LOWORD(lp), HIWORD(lp),color);

    cohenSutherland(double(points[0]),double(points[1]),double(points[2]),double(points[3]));

    parametric_line(hdc,answer[0],answer[1], answer[2], answer[3],color);
    twoinputs=0;
    answer[0]=-1;answer[1]=-1;answer[2]=-1;answer[3]=-1;





}
            }

            ReleaseDC(hwnd, hdc);
            break;

        case WM_COMMAND:
        {   if (HIWORD(wp) == CBN_SELCHANGE)
                {
                TCHAR strText[255] = TEXT("\0");
                //get position of selected item
                LRESULT num = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
                //get selected item text
                SendMessage(hwndCombo, CB_GETLBTEXT, num, (LPARAM)strText);

                if (num == 0) //Change the background of window to be white
                {
                    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                choice = num;
                SetFocus(hwnd);
                //    printf("%d",choice);
            }

            if (LOWORD(wp) == Blue_ID)
            {
color=RGB(0,0,255);
                MessageBox(hwnd, "Button clicked!", "Button Click Event", MB_OK);
            }
            if (LOWORD(wp) == Green_ID)
            {
                color=RGB(0,255,0);
                // Handle button click event here
                MessageBox(hwnd, "Button clicked!", "Button Click Event", MB_OK);
            }
            if (LOWORD(wp) == Red_ID)
            {
                color=RGB(255,0,0);
                // Handle button click event here
                MessageBox(hwnd, "Button clicked!", "Button Click Event", MB_OK);
            }

            break;

        }


        case WM_ERASEBKGND:
        {
            HDC hdc = (HDC)wp;
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW+1));
            break;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, mcode, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("DDALine");

    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = MyWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_WAIT);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

//    HWND hwnd = CreateWindow(szAppName, TEXT("DDA Line Drawing Algorithm"),
//        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
//        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//        NULL, NULL, hInstance, NULL);

    HWND   hwnd = CreateWindow(szAppName, TEXT("Choose option"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, SCREEN_WIDTH, SCREEN_HIGHT, 0, 0, hInstance, 0);


    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        //MessageBox(NULL, TEXT("wrong"), szAppName, MB_ICONERROR);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
