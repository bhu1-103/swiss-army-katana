#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265/2
int circle_resolution = 100;
int sun_radius = 10;

float povX = 0.0f;
float povY = 0.0f;
float povZ = 0.0f;
float screenWidth = 1280;
float screenHeight = 720;
float py_h;
float py_w;
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

void draw_sun()
{
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f,20.0f,0.0f);
		
		for(int i = 0; i < circle_resolution+1; i++)
		{
			float angle = 2 * PI * (float)i / (float)circle_resolution;
			float x = sun_radius * sinf(angle);
			float y = sun_radius * cosf(angle);
			glVertex3f(y,20.0f,x);
		}

		glVertex3f(sun_radius,20.0f,0.0f);
	glEnd();
}

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
    glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
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
    gluLookAt(povX,povY,3.0f+povZ,
                   0.0f,0.0f,0.0f,
                   0.0f,1.0f,0.0f);

    //begin drawing
	draw_sun();
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
	pyramid(num11, num12, +3.0f,+5.0f);
	pyramid(num13, num14, +3.0f,+5.0f);
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

