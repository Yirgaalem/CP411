#include "House.hpp"

House::House(){
	Shape *cube = new Cube();
	Shape *pyramid = new Pyramid();
}



void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();

    // draw cube
    glScalef(s,s,s);
    cube.draw();
    glPopMatrix();

    //draw pyramid
    glPushMatrix();
	this->ctmMultiply();
    glScalef(s,s,s);
    glTranslatef(0,0,1); //So it can be ontop of the cube
    pyramid.draw();
    glPopMatrix();


}

