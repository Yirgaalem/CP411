/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-15 (update)
 */
#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Point.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"


class Camera {
 public:
	Point eye; 			/* camera position */
	Point ref; 			/* look at point  */
	Vector viewup; 		/* view up vector */
	GLfloat aspect, dnear, dfar, vangle, W, H;
	Vector viewNorm;    /* ref-eye/|ref-eye| */

	Camera();
	void set(Point Eye, Point look, Vector up);
	void set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz);
	void setViewNorm();
	void printCamera(void);
	void setDefaultCamera();
	void rotate(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle);
	void setRef(float lx, float ly, float lz);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	void setViewVolume(float viewAngle, float aspect, float Near, float Far);
	void setAspect(float aspect);
	void setProjectionMatrix();
};

#endif
