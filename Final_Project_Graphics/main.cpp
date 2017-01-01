//
//  main.cpp
//  Final_Project_Graphics
//
//  Created by Sujal Dhungana on 3/23/16.
//  Copyright © 2016 example. All rights reserved.
//

#include <iostream>
#include "GLUT/glut.h"

#include "Angel.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "ReadModel.h"
#include "mycamera.hpp"
#include  "vec3f.hpp"


#define SCREEN_WIDTH 725
#define SCREEN_HEIGHT 725

GLuint loadBMP_custom(unsigned char** data, int* w, int* h, const char * imagepath);

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

void UploadModel(Model&, int);
void UploadModel2(Model&, const char *);

const int NUM_MODELS = 10;
Model model[NUM_MODELS];

//---- GLuints for passing to vshader and fshader----
GLuint program;         //  Program*
GLuint Ka,Kd,Ks;        //  Materials amb, dif, spec
GLuint AmbientLight, DiffuseLight, SpecularLight;
GLuint LightPosition;              //  Light Position*
GLuint Model_I;         //  Model Matrix* (currently never changing, ID Matrix)
GLuint View;            //  View Matrix*
GLuint Projection;      //  Projection Matrix*
GLuint vNormal;         //  Normals*
GLuint vPosition;       //  Vertices*
GLuint vao[NUM_MODELS]; //  VertexArrayObject*
//GLuint USS_VAO;
//GLuint T_VAO;

GLuint vTexCoord;
GLuint textures;

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
enum { SUN = 0, MER = 1, VEN = 2, EAR = 3, MAR = 4, JUP = 5, SAT = 6, URA = 7, NEP = 8, STARS = 9, UE = 10, SI = 11};

bool stars_on = true;

float dist_from_sun[NUM_MODELS] = {
    0.00,
    3.68,
    6.72,
    9.30,
    14.1,
    48.36,
    88.865,
    178.37,
    279.52,
    0.00
};

float orbit_time[NUM_MODELS] = {
    0.0000,
    1.0000,
    0.4285,
    0.2500,
    0.1300,
    0.0211,
    0.0084,
    0.0029,
    0.0015,
    0.00
};

float size_rel[NUM_MODELS] = {
    30.00,
    0.38,
    0.95,
    1.0,
    0.53,
    11.19,
    9.40,
    4.04,
    3.88,
    2000000
};

int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };
GLfloat theta_total = 0.0;
int dirn = 1;
bool do_rotation = false;
bool start_orbit = false;
bool start_spin = false;

//---------------------------------------------------------------------------
//-----  Viewing transformation parameters

GLfloat Cx = 0;
GLfloat Cy = 0;
GLfloat Cz = 250;


point4  eye( Cx, Cy, Cz, 1.0 );
point4  at( 0.0, 0.0, 0.0, 1.0 );
vec4    up( 0.0, 1.0, 0.0, 0.0 );

//---------------------------------------------------------------------------
//-----  Projection transformation parameters

GLfloat  left = -1.0, right = 1.0;
GLfloat  bottom = -1.0, top = 1.0;
GLfloat  zNear = 1.0, zFar = 2000000.0;
//----------------------------------------------------------------------------

const int lights = 8;
point4 light_posXZ[lights] = {
    point4( 0.0, 0.0,  6.0, 0.0 ),
    point4( 3.0, 0.0,  3.0, 0.0 ),
    point4( 6.0, 0.0,  0.0, 0.0 ),
    point4( 3.0, 0.0,  -3.0, 0.0 ),
    point4( 0.0, 0.0,  -6.0, 0.0 ),
    point4( -3.0, 0.0,  -3.0, 0.0 ),
    point4( -6.0, 0.0,  0.0, 0.0 ),
    point4( -3.0, 0.0,  3.0, 0.0 ),
    
};

point4 light_posYZ[lights] = {
    point4( 0.0, 0.0,  6.0, 0.0 ),
    point4( 0.0, -3.0,  3.0, 0.0 ),
    point4( 0.0, -6.0,  0.0, 0.0 ),
    point4( 0.0, -3.0,  -3.0, 0.0 ),
    point4( 0.0, 0.0,  -6.0, 0.0 ),
    point4( 0.0, 3.0,  -3.0, 0.0 ),
    point4( 0.0, 6.0,  0.0, 0.0 ),
    point4( 0.0, 3.0,  3.0, 0.0 ),
    
};

