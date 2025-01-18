#include <graphics.h>
#include <iostream>

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

void drawClippedLineBarsky(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p[4] = {-dx, dx, -dy, dy};
    int q[4] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};
    double t1 = 0, t2 = 1;
    for (int i = 0; i < 4; i++)
    {
        if (p[i] == 0)
        {
            if (q[i] < 0)
                return;
        }
        else
        {
            double t = (double)q[i] / p[i];
            if (p[i] < 0)
            {
                if (t > t1)
                    t1 = t;
            }
            else
            {
                if (t < t2)
                    t2 = t;
            }
        }
    }
    if (t1 < t2)
    {
        int x1_ = x1 + t1 * dx;
        int y1_ = y1 + t1 * dy;
        int x2_ = x1 + t2 * dx;
        int y2_ = y1 + t2 * dy;
        drawBresenham(x1_, y1_, x2_, y2_);
    }
}

int main()
{
    int xmin = 10, ymin = 10, xmax = 100, ymax = 100;
    std::cout << "Enter the coordinates of the clipping window (xmin, ymin, xmax, ymax): \n";
    std::cin >> xmin >> ymin >> xmax >> ymax;
    int x1 = 5, y1 = 5, x2 = 110, y2 = 105;
    std::cout << "Enter the coordinates of the first point: \n";
    std::cin >> x1 >> y1;
    std::cout << "Enter the coordinates of the second point: \n";
    std::cin >> x2 >> y2;

    int gm, gd = DETECT;
    initgraph(&gd, &gm, NULL);

    // Draw the clipping window
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);

    std::cout << "Clipping the line" << std::endl;
    drawClippedLineBarsky(x1, y1, x2, y2, xmin, ymin, xmax, ymax);
    std::cout << "Line clipped successfully" << std::endl;

    getch();
    closegraph();
    return 0;
}