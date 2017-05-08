#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "Background.h"

class Block : public TexRect
{
	float xLeft,xRight;
public:

	Block(float x, float y, float w, float h);

	bool contains(float obj1, float obj2);
	void updateCoords(float x_update);
};

#endif
