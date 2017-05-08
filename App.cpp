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
	block = loadTexture("..\\resources\\wall.bmp");
	dog = loadTexture("..\\resources\\doggo.bmp");

     // Title/End Screens
     title = loadTexture("..\\resources\\title_screen_1.bmp");
     // end = loadTexture("..\\resources\\");

	#else
     //Game Environment
	floor = loadTexture("resources/ground2.bmp");
	cld = loadTexture("resources/cloud.bmp");
	bkgd = loadTexture("resources/bkgd.bmp");
	bkgdHills = loadTexture("resources/bkgdHills.bmp");
	block = loadTexture("resources/trampoline.bmp");
	dog = loadTexture("resources/doggo.bmp");

     // Title/End Screens
     title = loadTexture("resources/title_screen_1.bmp");
     // end = loadTexture("resources/");

	#endif

     // Game Environment Objects
     background = new TexRect(-1, 1, 2, 2);
     ground = new TexRect(-1.0, -0.9, 2.0, 0.1);
	cloud = new TexRect(0.05, 0.7, 0.35, 0.70);
	hills = new Background(-1.0, -0.6, 2.0, 0.3);
	trampoline = new Block(0.25, -0.6, 0.23, 0.3);
	doggo = new Doggo(-0.5, -0.5, 0.3, 0.4);

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
    else if(!gameOver)
    {
     	glBindTexture(GL_TEXTURE_2D,block);
     	trampoline->draw();

     	glBindTexture(GL_TEXTURE_2D, dog);
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

	if(key == GLUT_KEY_LEFT)
	{
		left = true;
		right = false;
		Movement = 1;

          #if defined WIN32
          dog = loadTexture("..\\resources\\Doggo_2.bmp");
          #else
          dog = loadTexture("resources/Doggo_2.bmp");
          #endif
	}

     if(key == GLUT_KEY_RIGHT)
	{
		right = true;
		left = false;
		Movement = 2;

          #if defined WIN32
          dog = loadTexture("..\\resources\\doggo.bmp");
          #else
          dog = loadTexture("resources/doggo.bmp");
          #endif
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

bool App::xCollision()
{
	// if(mov == 1) // Moving Left
	// {
	// 	if((trampoline->getX() <= doggo->getR() && trampoline->getX() >= doggo->getX())
     //           && trampoline->getY() > doggo->getB()) {
	// 		return 1;
     //      }
	// 	else{
	// 		return 0;
     //      }
	// }
	// else if(mov == 2) // Moving Right
	// {
	// 	if ( (trampoline->getX() <= doggo->getX() && trampoline->getR() >= doggo->getX() )
     //           && trampoline->getY() > doggo->getB()) {
	// 		return 1;
     //      }
	// 	else{
	// 		return 0;
     //      }
	// }

     if
     (    ( trampoline->getX() <= doggo->getR() &&
          trampoline->getX() >= doggo->getX() ) ||
          ( trampoline->getR() <= doggo->getR() &&
          trampoline->getR() >= doggo->getX() ))
     {
          return 1;
     }else{
          return 0;
     }
}

bool App::yCollision()
{
     if(doggo->getB() <= trampoline->getY())
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
     		trampoline->updateCoords(trampoline->getX() + 0.01);

     		if (xCollision() && yCollision())
     		{
     			hills->updateTexCoords(hills->getTL() + 0.005, hills->getTR() + 0.005);
                    trampoline->updateCoords(trampoline->getX() - 0.01);
     		}
               else if(trampoline->getY() <= doggo->getB() && xCollision())
               {
                    doggo->updateGroundLevel(trampoline->getY() + doggo->getH());
                    doggo->isJumping = 1;
               }
               else
                    doggo->updateGroundLevel(-0.5);
     	}

     	if (right)
     	{
     		hills->move(Movement);
     		trampoline->updateCoords(trampoline->getX() - 0.01);

     		if (xCollision() && yCollision())
     		{
                    hills->updateTexCoords(hills->getTL() - 0.005, hills->getTR() - 0.005);
     			trampoline->updateCoords(trampoline->getX() + 0.01);

     			// if (doggo->isJumping){
     			// 	doggo->setY(trampoline->getY() + doggo->getH());
     			// }
     			// else {
     			// 	hills->updateTexCoords(hills->getTL() - 0.005, hills->getTR() - 0.005);
     			// 	trampoline->updateCoords(trampoline->getX());
     			// }
     		}
               else if(trampoline->getY() <= doggo->getB() && xCollision())
               {
                    doggo->updateGroundLevel(trampoline->getY() + doggo->getH());
                    doggo->isJumping = 1;
               }
               else
                    doggo->updateGroundLevel(-0.5);

     	}
     }

	redraw();
}











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
