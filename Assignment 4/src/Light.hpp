/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-15 (update)
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Matrix.hpp"



class Light : public Shape {
	public:
		GLfloat I, Rd;
		GLboolean on;
		GLfloat size;
		Light();
		void Reset();
		void draw();
		void LightReset();
		void Increment(GLfloat);

};
#endif /* LIGHT_HPP_ */
