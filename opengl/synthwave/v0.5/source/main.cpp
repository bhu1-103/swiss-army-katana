#include <GL/glut.h>
#include <stdlib.h>
#include "synthwave.h"
#include <math.h>

float povX = 0.0f;
float povY = 0.0f;
float povZ = 0.0f;
float cenX = 0.0f;
float cenY = 0.0f;
float cenZ = 0.0f;
float screenWidth = 1280;
float screenHeight = 720;
float py_h; //pyramid height
float py_w; //pyramid width, square base pyramid btw
float num1 = 20.0f - rand()%40; //made global variables because the position also got randomized after every frame...
float num2 = 20.0f - rand()%40; //will fix this mess soon
float num3 = 20.0f - rand()%40;
float num4 = 20.0f - rand()%40;
float num5 = 20.0f - rand()%40;
float num6 = 20.0f - rand()%40;
float num7 = 20.0f - rand()%40;
float num8 = 20.0f - rand()%40;
float num9 = 20.0f - rand()%40;
float num10 = 20.0f - rand()%40;
float num11 = 20.0f - rand()%40;
float num12 = 20.0f - rand()%40;
float num13 = 20.0f - rand()%40;
float num14 = 20.0f - rand()%40;


void initOpenGL() {
    glClearColor(0.2f, 0.0f, 0.2f, 1.0f); //deep dark purple bg
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,screenWidth/screenHeight,1.0f,50.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(povX,povY,3.0f+povZ, //eye position
                   cenX+0.0f,cenY+0.0f,cenZ+0.0f, //center position
                   0.0f,1.0f,0.0f); //z axis direction

    //begin drawing
	draw_sun(); //direct function call, will add input parameters for flexibility later
	draw_grid();

	//glColor4f(1.0f,0.0f,1.0f,1.0f);

	pyramid(num1, num2, +3.0f,+5.0f); //pretend you never saw this...
	pyramid(num3, num4, +3.0f,+5.0f);
	pyramid(num5, num6, +3.0f,+5.0f);
	pyramid(num7, num8, +3.0f,+5.0f);
	pyramid(num9, num10, +3.0f,+5.0f);
	pyramid(num11, num12, +3.0f,+5.0f);
	pyramid(num13, num14, +3.0f,+5.0f);

	glLineWidth(1.0f);
    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y)
{

        //typical wasd
        if(key == 'w'){povY += 0.1f;cenY += 0.1f;glutPostRedisplay();}
        if(key == 's'){povY -= 0.1f;cenY -= 0.1f;glutPostRedisplay();}
        if(key == 'd'){povX += 0.1f;cenX += 0.1f;glutPostRedisplay();}
        if(key == 'a'){povX -= 0.1f;cenX -= 0.1f;glutPostRedisplay();}
        if(key == 'm'){povZ += 0.1f;cenZ += 0.1f;glutPostRedisplay();}
        if(key == 'q'){povZ -= 0.1f;cenZ -= 0.1f;glutPostRedisplay();}
        if(key == 'e'){povZ += 0.1f;cenZ += 0.1f;glutPostRedisplay();}

        if(key == 'z'){povX += 0.1f;cenX += 0.1f;glutPostRedisplay();} //dungeon crawler 90 degree rotation
        if(key == 'x'){povX -= 0.1f;cenX -= 0.1f;glutPostRedisplay();}

        //weird....
        if(key == 'j'){povX -= 0.1f;glutPostRedisplay();} //look up
        if(key == 'l'){povX += 0.1f;glutPostRedisplay();} //look downw
        if(key == 'i'){povY -= 0.1f;povZ -= 0.1f;glutPostRedisplay();}
        if(key == 'k'){povY += 0.1f;povZ += 0.1f;glutPostRedisplay();}
        if(key == 'u'){povZ -= 0.1f;glutPostRedisplay();}
        if(key == 'o'){povZ += 0.1f;glutPostRedisplay();}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glViewport(0,0,screenWidth,screenHeight);
    glutCreateWindow("idk");
    initOpenGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();

    return 0;
}

