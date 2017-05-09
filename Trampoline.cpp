#include "Trampoline.h"

Trampoline::Trampoline(float x, float y, float w, float h, GLuint texture) : Block(x, y, w, h, texture) {}

void Trampoline::event(bool top, Doggo* d)
{
     if(top){
          //Not sure how to handle events, want it
          // To only register when the object is on top
          // of the Trampoline, as denoted by the bool
          printf("Trampoline event\n");
          d->isJumping = 1;
     }
}
