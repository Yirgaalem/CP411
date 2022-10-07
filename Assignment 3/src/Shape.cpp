#include "Shape.hpp"
#include <stdio.h>

using namespace std;

Shape::Shape() {
	reset();
}

Shape::~Shape() { };

Matrix Shape::getMC() {
	return  mc;
};


void Shape::reset(){
	mc.loadIdentity();
	s = 1;
}

void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	mc.mat[0][3] += tx;
	mc.mat[1][3] += ty;
	mc.mat[2][3] += tz;
	mc.mat[3][3] = 1;
}

void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {

	Matrix m;
	GLfloat x0 = mc.mat[0][3];
	GLfloat y0 = mc.mat[1][3];
	GLfloat z0 = mc.mat[2][3];

	mc.mat[0][3] -= x0;
	mc.mat[1][3] -= y0;
	mc.mat[2][3] -= z0;

	m.rotateMatrix(rx, ry, rz, angle);
	mc.matrixPreMultiply(&m);

	mc.mat[0][3] += x0;
	mc.mat[1][3] += y0;
	mc.mat[2][3] += z0;

}


void Shape::rotate(GLfloat x0, GLfloat  y0, GLfloat  z0, GLfloat  rx, GLfloat  ry, GLfloat rz,  GLfloat  angle) {
	// your implementation
	Matrix m;
	mc.mat[0][3] -= x0;
	mc.mat[1][3] -= y0;
	mc.mat[2][3] -= z0;

	GLfloat radianAngle = angle * 3.1415926/180;
	GLfloat axisVectLength = sqrt (rx * rx + ry*ry + rz*rz);
	GLfloat cosA = cos (radianAngle); //
	GLfloat oneC = 1 - cosA;
	GLfloat sinA = sin (radianAngle); //
	GLfloat ux = (rx) / axisVectLength; // compute unit vector
	GLfloat uy = (ry) / axisVectLength;
	GLfloat uz = (rz) / axisVectLength;
	m.mat[0][0] = ux*ux*oneC + cosA; //
	m.mat[0][1] = ux*uy*oneC - uz*sinA;
	m.mat[0][2] = ux*uz*oneC + uy*sinA;
	m.mat[0][3] = 0;
	m.mat[1][0] = uy*ux*oneC + uz*sinA; //
	m.mat[1][1] = uy*uy*oneC + cosA;
	m.mat[1][2] = uy*uz*oneC - ux*sinA;
	m.mat[1][3] = 0;
	m.mat[2][0] = uz*ux*oneC - uy*sinA;
	m.mat[2][1] = uz*uy*oneC + ux*sinA;
	m.mat[2][2] = uz*uz*oneC + cosA;
	m.mat[2][3] = 0;
	m.mat[3][0] = 0;
	m.mat[3][1] = 0;
	m.mat[3][2] = 0;
	m.mat[3][3] = 1;

	mc.matrixPreMultiply(&m);
	mc.mat[0][3] += x0;
	mc.mat[1][3] += y0;
	mc.mat[2][3] += z0;
}

void Shape::rotateOrigin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix matrix;
	this->rotate(rx,ry,rz,-angle);
	matrix.rotateMatrix(rx,ry,rz,angle);
	mc.matrixPreMultiply(&matrix);

}


void Shape::setScale(GLfloat x) {
	s = x;
}

void Shape::scaleChange(GLfloat x) {
	s += x;
}

void Shape::setId(GLint i) {
	id = i;
}

GLint Shape::getId() {
	return id;
}

void Shape::ctmMultiply() {
	GLfloat M[16];
	M[0] = mc.mat[0][0];
	M[1] = mc.mat[1][0];
	M[2] = mc.mat[2][0];
	M[3] = 0;
	M[4] = mc.mat[0][1];
	M[5] = mc.mat[1][1];
	M[6] = mc.mat[2][1];
	M[7] = 0;
	M[8] = mc.mat[0][2];
	M[9] = mc.mat[1][2];
	M[10] = mc.mat[2][2];
	M[11] = 0;
	M[12] = mc.mat[0][3];
	M[13] = mc.mat[1][3];
	M[14] = mc.mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);
}