color4 red = color4( 1.0, 0.2, 0.2, 0.0 );
color4 yellow = color4( 1.0, 1.0, 0.2, 1.0 );
color4 white = color4( 1.0, 1.0, 1.0, 1.0 );
color4 green = color4( 0.2, 1.0, 0.2, 1.0 );
color4 blue = color4( 0.2, 0.2, 1.0, 1.0 );
color4 orange = color4( 0.996, 0.3984, 0.0, 1.0 );
color4 black = color4( 0.0, 0.0, 0.0, 1.0 );
color4 pink = color4( 0.996, 0.4101, 0.7031, 1.0 );
color4 w_clear = color4( 1.0, 1.0, 1.0, 0.0 );
color4 b_clear = color4( 0.0, 0.0, 0.0, 0.0 );
color4 colors[9] = {
    yellow,
    green,
    yellow*pink,
    blue,
    red,
    orange,
    pink,
    white,
    pink*white
};

//File Locations for model obj's
const char *planet_texture[NUM_MODELS];
char planet[] = "objects/planet_obj.txt";
char planet_t[] = "objects/planet_textured_obj.txt";

//Various Flags for effects
int color_picker = 0;
bool color_strobe;
int light_picker = 0;
int star_picker = 0;
bool wire = false;
bool start_USS = false;


//Lighting Characteristics
float  material_shininess = 0.0;
point4 light_position = point4 ( 0.0, 0.0, 0.0, 1.0 );
color4 light_ambient = color4( 0.0, 0.0, 0.0, 1.0 );
color4 light_diffuse = color4( 0.95, 0.95, 0.95, 1.0 );
color4 light_specular = color4( 1.0, 1.0, 1.0, 1.0 );


//----------------------------------------------------------------------------
void UploadModel(Model& mod, int planet_index)
{
    int array_buffer_size = 0;
    mod.ogl_v_offset = array_buffer_size;
    mod.ogl_n_offset = array_buffer_size + mod.ogl_v_size;
    
    mod.ogl_uv_offset = array_buffer_size + mod.ogl_n_size + mod.ogl_n_offset;
    
    array_buffer_size = array_buffer_size + mod.ogl_v_size + mod.ogl_n_size + mod.ogl_uv_size;
    
    GLuint textures;
    glGenTextures( 1, &textures );
    glBindTexture( GL_TEXTURE_2D, textures );
    
    mod.uvs_buffer = textures;
    
    unsigned char* pic1 = NULL;
    int w,h;
    
    loadBMP_custom(&pic1, &w, &h, planet_texture[planet_index]);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, pic1);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glActiveTexture( GL_TEXTURE0 );
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
    mod.buffer = buffer;
    
    glBufferData( GL_ARRAY_BUFFER, array_buffer_size, NULL, GL_DYNAMIC_DRAW );
    
    glBufferSubData( GL_ARRAY_BUFFER, mod.ogl_v_offset, mod.ogl_v_size, mod.vertices );
    glBufferSubData( GL_ARRAY_BUFFER, mod.ogl_n_offset, mod.ogl_n_size, mod.normals );
    glBufferSubData( GL_ARRAY_BUFFER, mod.ogl_uv_offset, mod.ogl_uv_size, mod.uvs );
}

