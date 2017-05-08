//
//  TexRect.hpp
//  glutapp
//
//  Created by Angelo Kyrilov on 4/11/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef TexRect_hpp
#define TexRect_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class TexRect{
private:
    float x;
    float y;
    float w;
    float h;

protected:
     void setX(float a) { this->x = a; }
     void setY(float b) { this->y = b; }
     void setW(float c) { this->w = c; }
     void setH(float d) { this->h = d; }

public:
    TexRect (float x=0, float y=0, float w=0.5, float h=0.5){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

   virtual void draw(){
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);
        glVertex2f(x, y - h);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(x, y);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(x+w, y);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(x+w, y - h);

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

	float getX() const { return x; }
	float getY() const { return y; }
	float getH() const { return h; }
     float getW() const { return w; }
	float getR() const { return x + w; }
	float getB() const { return y - h; }
};

#endif /* TexRect_hpp */
