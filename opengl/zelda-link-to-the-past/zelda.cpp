#include <GL/glut.h>
#include <iostream>

// Character position and velocity
float characterX = 0.0f, characterY = 0.0f;
float velocityX = 0.0f, velocityY = 0.0f;
float moveSpeed = 0.02f; // Adjust as needed

void updateCharacter() {
    // Update character position based on velocity
    characterX += velocityX;
    characterY += velocityY;
    
    // Limit character movement within the road bounds
    if (characterX < -1.0f)
        characterX = -1.0f;
    else if (characterX > 1.0f)
        characterX = 1.0f;
    
    if (characterY < -1.0f)
        characterY = -1.0f;
    else if (characterY > 1.0f)
        characterY = 1.0f;
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            velocityY = moveSpeed;
            break;
        case 'a':
            velocityX = -moveSpeed;
            break;
        case 's':
            velocityY = -moveSpeed;
            break;
        case 'd':
            velocityX = moveSpeed;
            break;
    }
}

void handleKeyRelease(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 's':
            velocityY = 0.0f;
            break;
        case 'a':
        case 'd':
            velocityX = 0.0f;
            break;
    }
}

void drawRoad() {
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray color for the road
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
}

void drawCharacter() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the character
    glPointSize(20.0f); // Set point size to make character visible
    
    glBegin(GL_POINTS);
    glVertex2f(characterX, characterY);
    glEnd();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawRoad();
    drawCharacter();
    
    glutSwapBuffers();
}

void initRendering() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

void update(int value) {
    updateCharacter(); // Update character position
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Call update function every 16 milliseconds (about 60 FPS)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    
    glutCreateWindow("zelda");
    initRendering();
    
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyRelease); // Register key release function
    glutReshapeFunc(handleResize);
    glutTimerFunc(16, update, 0);
    
    glutMainLoop();
    return 0;
}

