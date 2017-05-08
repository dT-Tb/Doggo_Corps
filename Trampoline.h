#include "Block.h"

class Trampoline : public Block
{
public:
     Trampoline(float x, float y, float w, float h);

     void event(bool top);
};
