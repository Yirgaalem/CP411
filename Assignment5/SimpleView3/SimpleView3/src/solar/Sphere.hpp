#ifndef SPHERE_H
#define SPHERE_H

#include <windows.h>
#include <GL/glut.h>
#include "../Shape.hpp"

class Sphere: public Shape {
public:
	GLdouble radius; // radius
	GLint splices, stacks;
	GLfloat r, g, b; //radius, red, green, blue
	GLuint textureID;
	GLUquadric *quad;
	Sphere(GLdouble);
	void draw();
};

#endif
