
#include <graphics.h>
#include <iostream>

void midpointCircleDrawing(int xc, int yc, int r)
{
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y)
    {
        putpixel(xc + x, yc + y, WHITE); 
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);                         
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE); 
        x++;

        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * x - 2 * y + 1;
        }
    }
}

int main()
{
    int xc, yc, r;
    std::cout << "Enter the center of the circle: \nxc: ";
    std::cin >> xc;
    std::cout << "yc: ";
    std::cin >> yc;
    std::cout << "Enter the radius of the circle: ";
    std::cin >> r;

    int gm, gd = DETECT;
    initgraph(&gd, &gm, NULL);

    std::cout << "Drawing circle using Midpoint Circle Drawing Algorithm..." << std::endl;
    midpointCircleDrawing(xc, yc, r);
    std::cout << "Circle drawn successfully!" << std::endl;

    sleep(10000);
    getch();
    getch();
    closegraph();
    return 0;
}