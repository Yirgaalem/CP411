/*
 * Description: implementation of SimpleDraw file functions
 * Author: HBF
 * Version: 2021-08-24
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "file.hpp"
#include "object.hpp"
#include "edit.hpp"

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

extern LIST objlist;

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight) {
	FILE *fp = fopen(ptrcFileName, "wb");
		if (fp == NULL)
			return 0;



		// allocate memory to store image data
		int bitsize = nWidth*nHeight*3 +  ((3*nWidth)%4 == 0 ? 0 : (4-(3*nWidth)%4)*nHeight);

		printf("step 0 %d\n", bitsize);

		unsigned char *ptrImage = (unsigned char*) malloc(bitsize);
		if (ptrImage == NULL) {
			fclose(fp);
			return 0;
		}

		//read pixels from frame buffer, byte order is BGR
		glReadPixels(nX, nY, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, ptrImage);

		printf("step 1\n");
		// clean memory buffer of bitmap header and information header
		BITMAPFILEHEADER bfh;
		BITMAPINFOHEADER bih;
		memset(&bfh, 0, sizeof(bfh));
		memset(&bih, 0, sizeof(bih));

		// set the bitmap header with the give parameters
		bfh.bfType = 0x4d42; // 'MB'
		bfh.bfSize = sizeof(bfh) + sizeof(bih) + bitsize;
		bfh.bfOffBits = sizeof(bfh) + sizeof(bih);

	    // set bitmap information header
		bih.biSize = sizeof(bih);
		bih.biWidth = nWidth + nWidth%4;
		bih.biHeight = nHeight;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		bih.biSizeImage = bitsize;

		// write to file
		if (fwrite(&bfh, sizeof(bfh), 1, fp) < 1) {
			free(ptrImage);
			fclose(fp);
			return 0;
		};

		if (fwrite(&bih, sizeof(bih), 1, fp)<1) {
			free(ptrImage);
			fclose(fp);
			return 0;
		}


		if (fwrite(ptrImage, 1, bitsize, fp) < bitsize ) {
			free(ptrImage);
			fclose(fp);
			return 0;
		}

		fclose(fp);
		free(ptrImage);

		return 1;
}

int saveSVG(const char *filename, int winWidth, int winHeight) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)  return EXIT_FAILURE;

	char line[255];
	int width, height; //store calculated height and width

	//write header data for SVG
	sprintf(line, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(line, fp);
	sprintf(line, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(line, fp);
	sprintf(line, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(line, fp);
	sprintf(line,
			"<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			winWidth, winHeight);
	fputs(line, fp);

	// traverse through object list and a line for each object
	// need to convert the rectangal/circle data to SVG rect/circle data

    // your implementation
	NODE *curr = objlist.start;
	int fr,fb,fg,sr,sb,sg;


	while(curr){
		SHAPE *shape = curr->object;
		//Values of fr... are either 1.0 or 0.0, 1.0 means 100% of the colour, 0.0 menas 0%. Multiplying it by 255 we can use the RGB(255,255,255) format.
		fr = (int) (curr->object->fr * 255); fb = (int) (curr->object->fb * 255); fg = (int) (curr->object->fg * 255);
		sr = (int) (curr->object->sr * 255); sb = (int) (curr->object->sb * 255); sg = (int) (curr->object->sg * 255);

		if(shape->type == 1)//Rectangle
			sprintf(line,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" storke-width=\"%d\" />\n",
					min(shape->x1,shape->x2),min(shape->y1,shape->y2), abs(shape->x1-shape->x2), abs(shape->y1-shape->y2),fr,fg,fb,sr,sg,sb,shape->swidth);

		else if(shape->type == 2) //Circle
			sprintf(line,"<circle cx=\"%d\" cy=\"%d\" r=\"%f\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\" />\n",
					shape->x1,shape->y1,sqrt((shape->x2-shape->x1)*(shape->x2-shape->x1)+(shape->y2-shape->y1)*(shape->y2-shape->y1)),fr,fg,fb,sr,sg,sb,shape->swidth);


		fputs(line,fp);
		curr = curr->next;
	}

	sprintf(line, "</svg>\n");
	fputs(line, fp);
	fclose(fp);

	return EXIT_SUCCESS;
}

int openSVG(const char *filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) return EXIT_FAILURE;

	int lineLength = 255;
	char line[lineLength];
	int x1, y1, w, h, fr, fg, fb, sr, sg, sb, sw; // variables to hold scan values

	// read line by line, if it is line of rect/circle element, retrieve the attribute values and convert them to
	// object values and create object and insert to the object list.

	while ( fgets(line, lineLength, fp)) {
		//printf("%s\n", buffer);
		SHAPE *shapeObj;
		if (line[0] == '<' && line[1] == 'r' ) { // rectangle
			sscanf(line,
					"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
					&x1, &y1, &w, &h, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

			shapeObj = (SHAPE*) malloc(sizeof(SHAPE));
			shapeObj->type = RECTANGLE;
			shapeObj->x1 = x1;
			shapeObj->y1 = y1;
			shapeObj->x2 = x1 + w;
			shapeObj->y2 = y1 + h;
			shapeObj->fr = fr / 255;
			shapeObj->fg = fg / 255;
			shapeObj->fb = fb / 255;
			shapeObj->sr = sr / 255;
			shapeObj->sg = sg / 255;
			shapeObj->sb = sb / 255;
			shapeObj->swidth = sw;
			insert(&objlist, shapeObj);

		} else if (line[0] == '<' && line[1] == 'c' )  {
			// ....
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

