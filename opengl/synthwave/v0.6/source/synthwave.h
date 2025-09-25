#ifndef SYNTHWAVE_H //if not defined
#define SYNTHWAVE_H //define

#include <GL/glut.h>
#define HALF_PI 3.14159265/2 //because I wanted only half of the sun and most likely wont be using it anywhere else

extern const int circle_resolution;
extern const int sun_radius;
extern const int sun_distance_far;
extern const int x_dis;

void draw_sun();
void draw_grid();
void draw_fence(int x_dis);
void pyramid(float x, float y, float py_w, float py_h);
void character(float origin_x, float origin_y, float origin_z, float side_length);

#endif
