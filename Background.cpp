#include "Background.h"

Background::Background(float x, float y, float w, float h, float tl, float tr) : TexRect(x, y, w, h)
{
	setX(x);
	setY(y);
	setW(w);
	setH(h);

	texleft = tl;
	texright = tr;
}

void Background::updateTexCoords(float tl, float tr)
{ // move this to correct subclass
		texleft = tl;
		texright = tr;
}

void Background::draw()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_QUADS);

	glTexCoord2f(texleft, 0.0);
	glVertex2f(getX(), getY() - getH());

	glTexCoord2f(texleft, 1.0);
	glVertex2f(getX(), getY());

	glTexCoord2f(texright, 1.0);
	glVertex2f(getX() + getW(), getY());

	glTexCoord2f(texright, 0.0);
	glVertex2f(getX() + getW(), getY() - getH());

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Background::move(int m)
{
	if(m == 1)
		updateTexCoords(getTL() - 0.008, getTR() - 0.008);

	else if(m == 2)
		updateTexCoords(getTL() + 0.008, getTR() + 0.008);
}
