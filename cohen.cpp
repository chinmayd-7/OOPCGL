#include <iostream>
#include <graphics.h> // Include graphics library
using namespace std;

// Define the region codes
#define INSIDE 0  // 0000
#define LEFT 1    // 0001
#define RIGHT 2   // 0010
#define BOTTOM 4   // 0100
#define TOP 8      // 1000

// Function to compute the region code for a point (x, y)
int computeCode(float x, float y, float x_min, float y_min, float x_max, float y_max) {
    int code = INSIDE;

    if (x < x_min)      // to the left of clip window
        code |= LEFT;
    else if (x > x_max) // to the right of clip window
        code |= RIGHT;
    if (y < y_min)      // below the clip window
        code |= BOTTOM;
    else if (y > y_max) // above the clip window
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void cohenSutherlandClip(float x0, float y0, float x1, float y1, float x_min, float y_min, float x_max, float y_max) {
    int code0 = computeCode(x0, y0, x_min, y_min, x_max, y_max);
    int code1 = computeCode(x1, y1, x_min, y_min, x_max, y_max);
    bool accept = false;

    while (true) {
        if ((code0 == 0) && (code1 == 0)) {
            // Both points inside
            accept = true;
            break;
        } else if (code0 & code1) {
            // Both points share an outside zone
            break;
        } else {
            int code_out;
            float x, y;

            // At least one point is outside the clipping window
            if (code0 != 0) {
                code_out = code0; // Choose an outside point
            } else {
                code_out = code1;
            }

            //chinu
            float m=(y1-y0)/(x1-x0);
            float c=y0-(m*x0);
            // Find the intersection point
            if (code_out & TOP) {
                // Point is above the clip window
                // x = x0 + (x1 - x0) * (y_max - y0) / (y1 - y0);
                y = y_max;
                x=(y-c)/m;
            } else if (code_out & BOTTOM) {
                // Point is below the clip window
                // x = x0 + (x1 - x0) * (y_min - y0) / (y1 - y0);
                y = y_min;
                x=(y-c)/m;
            } else if (code_out & RIGHT) {
                // Point is to the right of the clip window
                // y = y0 + (y1 - y0) * (x_max - x0) / (x1 - x0);
                x = x_max;
                y=m*x+c;
            } else if (code_out & LEFT) {
                // Point is to the left of the clip window
                // y = y0 + (y1 - y0) * (x_min - x0) / (x1 - x0);
                x = x_min;
                y=m*x+c;
            }

            // Now we move the outside point to the intersection point
            if (code_out == code0) {
                x0 = x;
                y0 = y;
                code0 = computeCode(x0, y0, x_min, y_min, x_max, y_max);
            } else {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, x_min, y_min, x_max, y_max);
            }
        }
    }

    if (accept) {
        // Draw the accepted line
        line(x0, y0, x1, y1);
    }
}

int main() {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Define clipping window
    float x_min = 100, y_min = 100, x_max = 300, y_max = 300;

    // Draw the clipping window
    rectangle(x_min, y_min, x_max, y_max);

    // Define line coordinates
    float x0 = 50, y0 = 250, x1 = 250, y1 = 50;

    // Clip the line
    cohenSutherlandClip(x0, y0, x1, y1, x_min, y_min, x_max, y_max);

    getch();
    closegraph();
    return 0;
}