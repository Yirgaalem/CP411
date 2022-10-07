/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-06
 */
#ifndef HOUSE_HPP_
#define HOUSE_HPP_

#include <GL/glut.h>
#include "Pyramid.hpp"
#include "Cube.hpp"


class House: public Shape{
protected:
	Pyramid* pyramid;
	Cube* cube;

public:
	~House();
	House();
	void draw();
};


#endif /* House_HPP_ */
