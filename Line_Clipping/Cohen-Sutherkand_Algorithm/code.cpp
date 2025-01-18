#include<iostream>
#include<graphics.h>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
using namespace std;

typedef struct{
    int x, y;
} Point;

int computeCode(Point p, int xmin, int ymin, int xmax, int ymax){
    int code = 0;
    if(p.x < xmin)
        code |= LEFT;
    if(p.x > xmax)
        code |= RIGHT;
    if(p.y < ymin)
        code |= BOTTOM;
    if(p.y > ymax)
        code |= TOP;
    return code;
}
void drawBresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int xi = x1 < x2 ? 1 : -1;
    int yi = y1 < y2 ? 1 : -1;
    int p;
    int x = x1, y = y1;

    if (dx > dy)
    {
        // Shallow slope (dx > dy)
        p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++)
        {
            putpixel(x, y, WHITE);
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
            putpixel(x, y, WHITE);
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

void drawwindow(int xmin, int ymin, int xmax, int ymax){
    line(xmin, ymin, xmax, ymin);
    line(xmax, ymin, xmax, ymax);
    line(xmax, ymax, xmin, ymax);
    line(xmin, ymax, xmin, ymin);
}

void cohenSutherland(Point p1, Point p2, int xmin, int ymin, int xmax, int ymax){
    int code1 = computeCode(p1, xmin, ymin, xmax, ymax);
    int code2 = computeCode(p2, xmin, ymin, xmax, ymax);
    bool accept = false;
    while(true){
        if((code1 == 0) && (code2 == 0)){
            accept = true;
            break;
        }
        else if(code1 & code2){
            break;
        }
        else{
            int code_out;
            double x, y;
            if(code1 != 0)
                code_out = code1;
            else
                code_out = code2;
            if(code_out & TOP){
                x = p1.x + (p2.x - p1.x) * (ymax - p1.y) / (p2.y - p1.y);
                y = ymax;
            }
            else if(code_out & BOTTOM){
                x = p1.x + (p2.x - p1.x) * (ymin - p1.y) / (p2.y - p1.y);
                y = ymin;
            }
            else if(code_out & RIGHT){
                y = p1.y + (p2.y - p1.y) * (xmax - p1.x) / (p2.x - p1.x);
                x = xmax;
            }
            else if(code_out & LEFT){
                y = p1.y + (p2.y - p1.y) * (xmin - p1.x) / (p2.x - p1.x);
                x = xmin;
            }
            if(code_out == code1){
                p1.x = x;
                p1.y = y;
                code1 = computeCode(p1, xmin, ymin, xmax, ymax);
            }
            else{
                p2.x = x;
                p2.y = y;
                code2 = computeCode(p2, xmin, ymin, xmax, ymax);
            }
        }
    }
    if(accept){
        drawBresenham(p1.x, p1.y, p2.x, p2.y);
    }
}   

int main(){

    return 0;
}