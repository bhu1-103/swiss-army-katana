#include <GL/glut.h>

float povX = 0.0f;
float povY = 0.0f;

void initOpenGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,1280.0f/720.0f,1.0f,10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(povX,povY,3.0f,
		   0.0f,0.0f,0.0f,
		   0.0f,1.0f,0.0f);
	

	//begin drawing
	glColor4f(1.0f,0.0f,0.0f,0.5f);
	glBegin(GL_QUADS);
		glVertex3f(-0.5f,-0.5f,0.0f);
		glVertex3f(-0.5f,+0.5f,0.0f);
		glVertex3f(+0.5f,+0.5f,0.0f);
		glVertex3f(+0.5f,-0.5f,0.0f);
	glEnd();
	
	glColor4f(0.0f,1.0f,0.0f,0.5f);
	glBegin(GL_QUADS);
		glVertex3f(-0.5f,-0.5f,-1.0f);
		glVertex3f(-0.5f,+0.5f,-1.0f);
		glVertex3f(+0.5f,+0.5f,-1.0f);
		glVertex3f(+0.5f,-0.5f,-1.0f);
	glEnd();


    glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y) 
{
	switch(key) 
	{	case 'a':
			povX -= 0.1f;
			glutPostRedisplay();
			break;
		case 'd':
			povX += 0.1f;
			glutPostRedisplay();
			break;
		case 'w':
			povY -= 0.1f;
			glutPostRedisplay();
			break;
		case 's':
			povY += 0.1f;
			glutPostRedisplay();
			break;
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

