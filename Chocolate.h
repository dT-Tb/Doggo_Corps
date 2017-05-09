#include "Block.h"

class Chocolate : public Block
{
public:
     Chocolate(float x, float y, float w, float h, GLuint texture);

     void event(bool top, Doggo* d);
};
