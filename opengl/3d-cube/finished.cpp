#include <GL/glut.h>

float povX = 0.0f;
float povY = 0.0f;
float screenWidth = 1280;
float screenHeight = 720;

void initOpenGL() {
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,screenWidth/screenHeight,1.0f,10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(povX,povY,3.0f,
		   0.0f,0.0f,0.0f,
		   0.0f,1.0f,0.0f);
	

	//begin drawing
	glColor4f(1.0f,0.0f,0.0f,0.5f); //front
	glBegin(GL_QUADS);
		glVertex3f(-0.5f,-0.5f,+0.0f);
		glVertex3f(-0.5f,+0.5f,+0.0f);
		glVertex3f(+0.5f,+0.5f,+0.0f);
		glVertex3f(+0.5f,-0.5f,+0.0f);
	glEnd();
	glColor4f(0.0f,1.0f,0.0f,0.5f); //back
	glBegin(GL_QUADS);
		glVertex3f(-0.5f,-0.5f,-1.0f);
		glVertex3f(-0.5f,+0.5f,-1.0f);
		glVertex3f(+0.5f,+0.5f,-1.0f);
		glVertex3f(+0.5f,-0.5f,-1.0f);
	glEnd();
	glColor4f(1.0f,1.0f,0.0f,0.5f); //right
	glBegin(GL_QUADS);
		glVertex3f(+0.5f,+0.5f,+0.0f);
		glVertex3f(+0.5f,+0.5f,-1.0f);
		glVertex3f(+0.5f,-0.5f,-1.0f);
		glVertex3f(+0.5f,-0.5f,+0.0f);
	glEnd();
	glColor4f(0.0f,0.0f,1.0f,0.5f); //left
	glBegin(GL_QUADS);
		glVertex3f(-0.5f,+0.5f,+0.0f);
		glVertex3f(-0.5f,+0.5f,-1.0f);
		glVertex3f(-0.5f,-0.5f,-1.0f);
		glVertex3f(-0.5f,-0.5f,+0.0f);
	glEnd();
	glColor4f(1.0f,0.0f,1.0f,0.5f); //top
	glBegin(GL_QUADS);
		glVertex3f(+0.5f,+0.5f,+0.0f);
		glVertex3f(+0.5f,+0.5f,-1.0f);
		glVertex3f(-0.5f,+0.5f,-1.0f);
		glVertex3f(-0.5f,+0.5f,+0.0f);
	glEnd();
	glColor4f(0.0f,1.0f,1.0f,0.5f); //bottom
	glBegin(GL_QUADS);
		glVertex3f(+0.5f,-0.5f,+0.0f);
		glVertex3f(+0.5f,-0.5f,-1.0f);
		glVertex3f(-0.5f,-0.5f,-1.0f);
		glVertex3f(-0.5f,-0.5f,+0.0f);
	glEnd();



    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) 
{
	if(key == 'a')
	{
		povX -= 0.1f;
		glutPostRedisplay();
	}
	if(key == 'd')
	{
		povX += 0.1f;
		glutPostRedisplay();
	}
	if(key == 'w')
	{
		povY -= 0.1f;
		glutPostRedisplay();
	}
	if(key == 's')
	{
		povY += 0.1f;
		glutPostRedisplay();
	}

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

