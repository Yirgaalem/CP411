
#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

Matrix::Matrix() {
	loadIdentity();
}

// mat <- identity matrix
void Matrix::loadIdentity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrixPreMultiply(Matrix* m) {
	// add code here
	GLint row, col;
	Matrix matTemp;

	for(row = 0; row < 4; row++){
		for(col = 0; col < 4; col++)
			matTemp.mat[row][col] = m->mat[row][0] * mat[0][col] + m->mat[row][1] * mat[1][col] + m->mat[row][2] * mat[2][col] + m->mat[row][3] * mat[3][col];

	}

	for (row = 0; row < 4; row++){
		for(col = 0; col < 4; col++)

			mat[row][col] = matTemp.mat[row][col];
	}


}

// transpose  mat <- mat'
void Matrix::transpose() {
	GLint row, col, temp;
	for(row = 0; row < 4; row++){
		for(col = row; col < 4; col++){
			if(row != col){
				temp = this->mat[row][col];
				this->mat[row][col] = this->mat[col][row];
				this->mat[col][row] = temp;
			}
		}
	}

}

// normalize MC
void Matrix::normalize() {
	GLfloat norm = sqrt(mat[0][0]*mat[0][0] +mat[1][0]*mat[1][0]+mat[2][0]*mat[2][0]);
	mat[0][0] = mat[0][0]/norm;
	mat[1][0] = mat[1][0]/norm;
	mat[2][0] = mat[2][0]/norm;
	mat[0][2] = mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1];
	mat[1][2] = mat[2][0]*mat[0][1]-mat[0][0]*mat[2][1];
	mat[2][2] = mat[0][0]*mat[1][1]-mat[1][0]*mat[0][1];

	norm = sqrt(mat[0][2]*mat[0][2] + mat[1][2]*mat[1][2]+mat[2][2]*mat[2][2]);

	mat[0][2] = mat[0][2]/norm;
	mat[1][2] = mat[1][2]/norm;
	mat[2][2] = mat[2][2]/norm;
	mat[0][1] = mat[1][2]*mat[2][0]-mat[1][0]*mat[2][2];
	mat[1][1] = mat[2][2]*mat[0][0]-mat[2][0]*mat[0][2];
	mat[2][1] = mat[0][2]*mat[1][0]-mat[0][0]*mat[1][2];
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

// v  <- mat * v
void Matrix::multiplyVector(GLfloat* v) {
	// add code here
	int row;

	for(row = 0; row < 4; row++)
		v[row] = (this->mat[row][0] * v[0]) + (this->mat[row][1] * v[1]) + (this->mat[row][2] * v[2] + (this->mat[row][3] * v[3]));

}

void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
// add code here
	if(rz == 1){
		this->mat[0][0] = cos(angle*(M_PI/180));
		this->mat[0][1] = -1*(sin(angle*(M_PI/180)));
 		this->mat[1][0] = sin(angle*(M_PI/180));
 		this->mat[1][1] = cos(angle*(M_PI/180));
	}

	else if(rx == 1){
		this->mat[1][1] = cos(angle*(M_PI/180));
		this->mat[1][2] = -1*(sin(angle*(M_PI/180)));
		this->mat[2][1] = sin(angle*(M_PI/180));
		this->mat[2][2] = cos(angle*(M_PI/180));
	}

	else if (ry == 1){
		this->mat[0][0] = cos(angle*(M_PI/180));
		this->mat[0][2] = sin(angle*(M_PI/180));
		this->mat[2][0] = -1*(sin(angle*(M_PI/180)));
		this->mat[2][2] = cos(angle*(M_PI/180) );

	}

}



