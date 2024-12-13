#include<graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;

class Point {
public:
    float x, y;
    Point(int x = 0, int y = 0) {
        this->x=x;
        this->y=y;
    }
    Point operator+(Point translation) {
        Point result;
        result.x = x + translation.x;
        result.y = y + translation.y;
        return result; 
    }
    Point operator*(Point scaling) {
        Point result;
        result.x = x * scaling.x;
        result.y = y * scaling.y;
        return result; 
    }
    Point operator-(int angle) {
        double rad = angle * PI / 180.0;
        Point result;
        result.x = x*cos(rad) - y*sin(rad);
        result.y = x*sin(rad) + y*cos(rad);
        return result; 
    }
    

};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Point p1(100,100);        //xmin,ymin
    Point p2(150,200);      //xmax,ymax
    Point p1_new,p2_new;

    line(p1.x,p1.y,p2.x,p2.y);
    Point t(2,2);           //translation coordinates
     p1_new=p1+t;      //new p1
     p2_new=p2+t;      //new p2
    line(p1_new.x,p1_new.y,p2_new.x,p2_new.y);     //translated rect

    //scaling:
    Point s(2,2);           //scaling coordinates
    p1_new=p1*s;      //new p1
     p2_new=p2*s;      //new p2
    line(round(p1_new.x),round(p1_new.y),round(p2_new.x),round(p2_new.y));     //scaled rect in GREEN color

    //rotation
     p1_new=p1-(-30);      //new p1
     p2_new=p2-(-30);      //new p2
    setcolor(RED);
    line(round(p1_new.x),round(p1_new.y),round(p2_new.x),round(p2_new.y));     //rotated rect in RED color

    getch();
    closegraph();
    return 0;
}