//----------------------------------------------------------------------------
void
init()
{
    
    glGenVertexArraysAPPLE( 1, &vao[0] );
    glBindVertexArrayAPPLE( vao[0] );
    ReadModel2(&model[0],planet_t);
    UploadModel(model[0],SUN);
    
    model[SUN].crm *= Scale(size_rel[SUN], size_rel[SUN], size_rel[SUN]);
    
    program = InitShader( "vshader53.glsl", "fshader53.glsl" );
    
    vPosition = glGetAttribLocation( program, "vPosition" );
    vNormal = glGetAttribLocation( program, "vNormal" );
    Model_I = glGetUniformLocation( program, "Model" );
    View = glGetUniformLocation( program, "View" );
    Projection = glGetUniformLocation( program, "Projection" );
    AmbientLight = glGetUniformLocation( program, "AmbientLight" );
    DiffuseLight = glGetUniformLocation( program, "DiffuseLight" );
    SpecularLight = glGetUniformLocation( program, "SpecularLight" );
    Ka = glGetUniformLocation( program, "ka" );
    Kd = glGetUniformLocation( program, "kd" );
    Ks = glGetUniformLocation( program, "ks" );
    LightPosition = glGetUniformLocation( program, "LightPosition" );
    
    
    //TEXTURE//
    vTexCoord = glGetAttribLocation( program, "vTexCoord" );
    glEnableVertexAttribArray( vTexCoord );
    
    // Set the value of the fragment shader texture sampler variable (texture) to GL_TEXTURE0
    glUniform1i( glGetUniformLocation(program, "texture"), 0);
    
    
    //TEXTURE////
    
    glUseProgram( program );
    
    glEnableVertexAttribArray( vTexCoord );
    glEnableVertexAttribArray( vPosition );
    glEnableVertexAttribArray( vNormal );
    
    
    /*might need to move up*/
    glUniform1f( glGetUniformLocation(program, "Shininess"),material_shininess );
    
    glEnable( GL_DEPTH_TEST );
    
    
    for(int i = 1; i < 10; i++)
    {
        glGenVertexArraysAPPLE( 1, &vao[i] );
        glBindVertexArrayAPPLE( vao[i] );
        
        ReadModel2(&model[i],planet_t);
        UploadModel(model[i],i);
        
        if(i != 9)
            model[i].crm = model[i].crm * Translate(dist_from_sun[i]+30.0,0.0,0.0) * Scale(size_rel[i], size_rel[i], size_rel[i]);
        else
        {
            model[i].crm = model[i].crm * Scale(size_rel[i], size_rel[i], size_rel[i]);
        }
    }
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(wire)
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
    glUseProgram(program);
    
    glBindVertexArrayAPPLE(vao[0]);
    
    mat4 I;
    
    //  Generate tha model-view matrix
    //----- view
    
    
    mat4  v = LookAt( eye, at, up );
    //v = model[0].crm * v;
   
    glUniformMatrix4fv( View, 1, GL_TRUE, v );
    
    glUniform1f( glGetUniformLocation(program, "Shininess"),material_shininess );
    
    glUniform4fv( LightPosition, 1, light_position );
    glUniform4fv( DiffuseLight, 1, light_diffuse );
    glUniform4fv( SpecularLight, 1, light_specular );
    
    //----- projection
    mat4  p = Frustum( left, right, bottom, top, zNear, zFar );
    
    glUniformMatrix4fv( Projection, 1, GL_TRUE, p );
    
    
    glUniform4fv( Ka, 1, white );
    glUniform4fv( Kd, 1, color4{0.80,0.80,0.80,1.0});
    glUniform4fv( Ks, 1, color4{0.5,0.5,0.5,1.0});
    for(int i = 0; i < 10; i++)
    {
        if(i == SUN || i == 9)
        {
            light_ambient = white;
        }
        else
        {
            light_ambient = color4( 0.375, 0.375, 0.375, 1.0 );
            
        }
        glUniform4fv( AmbientLight, 1, light_ambient );
        
        // Inform shaders/Bind the Vertex Array Object(vao).
        glBindVertexArrayAPPLE(vao[i]);
        
        // Inform shaders/Bind the buffer that was used with the Vertex Array Object(vao) above.
        glBindBuffer( GL_ARRAY_BUFFER, model[i].buffer );
        
        // // Inform shaders/Bind the texture buffer that was used with the Vertex Array Object(vao) above.
        glBindTexture( GL_TEXTURE_2D, model[i].uvs_buffer );
        
        glEnableVertexAttribArray(vPosition);
        glEnableVertexAttribArray(vNormal);
        glEnableVertexAttribArray(vTexCoord );
        
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model[i].ogl_v_offset));
        glVertexAttribPointer( vNormal  , 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model[i].ogl_n_offset));
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model[i].ogl_uv_offset));
        
        glUniformMatrix4fv( Model_I, 1, GL_TRUE, model[i].crm);
        
        if(STARS == i)
        {
            if(stars_on)
                glDrawArrays( GL_TRIANGLES, 0, model[i].num_vertices);
        }
        else
            glDrawArrays( GL_TRIANGLES, 0, model[i].num_vertices );
    }
    
    //Enable all three arrays
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vNormal);
    glEnableVertexAttribArray(vTexCoord );

    
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void speed_orbit()
{
    float inc = 0.10;
    for(int i = 0; i < 8; i++)
    {
        orbit_time[i] += inc;
    }
}

void slow_orbit()
{
    float dec = 0.10;
    for(int i = 0; i < 8; i++)
    {
        orbit_time[i] -= dec;
    }
}

void idle( void )
{
    
    if (start_orbit)
    {
        for(int i = 1; i < 9; i++)
        {
            model[i].crm =  RotateY(orbit_time[i]) * model[i].crm;
        }
        
    }
    else
    {
        start_orbit = false;
    }
    
    if (start_spin)
    {
        for(int i = 1; i < 9; i++)
        {
            model[i].crm = model[i].crm * RotateY(0.5);
        }
        
    }
    else
    {
        start_spin = false;
    }
    
    
    glutPostRedisplay();
    
    
    
}

