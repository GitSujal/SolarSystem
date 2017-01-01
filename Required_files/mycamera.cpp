//
//  mycamera.cpp
//  Project
//
//  Created by Sujal Dhungana on 3/6/16.
//  Copyright © 2016 example. All rights reserved.
//

#include "mycamera.hpp"
#include "vec3f.hpp"
#include <GLUT/GLUT.h>
#include <cmath>
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

//const static float STEP_SCALE = 0.1f;
//const static int MARGIN = 10;
//
//Camera::Camera(int WindowWidth, int WindowHeight)
//{
//    Window_Width  = WindowWidth;
//    Window_Height = WindowHeight;
//    position          = vec4();
//    lookat       = vec4();
//   lookat = normalize(lookat);
//    updirection           = vec4(0.0,1.0,0.0,1.0);
//    init();
//}
//Camera::Camera(){
//    Window_Width  = 725;
//    Window_Height = 725;
//    position          = vec4();
//    lookat       = vec4();
//    lookat = normalize(lookat);
//    updirection           = vec4(0.0,1.0,0.0,1.0);
//    init();
//}
//
//Camera::Camera(GLint WindowWidth, GLint WindowHeight, const vec4 Pos, const vec4 Target,const vec4 angle, const vec4 Up)
//{
//    Window_Width  = WindowWidth;
//    Window_Height = WindowHeight;
//    position = Pos;
//    lookat = Target;
//  lookat =  normalize(lookat);
////    angle = normalize(angle);
//    updirection = Up;
//  updirection =  normalize(updirection);
//    init();
//}
//
//void Camera::init()
//{
//    m_OnUpperEdge = false;
//    m_OnLowerEdge = false;
//    m_OnLeftEdge  = false;
//    m_OnRightEdge = false;
//}
//
//bool Camera::OnKeyboard(int Key)
//{
//    bool Ret = false;
//    
//    switch (Key) {
//            
//        case 'w':
//        {
//            Position += (lookat * STEP_SCALE);
//            Ret = true;
//        }
//            break;
//            
//        case 's':
//        {
//            Position -= (lookat * STEP_SCALE);
//            Ret = true;
//        }
//            break;
//            
//        case 'a':
//        {
//            vec4 Left = lookat.cross(updirection);
//            Left = normalize(Left);
//            Left *= STEP_SCALE;
//            position += Left;
//            Ret = true;
//        }
//            break;
//            
//        case 'd':
//        {
//            Vec3f Right = UpDirection.cross(Lookat);
//            Right.normalize();
//            Right *= STEP_SCALE;
//            Position += Right;
//            Ret = true;
//        }
//            break;
//    }
//    update();
//    return Ret;
//}
//
//void Camera::OnMouse(int x, int y)
//{
//    const int DeltaX = x - MousePosition.v[0];
//    const int DeltaY = y - MousePosition.v[1];
//    
//    MousePosition.v[0] = x;
//    MousePosition.v[1] = y;
//    
//    Angle.v[0] += (float)DeltaX / 20.0f;
//    Angle.v[1] += (float)DeltaY / 20.0f;
//    
//    if (DeltaX == 0) {
//        if (x <= MARGIN) {
//            //    m_AngleH -= 1.0f;
//            m_OnLeftEdge = true;
//        }
//        
//        else if (x >= (Window_Width - MARGIN)) {
//            //    m_AngleH += 1.0f;
//            m_OnRightEdge = true;
//        }
//    }
//    else {
//        m_OnLeftEdge = false;
//        m_OnRightEdge = false;
//    }
//    
//    if (DeltaY == 0) {
//        if (y <= MARGIN) {
//            m_OnUpperEdge = true;
//        }
//        else if (y >= (Window_Height - MARGIN)) {
//            m_OnLowerEdge = true;
//        }
//    }
//    else {
//        m_OnUpperEdge = false;
//        m_OnLowerEdge = false;
//    }
//    
//    update();
//}
//
//
//void Camera::OnRender()
//{
//    bool ShouldUpdate = false;
//    
//    if (m_OnLeftEdge) {
//        Angle.v[0] -= 0.1f;
//        ShouldUpdate = true;
//    }
//    else if (m_OnRightEdge) {
//        Angle.v[0] += 0.1f;
//        ShouldUpdate = true;
//    }
//    
//    if (m_OnUpperEdge) {
//        if (Angle.v[1] > -90.0f) {
//            Angle.v[1] -= 0.1f;
//            ShouldUpdate = true;
//        }
//    }
//    else if (m_OnLowerEdge) {
//        if (Angle.v[1] < 90.0f) {
//            Angle.v[1] += 0.1f;
//            ShouldUpdate = true;
//        }
//    }
//    
//    if (ShouldUpdate) {
//        update();
//    }
//}
//
//void Camera::update()
//{
//    const Vec3f Vaxis(0.0f, 1.0f, 0.0f);
//    
//    // Rotate the view vector by the horizontal angle around the vertical axis
//    Vec3f View(1.0f, 0.0f, 0.0f);
//    if (Angle.v[0]!=0) {
//     //   View.rotate(Angle.v[0], Vaxis);
//        glRotatef(Angle.v[0], 0.0, 1.0, 0.0);
//        View.normalize();
//    }
//    // Rotate the view vector by the vertical angle around the horizontal axis
//    Vec3f Haxis = Vaxis.cross(View);
//    Haxis.normalize();
//    if (Angle.v[1]!=0) {
//    //    View.rotate(Angle.v[1], Haxis);
//        glRotatef(Angle.v[1], Haxis.v[0], Haxis.v[1], Haxis.v[2]);
//    }
//    Lookat = View;
//  Lookat =  Lookat.normalize();
//    
//    UpDirection = Lookat.cross(Haxis);
//    UpDirection.normalize();
//}
//
//



















