#include "Doggo.h"
#define MAX_JUMP_SPEED 0.2f

//void Doggo::updateVals(float x, float y, float w, float h)
//{
//	this->x = x;
//	this->y = y;
//	this->w = w;
//	this->h = h;
//}

Doggo::Doggo(float x, float y, float w, float h)
{
	this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
	TexRect(x, y, w, h);

	yMult = MAX_JUMP_SPEED;
}

void Doggo::gravity()
{
	y -= 0.05f;

	if (y < -0.5f)
	{
		if (jumpReset)
		{
			jumpReset = 0;
			yMult = MAX_JUMP_SPEED;
		}

		y = -0.5;
	}

	TexRect(x, y, w, h);
}

void Doggo::jump()
{
	y += yMult;
	yMult *= 2.60;

	TexRect(x, y, w, h);
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
