#include<iostream>
#include<graphics.h>
#include<cmath>
using namespace std;

void drawBresenham(int x1, int y1, int x2, int y2, int color = WHITE)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int xi = x1 < x2 ? 1 : -1;
    int yi = y1 < y2 ? 1 : -1;
    int p;
    int x = x1, y = y1;

    if (dx > dy)
    {
        p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++)
        {
            putpixel(x, y, color);
            if (p >= 0)
            {
                y += yi;
                p -= 2 * dx;
            }
            x += xi;
            p += 2 * dy;
        }
    }
    else
    {
        p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++)
        {
            putpixel(x, y, color);
            if (p >= 0)
            {
                x += xi;
                p -= 2 * dy;
            }
            y += yi;
            p += 2 * dx;
        }
    }
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color = WHITE, int xc = 250, int yc = 250)
{
    x1 += xc;
    x2 += xc;
    x3 += xc;
    y1 += yc;
    y2 += yc;
    y3 += yc;
    drawBresenham(x1, y1, x2, y2, color);
    drawBresenham(x2, y2, x3, y3, color);
    drawBresenham(x3, y3, x1, y1, color);
}

void translate_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int tx, int ty)
{
    draw_triangle(x1 + tx, y1 + ty, x2 + tx, y2 + ty, x3 + tx, y3 + ty, RED);
}

void scale_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int sx, int sy){

    int cx = (x1+x2+x3)/3, cy = (y1,y2,y3)/3;
    x1 -= cx;
    x2 -= cx;
    x3 -= cx;
    y1 -= cy;
    y2 -= cy;
    y3 -= cy;
    x1 *= sx;
    x2 *= sx;
    x3 *= sx;
    y1 *= sy;
    y2 *= sy;
    y3 *= sy;
    draw_triangle(x1 + cx, y1 + cy, x2 + cx, y2 + cy, x3 + cx, y3 + cy, BLUE);
}

void rotate_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int ro){
    int cx = (x1+x2+x3)/3, cy = (y1,y2,y3)/3;
    x1 -= cx;
    x2 -= cx;
    x3 -= cx;
    y1 -= cy;
    y2 -= cy;
    y3 -= cy;
    ro = ro * 3.14159 / 180;
    int x1_ = x1*cos(ro) - y1*sin(ro);
    int y1_ = x1*sin(ro) + y1*cos(ro);
    int x2_ = x2*cos(ro) - y2*sin(ro);
    int y2_ = x2*sin(ro) + y2*cos(ro);
    int x3_ = x3*cos(ro) - y3*sin(ro);
    int y3_ = x3*sin(ro) + y3*cos(ro);
    draw_triangle(x1_ + cx, y1_ + cy, x2_ + cx, y2_ + cy, x3_ + cx, y3_ + cy, GREEN);
}

int main(){
    int x1, x2, y1, y2, x3, y3, xc, yc;
    // cout << "Enter the center of the triangle: " << endl;
    // cin >> xc >> yc;
    cout << "Enter the coordinates of the triangle: (point 1, point 2, point 3)" << endl;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int tx, ty;
    cout << "Enter the translation factor: " << endl;
    cin >> tx >> ty;
    int sx, sy;
    cout << "Enter scaling factor : " << endl;
    cin >> sx >> sy;
    int ro;
    cout << "Enter rotation angle : \n";
    cin >> ro;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    draw_triangle(x1, y1, x2, y2, x3, y3);
    translate_triangle(x1, y1, x2, y2, x3, y3, tx, ty);
    scale_triangle( x1,  y1,  x2,  y2,  x3,  y3,  sx,  sy);
    rotate_triangle( x1,  y1,  x2,  y2,  x3,  y3,  ro);
    getch();
    getch();
    closegraph();
    return 0;
}