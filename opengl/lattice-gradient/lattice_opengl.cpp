#include <GL/glut.h>
void drawVector(float x, float y, float r, float g, float b, float p, float q) {
	glLineWidth(7.0f);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2f(p/10, q/5.625);
	glVertex2f(x/10, y/5.625);
	glEnd();
}

void display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glScalef(0.7,0.7,1);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(0.6, 0.0, 0.8);
	glVertex2f(-10, 0);
	glVertex2f(+10, 0);
	glVertex2f(0, -10);
	glVertex2f(0, +10);
	glEnd();
        glPointSize(5.0f);
	glBegin(GL_POINTS);
	for(float i=-10; i<10; i+=0.3){
		for(float j=-10; j<10; j+=0.1){
			glColor3f(j, j, (1-j)/2);
			glVertex2f(i, j/0.5625);
		}
	}
	glEnd(); 
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(0.6, 0.0, 0.8);
	glVertex2f(-10, 0);
	glVertex2f(10, 0);
	glVertex2f(0, -10);
	glVertex2f(0, 10);
	glEnd();
	drawVector(+0, +1, +1, +0, +0, +0, +0); // red vector
	drawVector(+1, +0, +0, +1, +0, +0, +0); // green vector
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("bhu1");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

