#include<GL/glut>

float sunY = -0.8;  // Initial Y-coordinate of the sun (starting from below the horizon)
int direction = 1;  // 1 for sunrise, -1 for sunset

// Function to draw the sun
void drawSun() {
    glColor3f(1.0, 0.5, 0.0);  // Orange color for the sun
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(100); // Angle for each vertex
        float x = 0.1 * cosf(theta);  // X-coordinate of the circle
        float y = 0.1 * sinf(theta);  // Y-coordinate of the circle
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set background color for sky based on sun's position (day -> night transition)
    if (sunY >= 0) {
        glClearColor(0.0, 0.7, 1.0, 1.0);  // Blue sky for sunrise/day
    } else {
        glClearColor(0.1, 0.1, 0.3, 1.0);  // Darker sky for sunset/night
    }
    
    // Set position and draw the sun
    glPushMatrix();
    glTranslatef(0.0, sunY, 0.0);  // Move sun up and down
    drawSun();
    glPopMatrix();

    glutSwapBuffers();
}

// Function to animate the sun
void update(int value) {
    sunY += direction * 0.01;  // Move the sun by small increments

    // Reverse direction when the sun reaches the top (sunrise) or bottom (sunset)
    if (sunY > 0.8 || sunY < -0.8) {
        direction *= -1;
    }

    glutPostRedisplay();  // Redraw the scene
    glutTimerFunc(50, update, 0);  // Set the timer to update the animation
}

// Initialize OpenGL
void init() {
    glClearColor(0.1, 0.1, 0.3, 1.0);  // Initial background color (sunset/night)
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);  // Window size
    glutCreateWindow("Sunrise and Sunset Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0);  // Start the animation
    glutMainLoop();
    return 0;
}

