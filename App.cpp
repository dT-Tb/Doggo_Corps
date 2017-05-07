#include "App.h"

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
	dog = loadTexture("..\\resources\\monalisa.bmp");
	#else
	floor = loadTexture("resources/ground2.bmp");
	cld = loadTexture("resources/cloud.bmp");
	bkgd = loadTexture("resources/bkgd.bmp");
	bkgdHills = loadTexture("resources/bkgdHills.bmp");
	blk = loadTexture("resources/wall.bmp");
	dog = loadTexture("resources/monalisa.bmp");
	#endif
    
    background = new TexRect(-1, 1, 2, 2);
    ground = new TexRect(-1.0, -0.9, 2.0, 0.1);
	cloud = new TexRect(-0.7, 0.7, 0.35, 0.70);
	hills = new Background(-1.0, -0.6, 2.0, 0.3);
	block = new Block(-0.25, -0.6, 0.15, 0.3);
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

/*void App::glutSpecialFunc(void(*func)(int key, int x, int y))
{
	if (GLUT_KEY_UP)
		doggo->isJumping = 1;

}*/

void App::idle()
{
	doggo->gravity();

	if(doggo->isJumping)
	{
		if(doggo->getY() <= 0.11 && !doggo->jumpReset)
		{
			doggo->jump();
		}
		else
		{
			doggo->isJumping = 0;
			doggo->jumpReset = 1;
		}
	}


	if (Movement == 1)
	{
		hills->updateTexCoords(hills->getTL() - 0.005, hills->getTR() - 0.005);
		block->updateCoords(block->getL() + 0.01, block->getR() + 0.01);
		//Movement = 0;
	}
	if (Movement == 2)
	{
		hills->updateTexCoords(hills->getTL() + 0.005, hills->getTR() + 0.005);
		block->updateCoords(block->getL() - 0.01, block->getR() - 0.01);
		//Movement = 0;
	}
	
	redraw();
}

void App::keyPress(unsigned char key) {
#define ESC 27
#define SPACEBAR 32

    if (key == ESC) {
        // Exit the app when Esc key is pressed
        exit(0);
    }
	if (key == SPACEBAR) {
		doggo->isJumping = 1;
		doggo->jumpReset = 1;
	}
	if (key == 'w') {
		doggo->isJumping = 1;
	}
	if (key == 'a') {
		Movement = doggo->move('a');
	}
	if (key == 'd') {
		Movement = doggo->move('d');
	}

	redraw();
}
