#include "Chocolate.h"

Chocolate::Chocolate(float x, float y, float w, float h) : Block(x, y, w, h) { }

void Chocolate::event(bool top)
{
     // Not sure how to handle events yet, but Chocolate
     // objects should not care about where the Objects
     // collide, it should seek to end the game upon any
     // instance of collision
}
