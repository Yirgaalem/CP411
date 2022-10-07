/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2021-10-06
 */
#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];  /* 2D array to store cube vertices */
	GLint face[5][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color cube */
public:
	Pyramid();
	void draw();
	void drawFace(int);
};

#endif
