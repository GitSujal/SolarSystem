

#ifndef __ANGEL_H__
#define __ANGEL_H__
 
// --- Include system headers ---
//

#include <cmath>
#include <math.h>
#include <iostream>
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))


namespace Angel {

//  Helper function to load vertex and fragment shader files
GLuint InitShader( const char* vertexShaderFile,
		   const char* fragmentShaderFile );


const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant 
const GLfloat  DegreesToRadians = M_PI / 180.0;
    

}

#include "vec.h"
#include "mat.h"

//  Globally use namespace in our example programs.
using namespace Angel;

#endif
