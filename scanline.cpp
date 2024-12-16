#include <graphics.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Maximum number of vertices the polygon can have
const int MAX_VERTICES = 100;

// Base class for polygons
class Polygon {
protected:
    int vertices[MAX_VERTICES][2];  // 2D array to store vertices [x, y] coordinates
    int numVertices;                // Number of vertices in the polygon
    int color;                      // Color to fill the polygon
public:
    Polygon(int c) {
        color = c;
        numVertices=0;
    }

    // Function to add a vertex using direct assignment in the 2D array
    void addVertex(int x, int y) {
        if (numVertices < MAX_VERTICES) {
            vertices[numVertices][0] = x;  // Store x-coordinate
            vertices[numVertices][1] = y;  // Store y-coordinate
            numVertices++;
        } else {
            cout << "Maximum number of vertices reached." << endl;
        }
    }

    // Function to draw the polygon outline
    void draw() {
        for (int i = 0; i < numVertices - 1; i++) {
            line(vertices[i][0], vertices[i][1], vertices[i + 1][0], vertices[i + 1][1]);
        }
        // Connect the last vertex to the first
        line(vertices[numVertices - 1][0], vertices[numVertices - 1][1], vertices[0][0], vertices[0][1]);
    }
};

// Derived class for concave polygon with scanline fill algorithm
class ConcavePolygon : public Polygon {
public:
    ConcavePolygon(int c) : Polygon(c) {}

    // Function to fill the polygon using scanline algorithm
    void fillPolygon() {
        int ymin = vertices[0][1], ymax = vertices[0][1];

        // Find the minimum and maximum y coordinates
        for (int i = 1; i < numVertices; i++) {
            if (vertices[i][1] < ymin) 
                ymin = vertices[i][1];
                
            if (vertices[i][1] > ymax) 
                ymax = vertices[i][1];
        }

        // For each scanline (y-coordinate)
        for (int y = ymin; y <= ymax; y++) {
            int intersections[MAX_VERTICES];
            int interCount = 0;

            // Find intersections of scanline with polygon edges
            for (int i = 0; i < numVertices; i++) {
                int x1 = vertices[i][0], y1 = vertices[i][1];
                int x2 = vertices[(i + 1) % numVertices][0], y2 = vertices[(i + 1) % numVertices][1];

                if (y1 == y2) continue;  // Ignore horizontal edges

                if (y >= min(y1, y2) && y <= max(y1, y2)) {
                    int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                    intersections[interCount++] = x;
                }
            }

            // Sort intersections by x-coordinate
            sort(intersections, intersections + interCount);

            // Fill pixels between pairs of intersections
            for (int i = 0; i < interCount; i += 2) {
                int xStart = intersections[i];
                int xEnd = intersections[i + 1];
                for (int x = xStart; x <= xEnd; x++) {
                    putpixel(x, y, color);
                }
            }
        }
    }
};

// Main function to test the implementation
int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm,NULL);

    // Create a concave polygon with color RED
    ConcavePolygon polygon(RED);

    // Add vertices to the concave polygon
    polygon.addVertex(200, 100);
    polygon.addVertex(300, 200);
    polygon.addVertex(250, 300);
    polygon.addVertex(150, 300);
    polygon.addVertex(100, 200);

    // Draw the polygon
    polygon.draw();

    // Fill the polygon using scanline algorithm
    polygon.fillPolygon();

    // Wait for user input to close the graphics window
    getch();
    closegraph();

    return 0;
}