//----------------------------------------------------------------------------
GLfloat in = 1.0;
void keyboard( unsigned char key, int x, int y )
{
    unsigned int i = (unsigned int)key - '0';
    mat4 I;
    
    if(do_rotation == false){
        switch( key )
        {
            case 033: // Escape Key
            case 'Q':
                exit( EXIT_SUCCESS );
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                
                if(i == SUN)
                {
                    Cx = dist_from_sun[i];
                    Cy = 0.0;
                    Cz = 2*size_rel[i];
                    eye = point4( Cx, Cy, Cz, 1.0 );
                    
                    at = point4(dist_from_sun[i],0.0,0.0,1.0);
                }
                else{
                    Cx = dist_from_sun[i]+(size_rel[SUN]);
                    Cy = 0.0;
                    Cz = (1.75*size_rel[i])+1;
                    eye = point4( Cx, Cy, Cz, 1.0 );
                    
                    at = point4(dist_from_sun[i]+(size_rel[SUN]),0.0,0.0,1.0);
                }
                
                break;
            case '9':
                Cx = dist_from_sun[EAR]+(size_rel[SUN])+3;
                Cy = 5.1;
                Cz = (1.75*size_rel[EAR])+2;
                eye = point4( Cx, Cy, Cz, 1.0 );
                
                at = point4(dist_from_sun[EAR]+(size_rel[SUN]),2.0,0.0,1.0);
                break;
            case 'w':
                eye = RotateX(.5) * eye;
                break;
            case 's':
                eye = I * RotateX(-.5) * eye;
                break;
            case 'a':
                eye = I * RotateY(-.5) * eye;
                break;
            case 'd':
                eye = I * RotateY(.5) * eye;
                break;
            case 'f':
                eye = I * RotateY(3) * eye;
                break;
            case ' ':  // defaults
                Cx = 0.0;
                Cy = 0.0;
                Cz = 250.0;
                eye = { Cx, Cy, Cz, 1.0 };
                at = { 0.0, 0.0, 0.0, 1.0 };
                up = { 0.0, 1.0, 0.0, 0.0 };
                break;
            case '+':
                if(light_picker >= lights)
                    light_picker = 0;
                light_position = light_posYZ[light_picker];
                light_picker++;
                break;
            case 'r':
                if(start_orbit)
                    start_orbit = false;
                else
                    start_orbit = true;
                break;
            case 'o':
                slow_orbit();
                break;
            case 'O':
                speed_orbit();
                break;
            case '=':
                Cx = eye.x * 1.025; Cy = eye.y * 1.025; Cz = eye.z * 1.025;
                eye = {Cx,Cy,Cz,1.0};
                break;
            case '-':
                Cx = eye.x * 0.975; Cy = eye.y * 0.975; Cz =  eye.z * 0.975;
                eye = {Cx,Cy,Cz,1.0};
                break;
            case 't':
                start_spin = !start_spin;
                break;
            case 'S':
                stars_on = !stars_on;
                break;
            case 'W':
                wire = !wire;
                break;
                
        }
        glutPostRedisplay();
    }
    
}

//----------------------------------------------------------------------------

void reshape( int width, int height )
{
    
    glViewport( 0, 0, width, height );
    
    GLfloat aspect = GLfloat(width)/height;
    mat4  projection = Perspective( 45.0, aspect, 0.5, 3.0 );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
}

void UploadModel2(Model& mod, const char * file)
{
    int array_buffer_size = 0;
    mod.ogl_v_offset = array_buffer_size;
    mod.ogl_n_offset = array_buffer_size + mod.ogl_v_size;
    
    mod.ogl_uv_offset = array_buffer_size + mod.ogl_n_size + mod.ogl_n_offset;
    
    array_buffer_size = array_buffer_size + mod.ogl_v_size + mod.ogl_n_size + mod.ogl_uv_size;
    
    GLuint textures;
    glGenTextures( 1, &textures );
    glBindTexture( GL_TEXTURE_2D, textures );
    
    mod.uvs_buffer = textures;
    
    unsigned char* pic1 = NULL;
    int w,h;
    loadBMP_custom(&pic1, &w, &h, file);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, pic1);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glActiveTexture( GL_TEXTURE0 );
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
    mod.buffer = buffer;
    
    glBufferData( GL_ARRAY_BUFFER, array_buffer_size, NULL, GL_DYNAMIC_DRAW );
    
    glBufferSubData( GL_ARRAY_BUFFER, mod.ogl_v_offset, mod.ogl_v_size, mod.vertices );
    glBufferSubData( GL_ARRAY_BUFFER, mod.ogl_n_offset, mod.ogl_n_size, mod.normals );
    glBufferSubData( GL_ARRAY_BUFFER, mod.ogl_uv_offset, mod.ogl_uv_size, mod.uvs );
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
    planet_texture[0] = "Textures/sun1.bmp";
    planet_texture[1] = "Textures/mer.bmp";
    planet_texture[2] = "Textures/ven.bmp";
    planet_texture[3] = "Textures/earth1.bmp";
    planet_texture[4] = "Textures/mar.bmp";
    planet_texture[5] = "Textures/jup.bmp";
    planet_texture[6] = "Textures/sat.bmp";
    planet_texture[7] = "Textures/ura.bmp";
    planet_texture[8] = "Textures/nep.bmp";
    planet_texture[9] = "Textures/universe.bmp";
    
    
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow( "Solar System" );
    init();
    
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );
    
    glutMainLoop();
    return 0;
}
