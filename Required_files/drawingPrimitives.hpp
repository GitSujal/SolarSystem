//
//  drawingPrimitives.hpp
//  Project
//
//  Created by Sujal Dhungana on 3/6/16.
//  Copyright © 2016 example. All rights reserved.
//

#ifndef drawingPrimitives_hpp
#define drawingPrimitives_hpp

#include <stdio.h>
#include "GLUT/glut.h"
#include "vec3f.hpp"

class primitives {
private:
public:
    void plot(GLfloat x, GLfloat y,GLfloat z);

};

class line: primitives
{
private:
    Vec3f Startpoints;
    Vec3f Endpoints;
public:
    line();
    line(Vec3f start, Vec3f end);
    void drawline();
    Vec3f vectorized();
};

class ellipse: primitives
{
private:
    Vec3f Center;
    GLfloat Radius_x;
    GLfloat Radius_y;

public:
    ellipse();
    ellipse(Vec3f center, GLfloat radius_x, GLfloat radius_y);
    ellipse(GLfloat radius_x, GLfloat radius_y);
    ellipse(Vec3f center, GLfloat radius);
    ellipse(GLfloat radius);
   void drawellipse();
    void drawcircle();
    
    };




#endif /* drawingPrimitives_hpp */
