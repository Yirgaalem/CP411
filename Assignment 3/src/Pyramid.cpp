#include "Pyramid.hpp"


Pyramid::Pyramid(){

	vertex[0][0] = -1;  vertex[0][1] = -1;  vertex[0][2] =   0;
	vertex[1][0] =  1;  vertex[1][1] = -1;  vertex[1][2] =   0;
	vertex[2][0] =  1;  vertex[2][1] =  1;  vertex[2][2] =   0;
	vertex[3][0] = -1;  vertex[3][1] =  1;  vertex[3][2] =   0;
	vertex[4][0] =  0;  vertex[4][1] =  0;  vertex[4][2] = 1.5;

	face[0][0] = 0; face[0][1] = 1; face[0][2] = 4; face[0][3] = -1;
	face[1][0] = 0; face[1][1] = 3; face[1][2] = 4; face[1][3] = -1;
	face[2][0] = 1; face[2][1] = 2; face[2][2] = 4; face[2][3] = -1;
	face[3][0] = 2; face[3][1] = 3; face[3][2] = 4; face[3][3] = -1;
	face[4][0] = 3; face[4][1] = 2; face[4][2] = 1; face[4][3] =  0;

	r = 1.0;
	g = 1.0;
	b = 0.0;

}


void Pyramid::drawFace(int i)
{
// draw face i
	glBegin(GL_LINE_LOOP);
	    glVertex3fv(&vertex[face[i][0]][0]);
	    glVertex3fv(vertex[face[i][1]]);
	    glVertex3fv(vertex[face[i][2]]);
	    if(face[i][3] != -1)
	    	glVertex3fv(vertex[face[i][3]]);

	glEnd();
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 // set color
    glColor3f(r,g,b);//Was r,g,b but didnt make it yellow
 // draw all faces
    for(int i = 0; i < 4; i++)
    	drawFace(i);

    glPopMatrix();
}
