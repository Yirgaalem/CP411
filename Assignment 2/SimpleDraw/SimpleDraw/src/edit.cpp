/*
 * Description: implementation of edit.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "object.hpp"

extern LIST objlist;

GLint min(GLint x, GLint y) {
	return x < y ? x : y;
}

GLint max(GLint x, GLint y) {
	if (x < y)
		return y;
	else
		return x;
}

NODE *select(GLint x, GLint y) {
	// your implementation
    // search the object that cover the clicking point staring
	NODE *node = objlist.end;

	while(node){
		//Rectangle
		if(node->object->type == 1 && max(node->object->x1,node->object->x2) > x && min(node->object->x1,node->object->x2) < x && max(node->object->y1,node->object->y2) > y && min(node->object->y1,node->object->y2) < y)
			break;

		//Circle
		else if(node->object->type == 2){
			GLint rSquared = (GLint) (node->object->x2 - node->object->x1) * (node->object->x2 - node->object->x1) + (node->object->y2 - node->object->y1) * (node->object->y2 - node->object->y1);

			if((x-node->object->x1) * (x - node->object->x1) + (y - node->object->y1) * (y - node->object->y1) < rSquared)
				break;

		}
		node = node->prev;
	}

	return node;

}

void Delete(NODE **pp) {

	deleteNode(&objlist, pp);
}

void moveFront(NODE *p) {
	// your implementation

	if(p==NULL || p ==objlist.end)
		return;

	if(p == objlist.start){
		p->next->prev = NULL;
		objlist.start = p->next;

	} else{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}

	p->prev = objlist.end;
	p->next = NULL;
	objlist.end->next = p;
	objlist.end = p;

}

void moveBack(NODE *p) {
	// your implementation
	if(p==NULL || p ==objlist.start)
		return;

	if(p == objlist.end){
		p->prev->next = NULL;
		objlist.end = p->prev;

	} else{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	p->next = objlist.start;
	p->prev = NULL;
	objlist.start->prev = p;
	objlist.start = p;
}



