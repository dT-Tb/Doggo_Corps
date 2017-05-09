#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "TexRect.hpp"
#include "Doggo.h"
#include <cstdio>

class Block : public TexRect
{
	GLuint texture;

public:
	Block(float x, float y, float w, float h, GLuint texture);

	void updateCoords(float x_update);
	void move(int mov);
	virtual void event(bool top, Doggo* d) { }

	GLuint getTexId() const { return texture; }
};

#endif
