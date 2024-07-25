#include "synthwave.h"
#include <math.h>

const int circle_resolution = 100;
const int sun_radius = 10;

void draw_sun()
{
	glColor3f(1.0f,0.0f,0.2f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f,20.0f,0.0f);
		
		for(int i = 0; i < circle_resolution+1; i++)
		{
			float angle = 2 * HALF_PI * (float)i / (float)circle_resolution;
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

void draw_grid()
{
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
}
