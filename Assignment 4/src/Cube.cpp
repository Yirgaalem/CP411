/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-15 (update)
 */

#include <stdio.h>
#include "Cube.hpp"

extern Camera myCamera;
extern Light myLight;
extern bool isCulling;
extern bool isShading;
extern RenderMode renderMode;
extern CullMode cullMode;
Cube::Cube() {
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 1;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 1;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 1;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

	// faceColor
	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0;
	faceColor[0][2] = 0.0;//red

	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0;
	faceColor[1][2] = 0.0;//blue

	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0;
	faceColor[2][2] = 1.0;//green

	faceColor[3][0] = 1.0, faceColor[5][1] = 1.0;
	faceColor[3][2] = 0.0;//yellow

	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0;
	faceColor[4][2] = 1.0; //pink

	faceColor[5][0] = 0.0, faceColor[3][1] = 1.0;
	faceColor[5][2] = 1.0; //cyan


	// set or compute face normals
	for (int i = 0 ; i<6; i++) {
		Vector V1 = Vector(vertex[face[i][1]][0]-vertex[face[i][0]][0], vertex[face[i][1]][1]-vertex[face[i][0]][1], vertex[face[i][1]][2]-vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0]-vertex[face[i][1]][0], vertex[face[i][2]][1]-vertex[face[i][1]][1], vertex[face[i][2]][2]-vertex[face[i][1]][2]);
		Vector V3 =  V1.cross(V2);
		V3.normalize();
		faceNormal[i][0] = V3.x;
		faceNormal[i][1] = V3.y;
		faceNormal[i][2] = V3.z;
	}

	r = 1.0;
	g = 0.0;
	b = 0.0;
}

void Cube::drawFace(int i) {

	GLfloat shade = 1;

	switch (renderMode) {
		case WIRE:   // this case from SimpleView1
			glColor3f(r, g, b);
		    glBegin(GL_LINE_LOOP);
		    glVertex3fv(vertex[face[i][0]]);
		    glVertex3fv(vertex[face[i][1]]);
		    glVertex3fv(vertex[face[i][2]]);
		    glVertex3fv(vertex[face[i][3]]);
		    glEnd();
		    break;

		case CONSTANT:
//			glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
			if (myLight.on == true)
				shade = getFaceShade(i, myLight);
		    glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
		    glBegin(GL_POLYGON);
		    glVertex3fv(vertex[face[i][0]]);
		    glVertex3fv(vertex[face[i][1]]);
		    glVertex3fv(vertex[face[i][2]]);
		    glVertex3fv(vertex[face[i][3]]);
		    glEnd();
		    break;

		case FLAT:
		   glShadeModel(GL_FLAT);

		   // add your code

		   break;
		case SMOOTH:
			glEnable(GL_NORMALIZE);
			glShadeModel(GL_SMOOTH);
	//....

		break;
		case PHONE:
		  break;
	}

}

void Cube::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s,s,s);
	for (int i = 0; i < 6; i++) {
		if (cullMode == BACKFACE) {
			if (isFrontface(i, myCamera))
				drawFace(i);
		}
		else
			drawFace(i);
	}
	glPopMatrix();
}

bool Cube::isFrontface(int faceindex, Camera camera) {
// your implementation

	GLfloat v[4];
	v[0] = faceNormal[faceindex][0];  // get faceNormal in MCS
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0.0;
	mc.multiplyVector(v);   // compute faceNormal in WCS

	if (pmc != NULL) {  // if parent MCS exists, use the parent's origin as reference point.
		pmc->multiplyVector(v);
		return (pmc->mat[0][3] - camera.eye.x) * v[0] + (pmc->mat[1][3] - camera.eye.y) * v[1] + (pmc->mat[2][3] - camera.eye.z) * v[2] < 0;
	}
	return (mc.mat[0][3] - camera.eye.x) * v[0] + (mc.mat[1][3] - camera.eye.y) * v[1] + (mc.mat[2][3] - camera.eye.z) * v[2] < 0;

}

GLfloat Cube::getFaceShade(int faceindex, Light light) {
    GLfloat shade = 1, v[4], s[4], temp;

    // assign v the first vertex of face[faceindex][0]
    v[0] = vertex[face[faceindex][0]][0];
    v[1] = vertex[face[faceindex][0]][1];
    v[2] = vertex[face[faceindex][0]][2];
    v[3] = 1;

    // compute the position of vertex face[faceindex][0] in WCS
    mc.multiplyVector(v);
    if (pmc != NULL)
            pmc->multiplyVector(v);

    // compute the light vector s[] = lightposition - face[faceindex][0]
    s[0] = light.getMC().mat[0][3] - v[0];
    s[1] = light.getMC().mat[1][3] - v[0];
    s[2] = light.getMC().mat[2][3] - v[0];


    // normalize vector s
    GLfloat norm = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
    s[0] = s[0] / norm;
    s[1] = s[1] / norm;
    s[2] = s[2] / norm;

    // compute the normal of face[faceindex] in WCS
    v[0] = faceNormal[faceindex][0];
    v[1] = faceNormal[faceindex][1];
    v[2] = faceNormal[faceindex][2];
    v[3] = 0;
    mc.multiplyVector(v);

    if (pmc != NULL)
        pmc->multiplyVector(v);

    // normalize face normal
    norm = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[0] = v[0] / norm;
    v[1] = v[1] / norm;
    v[2] = v[2] / norm;

    // compute v dot s
    temp = v[0] * s[0] + v[1] * s[1] + v[2] * s[2];

    // compute shade factor
    shade = light.I * light.Rd * temp;

    if (shade < 0.01)
        shade = 0.1;
    if (shade > 0.99)
        shade = 0.9;

    return shade;
}
