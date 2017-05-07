#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"
#include "Doggo.h"
#include "Background.h"
#include "Block.h"

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    //bool movements
    bool left;
    bool right;
    bool up;
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    void specialKeyPress(int key);
    void specialKeyUp(int key);
    bool contains(int m);
	void idle();
    
    GLuint loadTexture(const char* filename);
    
    GLuint floor;
    GLuint bkgd;
	GLuint cld;
	GLuint bkgdHills;
	GLuint blk;
	GLuint dog;
    
    
    TexRect* ground;
    TexRect* background;
	TexRect* cloud;
	Background* hills;
	Block* block;
	Doggo* doggo;
};

#endif
