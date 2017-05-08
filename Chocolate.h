#include "Block.h"

class Chocolate : public Block
{
public:
     Chocolate(float x, float y, float w, float h);

     void event(bool top);
};
