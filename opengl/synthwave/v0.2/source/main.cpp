#include <GL/glut.h>
#include <stdlib.h>

float povX = 0.0f;
float povY = 0.0f;
float povZ = 0.0f;
float screenWidth = 1280;
float screenHeight = 720;
float py_h;
float py_w;
float num1 = 10.0f - rand()%20; //made global variables because the position also got randomized after every frame...
float num2 = 10.0f - rand()%20; //will fix this mess soon
float num3 = 10.0f - rand()%20;
float num4 = 10.0f - rand()%20;
float num5 = 10.0f - rand()%20;
float num6 = 10.0f - rand()%20;
float num7 = 10.0f - rand()%20;
float num8 = 10.0f - rand()%20;
float num9 = 10.0f - rand()%20;
float num10 = 10.0f - rand()%20;
float num11 = 10.0f - rand()%20;
float num12 = 10.0f - rand()%20;
float num13 = 10.0f - rand()%20;
float num14 = 10.0f - rand()%20;
float num15 = 10.0f - rand()%20;
float num16 = 10.0f - rand()%20;
float num17 = 10.0f - rand()%20;
float num18 = 10.0f - rand()%20;
float num19 = 10.0f - rand()%20;
float num20 = 10.0f - rand()%20;
float num21 = 10.0f - rand()%20;
float num22 = 10.0f - rand()%20;
float num23 = 10.0f - rand()%20;
float num24 = 10.0f - rand()%20;
float num25 = 10.0f - rand()%20;
float num26 = 10.0f - rand()%20;
float num27 = 10.0f - rand()%20;
float num28 = 10.0f - rand()%20;
float num29 = 10.0f - rand()%20;
float num30 = 10.0f - rand()%20;
float num31 = 10.0f - rand()%20;
float num32 = 10.0f - rand()%20;
float num33 = 10.0f - rand()%20;
float num34 = 10.0f - rand()%20;
float num35 = 10.0f - rand()%20;
float num36 = 10.0f - rand()%20;
float num37 = 10.0f - rand()%20;
float num38 = 10.0f - rand()%20;
float num39 = 10.0f - rand()%20;
float num40 = 10.0f - rand()%20;
float num41 = 10.0f - rand()%20;
float num42 = 10.0f - rand()%20;
float num43 = 10.0f - rand()%20;
float num44 = 10.0f - rand()%20;
float num45 = 10.0f - rand()%20;
float num46 = 10.0f - rand()%20;
float num47 = 10.0f - rand()%20;
float num48 = 10.0f - rand()%20;
float num49 = 10.0f - rand()%20;
float num50 = 10.0f - rand()%20;

void pyramid(float x, float y, float py_w, float py_h)
{
	glColor4f(1.0,0.0,1.0,0.3);
	glBegin(GL_TRIANGLES);
		glVertex3f(  x+0.0f,  y+0.0f,+0.0f); //1
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+0.0f,+0.0f);
		glVertex3f(  x+py_w,  y+0.0f,+0.0f); //2
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+py_w,+0.0f);
		glVertex3f(  x+py_w,  y+py_w,+0.0f); //3
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+0.0f,  y+py_w,+0.0f);
		glVertex3f(  x+0.0f,  y+py_w,+0.0f); //4
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+0.0f,  y+0.0f,+0.0f);
	glEnd();

	glLineWidth(5.0f);
	glColor4f(1.0f,0.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glVertex3f(x+0.0f,y+0.0f,0.0f);
		glVertex3f(x+py_w,y+0.0f,0.0f);
		glVertex3f(x+py_w,y+0.0f,0.0f);
		glVertex3f(x+py_w,y+py_w,0.0f);
		glVertex3f(x+py_w,y+py_w,0.0f);
		glVertex3f(x+0.0f,y+py_w,0.0f);
		glVertex3f(x+0.0f,y+py_w,0.0f);
		glVertex3f(x+0.0f,y+0.0f,0.0f);
	glEnd();

	
	glBegin(GL_LINES);
		glVertex3f(  x+0.0f,  y+0.0f,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+0.0f,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+py_w,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+0.0f,  y+py_w,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
	glEnd();

}

void initOpenGL() {
    glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,screenWidth/screenHeight,1.0f,20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(povX,povY,3.0f+povZ,
                   0.0f,0.0f,0.0f,
                   0.0f,1.0f,0.0f);

    //begin drawing
	glColor4f(1.0f,0.0f,1.0f,1.0f);
	glLineWidth(1.0f);
	for(float i=-50;i<=50;i=i+0.5)
	{
		glBegin(GL_LINES);
			glVertex3f(i,+50.0f,0.0f);
			glVertex3f(i,-50.0f,0.0f);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(+50.0f,i,0.0f);
			glVertex3f(-50.0f,i,0.0f);
		glEnd();
	}

	pyramid(num1, num2, +3.0f,+5.0f);
	pyramid(num3, num4, +3.0f,+5.0f);
	pyramid(num5, num6, +3.0f,+5.0f);
	pyramid(num7, num8, +3.0f,+5.0f);
	pyramid(num9, num10, +3.0f,+5.0f);
	glLineWidth(1.0f);
    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y)
{
        if(key == 'a'){povX -= 0.1f;glutPostRedisplay();}
        if(key == 'd'){povX += 0.1f;glutPostRedisplay();}
        if(key == 'w'){povY -= 0.1f;glutPostRedisplay();}
        if(key == 's'){povY += 0.1f;glutPostRedisplay();}
        if(key == 'q'){povZ -= 0.1f;glutPostRedisplay();}
        if(key == 'e'){povZ += 0.1f;glutPostRedisplay();}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glViewport(0,0,1280,720);
    glutCreateWindow("idk");
    initOpenGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();

    return 0;
}

