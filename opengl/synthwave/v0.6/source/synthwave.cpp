#include "synthwave.h"
#include <math.h>

const int circle_resolution = 100;
const int sun_radius = 10;
const int sun_distance_far = 20;

void draw_sun()
{
	glColor3f(1.0f,0.0f,0.2f);
	glBegin(GL_TRIANGLE_FAN); //to understand what a triangle fan is, look at an n64 game and think, "the models in those games were made of triangles"
		glVertex3f(0.0f,sun_distance_far,0.0f);
		
		for(int i = 0; i < circle_resolution+1; i++) 
		{
			float angle = 2 * HALF_PI * (float)i / (float)circle_resolution; //resolution here means the number of triangles to combine to make a circle
			float x = sun_radius * cosf(angle); //to find x co-ordinate, we use cos()
			float z = sun_radius * sinf(angle); //to find z co-ordinate, we use sin()
			glVertex3f(x,sun_distance_far,z);   //make the triangle fan
		}

		glVertex3f(sun_radius,sun_distance_far,0.0f); //end the triangle fan
	glEnd();
}

void pyramid(float x, float y, float py_w, float py_h)
{
	glColor4f(1.0,0.0,1.0,0.3);
	glBegin(GL_TRIANGLES);
		glVertex3f(  x+0.0f,  y+0.0f,+0.0f); //triangle 1
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+0.0f,+0.0f);
		glVertex3f(  x+py_w,  y+0.0f,+0.0f); //triangle 2
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+py_w,+0.0f);
		glVertex3f(  x+py_w,  y+py_w,+0.0f); //triangle 3
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+0.0f,  y+py_w,+0.0f);
		glVertex3f(  x+0.0f,  y+py_w,+0.0f); //triangle 4
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+0.0f,  y+0.0f,+0.0f);
	glEnd();

	glLineWidth(5.0f); //this part of the code is for making the thick borders
	glColor4f(1.0f,0.0f,1.0f,1.0f); //the code just before this serves the purpose of making the pyramids/mountains have a sort of translucent look
	glBegin(GL_LINES);
		glVertex3f(x+0.0f,y+0.0f,0.0f);
		glVertex3f(x+py_w,y+0.0f,0.0f);
		glVertex3f(x+py_w,y+0.0f,0.0f);
		glVertex3f(x+py_w,y+py_w,0.0f);
		glVertex3f(x+py_w,y+py_w,0.0f);
		glVertex3f(x+0.0f,y+py_w,0.0f);
		glVertex3f(x+0.0f,y+py_w,0.0f);
		glVertex3f(x+0.0f,y+0.0f,0.0f);
	glEnd(); //so satisfying

	
	glBegin(GL_LINES); //for drawing the square base of the pyramid
		glVertex3f(  x+0.0f,  y+0.0f,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+0.0f,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+py_w,  y+py_w,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
		glVertex3f(  x+0.0f,  y+py_w,+0.0f);
		glVertex3f(x+py_w/2,y+py_w/2, py_h);
	glEnd(); //even more satisfying
}

void draw_fence(int x_dis)
{
	float road_length = 30.0f;
	glColor4f(0.8f,0.0f,0.6f,0.5f);
	glLineWidth(3.0f);
	glBegin(GL_QUADS);
		glVertex3f(x_dis,+road_length,+0.3f);
		glVertex3f(x_dis,-road_length,+0.3f);
		glVertex3f(x_dis,-road_length,+0.0f);
		glVertex3f(x_dis,+road_length,+0.0f);
	glEnd();
	glColor4f(0.4f,1.0f,0.8f,1.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
		glVertex3f(x_dis,+road_length,+0.3f);
		glVertex3f(x_dis,-road_length,+0.3f);
		glVertex3f(x_dis,-road_length,+0.0f);
		glVertex3f(x_dis,+road_length,+0.0f);
	glEnd();
}

void character(float origin_x, float origin_y, float origin_z, float side_length) //for now, it's a simple** cube
{
	origin_x = origin_x - side_length / 2;
	origin_y = origin_y - side_length / 2;
	//origin_z = origin_z - side_length / 2; //not required, for now
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glLineWidth(10.0f);
	glBegin(GL_LINE_STRIP);
		glVertex3f(           +origin_x,           +origin_y,           +origin_z);
		glVertex3f(           +origin_x,           +origin_y,side_length+origin_z);
		glVertex3f(           +origin_x,side_length+origin_y,side_length+origin_z);
		glVertex3f(           +origin_x,side_length+origin_y,           +origin_z);
		glVertex3f(           +origin_x,           +origin_y,           +origin_z);
		glVertex3f(side_length+origin_x,           +origin_y,           +origin_z);
		glVertex3f(side_length+origin_x,           +origin_y,side_length+origin_z);
		glVertex3f(side_length+origin_x,side_length+origin_y,side_length+origin_z);
		glVertex3f(side_length+origin_x,side_length+origin_y,           +origin_z);
		glVertex3f(side_length+origin_x,           +origin_y,           +origin_z);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(           +origin_x,           +origin_y,side_length+origin_z);
		glVertex3f(side_length+origin_x,           +origin_y,side_length+origin_z);
		glVertex3f(           +origin_x,side_length+origin_y,side_length+origin_z);
		glVertex3f(side_length+origin_x,side_length+origin_y,side_length+origin_z);
		glVertex3f(           +origin_x,side_length+origin_y,           +origin_z);
		glVertex3f(side_length+origin_x,side_length+origin_y,           +origin_z);
	glEnd();
}

void draw_grid()
{
	glColor4f(1.0f,0.0f,1.0f,1.0f);
	glLineWidth(1.0f);
	for(float i=-50;i<=50;i=i+0.5) //simple for loop to draw many lines -> grid
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
