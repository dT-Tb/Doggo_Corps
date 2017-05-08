#pragma once
#ifndef DOGGO_H
#define DOGGO_H

#include "TexRect.hpp"

class Doggo : public TexRect
{
	float yMult, groundLevel;
	bool dead = 0;

public:
	bool isJumping = 0;
	bool jumpReset = 0;

	Doggo(float x, float y, float w, float h);

	//void updateVals(float x, float y, float w, float h); // move this to correct subclass
	void gravity();
	void jump();
	void updateGroundLevel(float glvl);
	int move(float a);
	void die(){ dead = 1; }

	float getGLevel() const { return groundLevel; }
	bool isDead() const { return dead; }
};

#endif
