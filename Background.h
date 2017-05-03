#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "TexRect.hpp"

class Background : public TexRect
{
private:

	float texleft, texright, x, y, w, h;
public:

	Background(float x = 0, float y = 0, float w = 0.5, float h = 0.5, float tl = 0, float tr = 0.5)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		texleft = tl;
		texright = tr;
	}

	void updateTexCoords(float tl, float tr) { // move this to correct subclass
		texleft = tl;
		texright = tr;
	}

	void draw() {
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
	}

	float getTL() { return texleft; }
	float getTR() { return texright; }

};
#endif
