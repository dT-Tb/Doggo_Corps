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

     // boolean flags to denote current game state
     bool started = 0;
     bool gameOver = 0;
     bool titleAnim = 0; // for animating the title screen

     //boolean flags to denote movement
     bool left = false;
     bool right = false;
public:
     // Constructor, to initialize state
     App(const char* label, int x, int y, int w, int h);


     // These are the events we want to handle
     void draw();
     void drawTitleScreen();
     void drawEndScreen();
     void keyPress(unsigned char key);
     void keyUp(unsigned char key){}
     void mouseDown(float x, float y);
     void mouseDrag(float x, float y);
     void specialKeyPress(int key);
     void specialKeyUp(int key);
	void idle();

     // Collision checks for respective dimensions
     bool xCollision();
     bool yCollision();

     GLuint loadTexture(const char* filename);

     // Environment
     GLuint floor;
     GLuint bkgd;
	GLuint cld;
	GLuint bkgdHills;
	GLuint block;
	GLuint dog;

     // Title/End Screens
     GLuint title;
     GLuint end;

     // Environment Objects
     TexRect* ground;
     TexRect* background;
	TexRect* cloud;
	Background* hills;
	Block* trampoline;
	Doggo* doggo;

     // Title/End Objects
     TexRect* titleScreen;
     TexRect* endScreen;
};

#endif
