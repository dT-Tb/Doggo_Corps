#include "Doggo.h"
#define MAX_JUMP_SPEED 0.2

Doggo::Doggo(float x, float y, float w, float h) : TexRect(x, y, w, h)
{
	setX(x);
	setY(y);
	setW(w);
	setH(h);

	yMult = MAX_JUMP_SPEED;
	groundLevel = -0.5;
}

void Doggo::gravity()
{
	setY(getY() - 0.03);
	if (getY() <= groundLevel)
	{
		if (jumpReset)
		{
			jumpReset = 0;
			yMult = MAX_JUMP_SPEED;
		}

		setY(groundLevel);
	}

}

void Doggo::jump()
{
	if(yMult >= 0)
	{
		setY(getY() + yMult);
		yMult -= MAX_JUMP_SPEED * 0.085;
	}
	else{
		isJumping = 0;
		jumpReset = 1;
	}
}

void Doggo::updateGroundLevel(float glvl)
{
	groundLevel = glvl;
}

int Doggo::move(float a)
{
	if (a == 'a')
		return 1;
	if (a == 'd')
		return 2;
	else
		return 0;
}
