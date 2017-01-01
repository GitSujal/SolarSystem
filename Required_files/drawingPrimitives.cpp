//
//  drawingPrimitives.cpp
//  Project
//
//  Created by Sujal Dhungana on 3/6/16.
//  Copyright © 2016 example. All rights reserved.
//

#include "drawingPrimitives.hpp"
#include "GLUT/glut.h"
#include "vec3f.hpp"

line::line(){
    Endpoints = Vec3f();
    Startpoints = Vec3f();
}

line::line(Vec3f start, Vec3f end){
    Endpoints = end;
    Startpoints = start;
    drawline();
}

void line::drawline() {
    glBegin(GL_LINES);
    glVertex3f(Startpoints.v[0],Startpoints.v[1], Startpoints.v[2]);
    glVertex3f(Endpoints.v[0],Endpoints.v[1],Endpoints.v[2]);
    glEnd();
}

Vec3f line::vectorized() {
    return (Endpoints-Startpoints);
}

ellipse::ellipse() {
    Center = Vec3f();
    Radius_x = 0.0;
    Radius_y = 0.0;
}

ellipse::ellipse(Vec3f center, GLfloat radius_x, GLfloat radius_y){
    Center = center;
    Radius_x = radius_x;
    Radius_y = radius_y;
    drawellipse();
}

ellipse::ellipse(GLfloat radius_x, GLfloat radius_y){
    Center = Vec3f();
    Radius_x = radius_x;
    Radius_y = radius_y;
    drawellipse();
}

ellipse::ellipse(Vec3f center, GLfloat radius){
    Center = center;
    Radius_x = radius;
    Radius_y = radius;
    drawcircle();
    
}

ellipse::ellipse(GLfloat radius){
     Center = Vec3f();
    Radius_x = radius;
    Radius_y = radius;
    drawcircle();
}
void ellipse::drawellipse(){
    int rxsq = Radius_x*Radius_x;
    int rysq = Radius_y*Radius_y;
    int  x =0;
    int y = Radius_y;
    int px = 0;
    int py = 2*rxsq*y;
    float  p = rysq - (rxsq*Radius_y)+(0.25*rxsq);
    do {
        x++;
        px += 2*rysq;
        if (p<0) {
            p += rysq +px;
        }
        else {
            y--;
            py -= 2*rxsq;
            p += rysq+px-py;
        }
        plot(x+Center.v[0],y+Center.v[1],Center.v[2]);
        plot(-x+Center.v[0],y+Center.v[1],Center.v[2]);
        plot(-x+Center.v[0],-y+Center.v[1],Center.v[2]);
        plot(x+Center.v[0],-y+Center.v[1],Center.v[2]);
    }
    while (px<py);
    
    p = rysq*float(x+0.5)*float(x+0.5)+rxsq*float(y-1)*float(y-1)-rxsq*rysq;
    
    do {
        y--;
        py -= 2*rxsq;
        if (p>0) {
            p += rxsq - py;
        }
        else {
            x++;
            px += 2*rysq;
            p += rxsq - py+px;
        }
        plot(x+Center.v[0],y+Center.v[1],Center.v[2]);
        plot(-x+Center.v[0],y+Center.v[1],Center.v[2]);
        plot(-x+Center.v[0],-y+Center.v[1],Center.v[2]);
        plot(x+Center.v[0],-y+Center.v[1],Center.v[2]);

    }
    while(y>0);
    
}

void ellipse::drawcircle() {
    int  x =0;
    int y=Radius_x;
    int p = 1-Radius_x;
    while (x<y) {
        x++;
        if (p<0) {
            p = p+2*x+1;
        }
        else{
            y--;
            p = p+2*(x-y)+1;
        }
        plot(x+Center.v[0],y+Center.v[1],Center.v[2]);
        plot(-x+Center.v[0],y+Center.v[1],Center.v[2]);
        plot(-x+Center.v[0],-y+Center.v[1],Center.v[2]);
        plot(x+Center.v[0],-y+Center.v[1],Center.v[2]);
        plot(y+Center[1], x+Center.v[0], Center.v[2]);
        plot(-y+Center[1], x+Center.v[0], Center.v[2]);
        plot(-y+Center[1], -x+Center.v[0], Center.v[2]);
        plot(y+Center[1], -x+Center.v[0], Center.v[2]);
    }
}

void primitives::plot(GLfloat x, GLfloat y,GLfloat z)
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex3f(float((250+x)/500),float((250+y)/500),z);
    glEnd();
}


