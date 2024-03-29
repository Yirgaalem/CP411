#include "Sphere.hpp"
extern RenderMode renderMode;

Sphere::Sphere(GLdouble size) {
	radius = size;
	splices = 50;
	stacks = 50;
	textureID = 0;
	r=1;
	g=1;
	b=1;
	quad = gluNewQuadric();
}

void Sphere::draw() {
	glPushMatrix();
	ctmMultiply();

	switch (renderMode) {
		case WIRE:
		case CONSTANT:
		case FLAT:
		case SMOOTH:
			glColor3f(r, g, b);
			glutSolidSphere(radius,splices,stacks);
			break;

		case TEXTURE:
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureID);
				gluSphere(quad, radius, splices, stacks);
				gluQuadricTexture(quad, textureID);
			glDisable(GL_TEXTURE_2D);
			break;

		case PHONE:
			// your code
			break;
	}

	glPopMatrix();
}


