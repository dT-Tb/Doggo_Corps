#include "Block.h"

Block::Block(float x, float y, float w, float h, GLuint texture) : TexRect(x, y, w, h)
{
	// setX(x);
	// setY(y);
	// setW(w);
	// setH(h);
	this->texture = texture;
}

void Block::updateCoords(float x_update)
{
	setX(x_update);
}

void Block::move(int mov)
{
	if(mov == 1)
		updateCoords(getX() + 0.018);

	else if(mov == 2)
		updateCoords(getX() - 0.018);
}
