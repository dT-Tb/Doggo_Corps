#include "App.h"
#include <cstdio>
#define MAX_JUMP_HEIGHT 0.9

static int Movement = 0;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;

	#if defined WIN32
     // Game Environment
     floor = loadTexture("..\\resources\\ground2.bmp");
     bkgd = loadTexture("..\\resources\\bkgd.bmp");
	cld = loadTexture("..\\resources\\cloud.bmp");
	bkgdHills = loadTexture("..\\resources\\bkgdHills.bmp");
	jumpBlock = loadTexture("..\\resources\\wall.bmp");
     killBlock = loadTexture("..\\resources\\chocolate.bmp");
     dogLeft = loadTexture("..\\resources\\doggo_2.bmp");
	dogRight = loadTexture("..\\resources\\doggo.bmp");

     // Title/End Screens
     title = loadTexture("..\\resources\\title_screen_1.bmp");
     // end = loadTexture("..\\resources\\");

	#else
     //Game Environment
	floor = loadTexture("resources/ground2.bmp");
	cld = loadTexture("resources/cloud.bmp");
	bkgd = loadTexture("resources/bkgd.bmp");
	bkgdHills = loadTexture("resources/bkgdHills.bmp");
	jumpBlock = loadTexture("resources/trampoline.bmp");
     killBlock = loadTexture("resources/chocolate.bmp");
     dogRight = loadTexture("resources/doggo.bmp");
     dogLeft = loadTexture("resources/doggo_2.bmp");

     // Title/End Screens
     title = loadTexture("resources/title_screen_1.bmp");
     // end = loadTexture("resources/");

	#endif

     // Game Environment Objects
     background = new TexRect(-1, 1, 2, 2);
     ground = new TexRect(-1.0, -0.9, 2.0, 0.1);
	cloud = new TexRect(0.05, 0.7, 0.35, 0.70);
	hills = new Background(-1.0, -0.6, 2.0, 0.3);
	//trampoline = new Trampoline(0.25, -0.6, 0.23, 0.3);
     chocolate = new Chocolate(0.75, -0.55, 0.17, 0.35);
	doggo = new Doggo(-0.5, -0.5, 0.3, 0.4);

	B.push_back(new Trampoline(0.25, -0.6, 0.23, 0.3));
	B.push_back(new Trampoline(0.85, -0.6, 0.23, 0.3));	
	
     // Title/End Screen Objects
     titleScreen = new TexRect(-1, 1, 2, 2);
     // endScreen = new TexRect(-1, 1, 2, 2);
}


