#pragma once
#ifndef DOGGO_H
#define DOGGO_H

#include "TexRect.hpp"

class Doggo : public TexRect
{
	float yMult, groundLevel;
	// yMult is for jumping acceleration

public:

	// Boolean values for jump state, isJumping is for rising
	// and jumpReset is for falling
	bool isJumping = 0;
	bool jumpReset = 0;

	Doggo(float x, float y, float w, float h);

	// Doggo Position Functions
	void gravity();
	void jump();
	void updateGroundLevel(float glvl);
};

#endif
