#include "Chocolate.h"

Chocolate::Chocolate(float x, float y, float w, float h, GLuint texture) : Block(x, y, w, h, texture) { }

void Chocolate::event(bool top, Doggo* d)
{
     // Not sure how to handle events yet, but Chocolate
     // objects should not care about where the Objects
     // collide, it should seek to end the game upon any
     // instance of collision
     printf("Chocolate event\n");
     d->die();
}
