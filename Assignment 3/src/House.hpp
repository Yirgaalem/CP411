/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2021-10-06
 */
#ifndef CHOUSE_H
#define CHOUSE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"


class House: public Shape {
protected:
	Cube cube;
	Pyramid pyramid;
public:
	House();
	void draw();
};

#endif
