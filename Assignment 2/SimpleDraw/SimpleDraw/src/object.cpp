/*
 * Description: implementation of object.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "object.hpp"

void insert(LIST *list, SHAPE *object) {
	NODE* node = (NODE *)malloc(sizeof(NODE));
	node->object = object;
	node->next = NULL; node->prev = NULL;

	if(list->start == NULL && list->end == NULL){
		list->start = node;
		list->end = node;

	} else {
		list->end->next = node;
		node->prev = list->end;
		list->end = node;
	}

}

void deleteNode(LIST *list, NODE **selectp) {

	if(list->start == list->end){ //1 node in list
		list->start = NULL;
		list->end = NULL;
	}
	else if(list->start == (*selectp)) //If deleted Node is at front of list

		if(list->start == list->end)//If only item in listW
			list->start = NULL;

		else{
			list->start = (*selectp)->next;
			list->start->prev = NULL;
		}

	else if(list->end == (*selectp)){
		list->end = (*selectp)->prev;
		list->end->next = NULL;
	}
	else
		(*selectp)->prev = (*selectp)->next;

	free((*selectp));
}

void clearList(LIST *list) {
// ...
	NODE *curr = list->start, *hold;
	while(curr){
		hold = curr->next;
		free(curr);
		curr = hold;
	}
	list->start = list->end = NULL;

}

void drawShape(SHAPE *object) {
	if (object->type == RECTANGLE) {
		// draw filled rectangle
		// draw outline
		glColor3f(object->fr, object->fg, object->fb);


		glBegin(GL_POLYGON);
			glVertex2i(object->x1,object->y1);
			glVertex2i(object->x2,object->y1);
			glVertex2i(object->x2,object->y2);
			glVertex2i(object->x1,object->y2);
		glEnd();

		glColor3f(object->sr, object->sg, object->sb);
		glLineWidth(object->swidth);

		glBegin(GL_LINE_LOOP);
			glVertex2i(object->x1,object->y1);
			glVertex2i(object->x2,object->y1);
			glVertex2i(object->x2,object->y2);
			glVertex2i(object->x1,object->y2);
		glEnd();



	} else if (object->type == CIRCLE) {
		// draw filled circle
		// draw outline
		//(x1,y1) is the center
		glColor3f(object->fr, object->fg, object->fb);
		circleMidpointFill(object->x1,object->y1,object->x2,object->y2);

		glPointSize(object->swidth);
		glColor3f(object->sr,object->sg, object->sb);
		circleMidpoint(object->x1,object->y1,object->x2,object->y2);

	}

}

void drawShapeHighLight(SHAPE *object) {
	// draw outline with high light color
	glColor3f(1.0, 1.0, 0);
	if(object->type == RECTANGLE){
		glBegin(GL_LINE_LOOP);
				glVertex2i(object->x1,object->y1);
				glVertex2i(object->x2,object->y1);
				glVertex2i(object->x2,object->y2);
				glVertex2i(object->x1,object->y2);
		glEnd();
	}

	else if(object->type == CIRCLE)
		circleMidpoint(object->x1,object->y1,object->x2,object->y2);

}

void drawList(LIST *list) {
	NODE *p = list->start;
	while (p) {
		drawShape(p->object);
		p = p->next;
	}
}

void setPixel(GLint x, GLint y) {
	//glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x,
		const GLint& y) {


	setPixel(xc + x, yc + y); setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y); setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x); setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x); setPixel(xc - y, yc - x);

}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint p = 1 - x2, x = 0, r = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	circlePlotPoints(x1,y1,x,r);

	while(x < r){// while we havent reached radius yet
		x++;

		if(p < 0)
			p += 2 * x + 1;

		else{
			r--;
			p += 2 * (x-r) + 1;
		}

		circlePlotPoints(x1,y1,x,r);

	}

}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2i(x1 - x, y1 + y); glVertex2i(x1 + x, y1 + y);
		glVertex2i(x1 - x, y1 - y); glVertex2i(x1 + x, y1 - y);
		glVertex2i(x1 - y, y1 + x); glVertex2i(x1 + y, y1 + x);
		glVertex2i(x1 - y, y1 - x); glVertex2i(x1 + y, y1 - x);
	glEnd();
}
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint p = 1 - x2, x = 0, r = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	circlePlotPointsFill(x1,y1,x,r);

	while(x < r){// while we havent reached radius yet
		x++;
		if(p < 0)
			p += 2 * x + 1;

		else{
			r--;
			p += 2 * (x-r) + 1;
		}

		circlePlotPointsFill(x1,y1,x,r);

	}

}
