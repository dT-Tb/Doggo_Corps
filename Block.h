#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "Background.h"

class Block : public TexRect
{
public:
	Block(float x, float y, float w, float h);
	
	void updateCoords(float x_update);
};

#endif
