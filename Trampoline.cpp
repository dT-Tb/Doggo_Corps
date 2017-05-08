#include "Trampoline.h"

Trampoline::Trampoline(float x, float y, float w, float h) : Block(x, y, w, h) {}

void Trampoline::event(bool top)
{
     if(top){
          //Not sure how to handle events, want it 
          // To only register when the object is on top
          // of the Trampoline, as denoted by the bool
     }
}