GLuint App::loadTexture(const char *filename) {
    GLuint texture_id;
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    RgbImage theTexMap( filename );

    // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
    //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

	 return texture_id;
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set Color
    glColor3d(1.0, 1.0, 1.0);

    if(!started)
    {
         drawTitleScreen();
    }
    else if(!gameIsOver)
    {
    	for(int i = 0; i < B.size(); i++)
    	{
     		glBindTexture(GL_TEXTURE_2D, jumpBlock);
     		B[i]->draw();
     	}

          glBindTexture(GL_TEXTURE_2D, killBlock);
          chocolate->draw();

          if(texLeftDir){
               glBindTexture(GL_TEXTURE_2D, dogLeft);
          }
          else if(texRightDir){
               glBindTexture(GL_TEXTURE_2D, dogRight);
          }
          doggo->draw();

          glBindTexture( GL_TEXTURE_2D, floor );
          ground->draw();

     	glBindTexture( GL_TEXTURE_2D, cld );
          cloud->draw();

     	glBindTexture( GL_TEXTURE_2D, bkgdHills );
        	hills->draw();

          glBindTexture( GL_TEXTURE_2D, bkgd );
          background->draw();
    }
    else
    {
         drawEndScreen();
    }

    glDisable(GL_TEXTURE_2D);

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::drawTitleScreen()
{
     if(titleAnim)
     {
          #if defined WIN32
          title = loadTexture("..\\resources\\title_screen_2.bmp");
          #else
          title = loadTexture("resources/title_screen_2.bmp");
          #endif

          titleAnim = 0;
     }
     else
     {
          #if defined WIN32
          title = loadTexture("..\\resources\\title_screen_1.bmp");
          #else
          title = loadTexture("resources/title_screen_1.bmp");
          #endif

          titleAnim = 1;
     }

     glBindTexture(GL_TEXTURE_2D, title);
     titleScreen->draw();
}

void App::drawEndScreen()
{
     glBindTexture(GL_TEXTURE_2D, end);
     endScreen->draw();
}

void App::keyPress(unsigned char key) {
#define ESC 27
#define SPACEBAR 32


     if (key == ESC) {
          // Exit the app when Esc key is pressed
          exit(0);
     }

	if (!started && key == SPACEBAR) {
          started = 1;
	}

	redraw();
}

void App::specialKeyPress(int key)
{
     if(key == GLUT_KEY_UP)
     {
          doggo->isJumping = 1;
     }

	if(key == GLUT_KEY_LEFT && !left)
	{
		left = true;
		right = false;
		Movement = 1;
          texLeftDir = 1;
          texRightDir = 0;
	}

     if(key == GLUT_KEY_RIGHT && !right)
	{
		right = true;
		left = false;
		Movement = 2;
          texLeftDir = 0;
          texRightDir = 1;
	}

	if(key == GLUT_KEY_DOWN)
	{
		right = false;
		left = false;
		Movement = 0;
	}
}

void App::specialKeyUp(int key)
{
	if(key == 100)
	{
		left = false;
		Movement = 0;
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		right = false;
		Movement = 0;
	}
}

template <typename T> bool App::xCollision(T* block)
{
     if
     (    ( block->getX() <= doggo->getR() &&
          block->getX() >= doggo->getX() ) ||
          ( block->getR() <= doggo->getR() &&
          block->getR() >= doggo->getX() ))
     {
          return 1;
     }else{
          return 0;
     }
}

template <typename T> bool App::yCollision(T*block)
{
     if(doggo->getB() <= block->getY())
          return 1;
     else
          return 0;
}

void App::idle()
{
     if(started)
     {
     	doggo->gravity();

     	if(doggo->isJumping)
     	{
     		if(doggo->getY() <= 0.5 && !doggo->jumpReset)
     		{
     			doggo->jump();
     		}
     		else
     		{
     			doggo->isJumping = 0;
     			doggo->jumpReset = 1;
     		}
     	}

     if (left)
     	{

     		hills->move(Movement);
     		for(int i = 0; i < B.size(); i++)
     		{
     			B[i]->updateCoords(B[i]->getX() + 0.02);
     		}
     		//trampoline->updateCoords(trampoline->getX() + 0.02);
               chocolate->updateCoords(chocolate->getX() + 0.02);
			for(int i = 0; i<B.size(); i++)
			{
     			if (xCollision(B[i]) && yCollision(B[i]))
     			{
     				hills->updateTexCoords(hills->getTL() + 0.005, hills->getTR() + 0.005);
                   	B[i]->updateCoords(B[i]->getX() - 0.02);
     			}
               	else if(B[i]->getY() <= doggo->getB() && xCollision(B[i]))
               	{
                    doggo->updateGroundLevel(B[i]->getY() + doggo->getH());
                    doggo->isJumping = 1;
               	}
               else
                    doggo->updateGroundLevel(-0.5);
     			}
     		}

     	if (right)
     	{
     		hills->move(Movement);
     		for(int i = 0; i < B.size(); i++)
     		{
     			B[i]->updateCoords(B[i]->getX() - 0.02);
     		}
     		//trampoline->updateCoords(trampoline->getX() - 0.02);
               chocolate->updateCoords(chocolate->getX() - 0.02);
			for(int i = 0; i<B.size(); i++)
			{
     			if (xCollision(B[i]) && yCollision(B[i]))
     			{
                    hills->updateTexCoords(hills->getTL() - 0.005, hills->getTR() - 0.005);
     				B[i]->updateCoords(B[i]->getX() + 0.02);
     			}
               	else if(B[i]->getY() <= doggo->getB() && xCollision(B[i]))
               	{
                    doggo->updateGroundLevel(B[i]->getY() + doggo->getH());
                    doggo->isJumping = 1;
               	}
               else
                    doggo->updateGroundLevel(-0.5);
          		} // if(right) end if
          	
     			} // if(started) endif
     		}


	redraw();
} // idle() end function











// These are not used -- so far --
void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;

    // Redraw the scene
    redraw();
}
