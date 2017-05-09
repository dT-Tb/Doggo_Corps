#ifndef App_h
#define App_h
#include<iostream>
#include<vector>
#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"
#include "Doggo.h"
#include "Background.h"
#include "Trampoline.h"
#include "Chocolate.h"
using namespace std;
class App: public GlutApp {
     // Maintain app state here
     float mx;
     float my;

     // boolean flags to denote current game state
     bool started = 0;
     bool gameIsOver = 0;
     bool titleAnim = 0; // for animating the title screen

     //boolean flags to denote movement
     bool left = false;
     bool right = false;
     bool texLeftDir = 0;
     bool texRightDir = 1; // Default set to right
public:
     // Constructor, to initialize state
     App(const char* label, int x, int y, int w, int h);


     // These are the events we want to handle
     void gameOver(){ gameIsOver = 1; }
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
     template <typename T> bool xCollision(T*);
     template <typename T> bool yCollision(T*);

     GLuint loadTexture(const char* filename);

     // Environment
     GLuint floor;
     GLuint bkgd;
	GLuint cld;
	GLuint bkgdHills;
	GLuint jumpBlock;
     GLuint killBlock;
	GLuint dogLeft;
     GLuint dogRight;

     // Title/End Screens
     GLuint title;
     GLuint end;

     // Environment Objects
     TexRect* ground;
     TexRect* background;
	TexRect* cloud;
	Background* hills;
	Trampoline* trampoline;
     Chocolate* chocolate;
	Doggo* doggo;
	vector<Block*>B;
     // Title/End Objects
     TexRect* titleScreen;
     TexRect* endScreen;
};

#endif
