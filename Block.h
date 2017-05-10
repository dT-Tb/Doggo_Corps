#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "TexRect.hpp"

class Block : public TexRect
{
	GLuint texture;

public:
	Block(float x, float y, float w, float h, GLuint texture);

	void updateCoords(float x_update);
	void move(int mov);

	GLuint getTexId() const { return texture; }
};

#endif
