#include "Chocolate.h"

Chocolate::Chocolate(float x, float y, float w, float h) : Block(x, y, w, h) { }

void Chocolate::event(bool top)
{
     doggo->die();
}
