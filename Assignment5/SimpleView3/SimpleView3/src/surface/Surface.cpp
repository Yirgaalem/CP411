#include "Surface.hpp"

extern RenderMode renderMode;

Surface::Surface() {
	reset();
}

void Surface::reset() {
	row = 0;
	col = 0;
}

void Surface::drawSurface() {

	switch (renderMode) {
	case WIRE:
        // your code to mesh wire
		break;
	case CONSTANT:
	case FLAT:
	case SMOOTH:
	case PHONE:
	case TEXTURE:
		glPolygonMode( GL_FRONT, GL_FILL);
		glPolygonMode( GL_BACK, GL_LINE);
        // your code to draw filled mesh, using GL_QUAD_STRIP
		glColor3f(0, 1.0, 1.0);
		for(int i = 0; i < row-1; i++){
			glBegin(GL_QUAD_STRIP);
			for(int j = 0; j < col-1; j++){
				glNormal3f(Normal[i][j].x, Normal[i][j].y, Normal[i][j].z);
				glVertex3f(Pts[i][j].x, Pts[i][j].y, Pts[i][j].z);
				glNormal3f(Normal[i+1][j].x, Normal[i+1][j].y, Normal[i+1][j].z);
				glVertex3f(Pts[i+1][j].x, Pts[i+1][j].y, Pts[i+1][j].z);
			}
			glEnd();
		}

		break;
	}
}

void Surface::draw() {
	glPushMatrix();
	ctmMultiply();
	glScalef(s * 0.01, s * 0.01, s * 0.01);		// to shrink the object to size of viewable
	drawSurface();
	glPopMatrix();
}

