#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "TexRect.hpp"

class Background : public TexRect
{
private:

	float texleft, texright;
public:

	Background(float x = 0, float y = 0, float w = 0.5, float h = 0.5, float tl = 0, float tr = 0.5);

	void updateTexCoords(float tl, float tr);
	void draw();
	void move(int m);

	float getTL() { return texleft; }
	float getTR() { return texright; }
};
#endif
