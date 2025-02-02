#include<iostream>
#include<graphics.h>
#include<cmath>
using namespace std;

typedef struct point{
    int x;
    int y;
}Vector2;

typedef struct triangle{
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
    int color = WHITE;
}TRIANGLE;

Vector2 centre = {250, 250};

void drawBresenham(Vector2 p1, Vector2 p2, int color = WHITE)
{
    int x1 = p1.x + centre.x, y1 = p1.y + centre.y, x2 = p2.x + centre.x, y2 = p2.y + centre.y;
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

void draw_triangle(TRIANGLE t){
    drawBresenham(t.p1, t.p2, t.color);
    drawBresenham(t.p1, t.p3, t.color);
    drawBresenham(t.p3, t.p2, t.color);
}

TRIANGLE translate (TRIANGLE t, Vector2 v){
    TRIANGLE t_;
    t_.p1.x = t.p1.x + v.x;
    t_.p1.y = t.p1.y + v.y;
    t_.p2.x = t.p2.x + v.x;
    t_.p2.y = t.p2.y + v.y;
    t_.p3.x = t.p3.x + v.x;
    t_.p3.y = t.p3.y + v.y;
    t_.color = RED; 
    return t_;
}

TRIANGLE scale (TRIANGLE t, Vector2 v){
    TRIANGLE t_;
    Vector2 centroid = {(t.p1.x + t.p2.x + t.p3.x) / 3, (t.p1.y + t.p2.y + t.p3.y) / 3};
    t_.p1.x = centroid.x + v.x * (t.p1.x - centroid.x);
    t_.p1.y = centroid.y + v.y * (t.p1.y - centroid.y);
    t_.p2.x = centroid.x + v.x * (t.p2.x - centroid.x);
    t_.p2.y = centroid.y + v.y * (t.p2.y - centroid.y);
    t_.p3.x = centroid.x + v.x * (t.p3.x - centroid.x);
    t_.p3.y = centroid.y + v.y * (t.p3.y - centroid.y);
    t_.color = GREEN;
    return t_;
}

TRIANGLE rotate (TRIANGLE t, float angle){
    TRIANGLE t_;
    angle = angle * 3.14159 / 180;
    float s = sin(angle);
    float c = cos(angle);
    t_.p1.x = t.p1.x * c - t.p1.y * s;
    t_.p1.y = t.p1.x * s + t.p1.y * c;
    t_.p2.x = t.p2.x * c - t.p2.y * s;
    t_.p2.y = t.p2.x * s + t.p2.y * c;
    t_.p3.x = t.p3.x * c - t.p3.y * s;
    t_.p3.y = t.p3.x * s + t.p3.y * c;
    t_.color = BLUE;
    return t_;
}

TRIANGLE reflect(TRIANGLE t, int axis){
    TRIANGLE t_;
    if(axis == 0){
        t_.p1.x = t.p1.x;
        t_.p1.y = -t.p1.y;
        t_.p2.x = t.p2.x;
        t_.p2.y = -t.p2.y;
        t_.p3.x = t.p3.x;
        t_.p3.y = -t.p3.y;
    }
    else if(axis == 1){
        t_.p1.x = -t.p1.x;
        t_.p1.y = t.p1.y;
        t_.p2.x = -t.p2.x;
        t_.p2.y = t.p2.y;
        t_.p3.x = -t.p3.x;
        t_.p3.y = t.p3.y;
    }
    else{
        t_.p1.x = -t.p1.x;
        t_.p1.y = -t.p1.y;
        t_.p2.x = -t.p2.x;
        t_.p2.y = -t.p2.y;
        t_.p3.x = -t.p3.x;
        t_.p3.y = -t.p3.y;
    }
    t_.color = YELLOW;
    return t_;
}

TRIANGLE shear (TRIANGLE t, float sx, float sy){
    TRIANGLE t_;
    t_.p1.x = t.p1.x + sx * t.p1.y;
    t_.p1.y = t.p1.y + sy * t.p1.x;
    t_.p2.x = t.p2.x + sx * t.p2.y;
    t_.p2.y = t.p2.y + sy * t.p2.x;
    t_.p3.x = t.p3.x + sx * t.p3.y;
    t_.p3.y = t.p3.y + sy * t.p3.x;
    t_.color = CYAN;
    return t_;
}

int main(){
    TRIANGLE t, t_; 
    cout << "Enter the coordinates of the triangle: \n";
    cout << "Enter the coordinates of the first point: \n";
    cin >> t.p1.x >> t.p1.y;
    cout << "Enter the coordinates of the second point: \n";
    cin >> t.p2.x >> t.p2.y;
    cout << "Enter the coordinates of the third point: \n";
    cin >> t.p3.x >> t.p3.y;
    int choice;
    cout << "Enter the choice: \n";
    cout << "1. Translate\n";
    cout << "2. Scale\n";
    cout << "3. Rotate\n";
    cout << "4. Reflect\n";
    cout << "5. Shear\n";
    cin >> choice;
    switch(choice){
        case 1:
            Vector2 v;
            cout << "Enter the translation vector: \n";
            cin >> v.x >> v.y;
            t_ = translate(t, v);
            break;
        case 2:
            Vector2 s;
            cout << "Enter the scaling vector: \n";
            cin >> s.x >> s.y;
            t_ = scale(t, s);
            break;
        case 3:
            float angle;
            cout << "Enter the angle of rotation: ";
            cin >> angle;
            t_ = rotate(t, angle);
            break;
        case 4:
            int axis;
            cout << "Enter the axis of reflection: ";
            cin >> axis;
            t_ = reflect(t, axis);
            break;
        case 5:
            float sx, sy;
            cout << "Enter the shear factors: \n";
            cin >> sx >> sy;
            t_ = shear(t, sx, sy);
            break;
        default:
            cout << "Invalid choice\n";
    }
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    draw_triangle(t);
    draw_triangle(t_);
    getch();
    closegraph();
    return 0;
}