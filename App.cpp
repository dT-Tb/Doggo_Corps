#include "App.h"
#include <cstdio>
#define MAX_JUMP_HEIGHT 0.9

static int Movement = 0;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;

	#if defined WIN32
    floor = loadTexture("..\\resources\\ground2.bmp");
    bkgd = loadTexture("..\\resources\\bkgd.bmp");
	cld = loadTexture("..\\resources\\cloud.bmp");
	bkgdHills = loadTexture("..\\resources\\bkgdHills.bmp");
	blk = loadTexture("..\\resources\\wall.bmp");
	dog = loadTexture("..\\resources\\doggo_2.bmp");
	#else
	floor = loadTexture("resources/ground2.bmp");
	cld = loadTexture("resources/cloud.bmp");
	bkgd = loadTexture("resources/bkgd.bmp");
	bkgdHills = loadTexture("resources/bkgdHills.bmp");
	blk = loadTexture("resources/wall.bmp");
	dog = loadTexture("resources/doggo_2.bmp");
	#endif

    background = new TexRect(-1, 1, 2, 2);
    ground = new TexRect(-1.0, -0.9, 2.0, 0.1);
	cloud = new TexRect(-0.7, 0.7, 0.35, 0.70);
	hills = new Background(-1.0, -0.6, 2.0, 0.3);
	block = new Block(-0.25, -0.6, 0.15, 0.3);
	block = new Block(0.25, -0.6, 0.15, 0.3);
	doggo = new Doggo(-0.5, -0.5, 0.2, 0.4);
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

	glBindTexture(GL_TEXTURE_2D,blk);
	block->draw();

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


    glDisable(GL_TEXTURE_2D);

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::keyPress(unsigned char key) {
#define ESC 27
#define SPACEBAR 32

    if (key == ESC) {
        // Exit the app when Esc key is pressed
        exit(0);
    }
	if (key == SPACEBAR) {
		left = 0;
          right = 0;
          Movement = 0;
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
	}

     if(key == GLUT_KEY_RIGHT)
	{
		right = true;
		left = false;
		Movement = 2;
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
	// 	if((block->getX() <= doggo->getR() && block->getX() >= doggo->getX())
     //           && block->getY() > doggo->getB()) {
	// 		return 1;
     //      }
	// 	else{
	// 		return 0;
     //      }
	// }
	// else if(mov == 2) // Moving Right
	// {
	// 	if ( (block->getX() <= doggo->getX() && block->getR() >= doggo->getX() )
     //           && block->getY() > doggo->getB()) {
	// 		return 1;
     //      }
	// 	else{
	// 		return 0;
     //      }
	// }

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

bool App::yCollision()
{
     if(doggo->getB() <= block->getY())
          return 1;
     else
          return 0;
}

void App::idle()
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
		block->updateCoords(block->getX() + 0.01);
          // printf("not colliding\n");
		if (xCollision() && yCollision())
		{
               // printf("colliding L\n");
			hills->updateTexCoords(hills->getTL() + 0.005, hills->getTR() + 0.005);
               block->updateCoords(block->getX() - 0.01);
		}
          else if(block->getY() <= doggo->getB() && xCollision())
          {
               doggo->updateGroundLevel(block->getY() + doggo->getH());
               doggo->isJumping = 1;
          }
          else
               doggo->updateGroundLevel(-0.5);
	}

	if (right)
	{
		hills->move(Movement);
		block->updateCoords(block->getX() - 0.01);
          // printf("not colliding\n");
		if (xCollision() && yCollision())
		{
               // printf("colliding R\n");
               hills->updateTexCoords(hills->getTL() - 0.005, hills->getTR() - 0.005);
			block->updateCoords(block->getX() + 0.01);

			// if (doggo->isJumping){
			// 	doggo->setY(block->getY() + doggo->getH());
			// }
			// else {
			// 	hills->updateTexCoords(hills->getTL() - 0.005, hills->getTR() - 0.005);
			// 	block->updateCoords(block->getX());
			// }
		}
          else if(block->getY() <= doggo->getB() && xCollision())
          {
               doggo->updateGroundLevel(block->getY() + doggo->getH());
               doggo->isJumping = 1;
          }
          else
               doggo->updateGroundLevel(-0.5);

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
