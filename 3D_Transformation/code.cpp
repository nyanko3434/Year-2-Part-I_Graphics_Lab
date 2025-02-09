#include<iostream>
#include<graphics.h>
#include<cmath>
using namespace std;

typedef struct Vector3{
    int x;
    int y;
    int z;
}vector3, POINT;

// typedef struct cube{
//     point p1;
//     point p2;
//     point p3;
//     point p4;
//     point p5;
//     point p6;
//     point p7;
//     point p8;
//     int color = WHITE;
// }CUBE;

vector3 centre = {250, 250, 250};

typedef struct point{
    int x;
    int y;
}Vector2;

POINT translate(POINT p, Vector3 v){
    POINT p_;
    p_.x = p.x + v.x;
    p_.y = p.y + v.y;
    p_.z = p.z + v.z;
    return p_;
}

POINT scale(POINT p, Vector3 v){
    POINT p_;
    p_.x = v.x * p.x;
    p_.y = v.y * p.y;
    p_.z = v.z * p.z;
    return p_;
}

POINT rotate(POINT p, float angle, int axis){
    POINT p_;
    angle = angle * 3.14159 / 180;
    float s = sin(angle);
    float c = cos(angle);
    if(axis == 0){
        p_.x = p.x;
        p_.y = p.y * c - p.z * s;
        p_.z = p.y * s + p.z * c;
    }
    else if(axis == 1){
        p_.x = p.x * c - p.z * s;
        p_.y = p.y;
        p_.z = p.x * s + p.z * c;
    }
    else if(axis == 2){
        p_.x = p.x * c - p.y * s;
        p_.y = p.x * s + p.y * c;
        p_.z = p.z;
    }
    return p_;
}

POINT reflect(POINT p, int axis){
    POINT p_;
    if(axis == 0){
        p_.x = p.x;
        p_.y = p.y;
        p_.z = -p.z;
    }
    else if(axis == 1){
        p_.x = p.x;
        p_.y = -p.y;
        p_.z = p.z;
    }
    else if(axis == 2){
        p_.x = -p.x;
        p_.y = p.y;
        p_.z = p.z;
    }
    return p_;
}

POINT shear(POINT p, float sa, float sb, int axis){
    POINT p_;
    if(axis == 0){
        p_.x = p.x + sa * p.y;
        p_.y = p.y + sb * p.x;
        p_.z = p.z;
    }
    else if(axis == 1){
        p_.x = p.x + sa * p.z;
        p_.y = p.y;
        p_.z = p.z + sb * p.x;
    }
    else if(axis == 2){
        p_.x = p.x;
        p_.y = p.y + sb * p.z;
        p_.z = p.z + sa * p.y;
    }
    return p_;
}

int main(){
    POINT p, p_;
    int axis;
    cout << "Enter the coordinates of the point: \n";
    cin >> p.x >> p.y >> p.z;
    cout << "Enter choice: \n";
    cout << "1. Translate\n";
    cout << "2. Scale\n";
    cout << "3. Rotate\n";
    cout << "4. Reflect\n";
    cout << "5. Shear\n";
    int choice;
    cin >> choice;
    switch(choice){
        case 1:
            cout << "Enter the translation vector: \n";
            Vector3 v;
            cin >> v.x >> v.y >> v.z;
            p_ = translate(p, v);
            break;
        case 2:
            cout << "Enter the scaling vector: \n";
            Vector3 s;
            cin >> s.x >> s.y >> s.z;
            p_ = scale(p, s);
            break;
        case 3:
            cout << "Enter the angle of rotation: \n";
            float angle;
            cin >> angle;
            cout << "Enter the axis of rotation: \n";
            cout << "0. X-axis\n";
            cout << "1. Y-axis\n";
            cout << "2. Z-axis\n";

            cin >> axis;
            p_ = rotate(p, angle, axis);
            break;
        case 4:
            cout << "Enter the axis of reflection: \n";
            cout << "0. XY-plane\n";
            cout << "1. XZ-plane\n";
            cout << "2. YZ-plane\n";

            cin >> axis;
            p_ = reflect(p, axis);
            break;
        case 5:
            cout << "Enter the shear factors: \n";
            float sa, sb;
            cin >> sa >> sb;
            cout << "Enter the axis of shear: \n";
            cout << "0. XY-plane\n";
            cout << "1. XZ-plane\n";
            cout << "2. YZ-plane\n";

            cin >> axis;
            p_ = shear(p, sa, sb, axis);
            break;
    }
    cout << "The new coordinates are: " << p_.x << " " << p_.y << " " << p_.z << "\n";

    return 0;
}