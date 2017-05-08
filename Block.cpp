#include "Block.h"

Block::Block(float x, float y, float w, float h) : TexRect(x, y, w, h)
{
	setX(x);
	setY(y);
	setW(w);
	setH(h);
}

void Block::updateCoords(float x_update)
{
	setX(x_update);
}
