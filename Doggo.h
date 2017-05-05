#pragma once
#ifndef DOGGO_H
#define DOGGO_H

#include "TexRect.hpp"

class Doggo : public TexRect
{
	float x;
	float y, yMult;
	float w;
	float h;

public:
	bool isJumping = 0;
	bool jumpReset = 0;

	Doggo(float x, float y, float w, float h);

	//void updateVals(float x, float y, float w, float h); // move this to correct subclass
	void gravity();
	void jump();
	int move(float a);

	void draw() {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(x, y - h);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(x, y);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w, y);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(x + w, y - h);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	float getY() const { return y; }
	float getXL() const { return x; }
	float getXR() const { return x + w; }

	float getH() const { return h; }

	float getB() const { return y - h; }

	void setY(float v) { y = v; }

};

#endif
