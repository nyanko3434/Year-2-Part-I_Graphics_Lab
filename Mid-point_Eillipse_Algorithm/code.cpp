#include<iostream>
#include<graphics.h>
using namespace std;

int xc, yc;

void plot(int x, int y){
    putpixel(xc + x, yc + y, 15);
    putpixel(xc - x, yc + y, 15);
    putpixel(xc + x, yc - y, 15);
    putpixel(xc - x, yc - y, 15);
}

void drawEllipse(int a, int b){
    int x = 0, y = b;
    int gm = DETECT, gd;
    initgraph(&gm, &gd, NULL);
    float d1 = b * b - a * a * b + 0.25 * a * a;
    plot(x, y);
    while(a * a * (y - 0.5) > b * b * (x + 1)){
        if(d1 < 0){
            d1 += b * b * (2 * x + 3);
            x++;
        }
        else{
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            x++;
            y--;
        }
        plot(x, y);
    }
    float d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while(y > 0){
        if(d2 < 0){
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
            y--;
        }
        else{
            d2 += a * a * (-2 * y + 3);
            y--;
        }
        plot(x, y);
    }
    getch();
    closegraph();
}

int main(){
    int a, b;
    cout << "Enter the Centre : \n xc : ";
    cin >> xc;
    cout << "yc : ";
    cin >> yc;
    cout << "Enter the Major and Minor Axis : \n a : ";
    cin >> a;
    cout << "b : ";
    cin >> b;
    drawEllipse(a, b);
    return 0;
}