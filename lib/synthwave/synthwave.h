#ifndef SYNTHWAVE_H
#define SYNTHWAVE_H

#include <GL/glut.h>
#define HALF_PI 3.14159265/2

extern const int circle_resolution;
extern const int sun_radius;

void draw_sun();
void draw_grid();
void pyramid(float x, float y, float py_w, float py_h);

#endif
