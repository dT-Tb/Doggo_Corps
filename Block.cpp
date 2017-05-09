#include "Block.h"

Block::Block(float x, float y, float w, float h, GLuint texture) : TexRect(x, y, w, h)
{
	this->texture = texture;
}

void Block::updateCoords(float x_update)
{
	setX(x_update);
}

void Block::move(int mov)
{
	if(mov == 1)
		updateCoords(getX() + 0.023);

	else if(mov == 2)
		updateCoords(getX() - 0.023);
}
