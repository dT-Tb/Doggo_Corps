#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "Background.h"

class Block : public TexRect
{
	float x, xLeft,xRight;
	float y;
	float w;
	float h;
public:

	Block(float x, float y, float w, float h);

	bool contains(float obj1, float obj2);
	void updateCoords(float xl, float xr);
	void draw() {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(xLeft, y - h);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(xLeft, y);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(xRight, y);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(xRight, y - h);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	/*void updateTexCoords(float tl, float tr);
	void draw(){
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBegin(GL_QUADS);

		glTexCoord2f(texleft, 0.0);
		glVertex2f(x, y - h);

		glTexCoord2f(texleft, 1.0);
		glVertex2f(x, y);

		glTexCoord2f(texright, 1.0);
		glVertex2f(x + w, y);

		glTexCoord2f(texright, 0.0);
		glVertex2f(x + w, y - h);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}*/


	float getL() { return xLeft; }
	float getR() { return xRight; }
<<<<<<< HEAD
=======

	float getT() { return y; }
>>>>>>> origin/master
};

#endif
