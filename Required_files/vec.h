

#ifndef __ANGEL_VEC_H__
#define __ANGEL_VEC_H__

#include "Angel.h"
#include "math.h"

namespace Angel {
    
    //  vec2.h - 2D vector
    
    struct vec2 {
        
        GLfloat  x;
        GLfloat  y;
        
        vec2( GLfloat s = GLfloat(0.0) ) :
        x(s), y(s) {}
        
        vec2( GLfloat x, GLfloat y ) :
        x(x), y(y) {}
        
        vec2( const vec2& v )
        { x = v.x;  y = v.y;  }
        
        //  --- Indexing Operator ---
        
        GLfloat& operator [] ( int i ) { return *(&x + i); }
        const GLfloat operator [] ( int i ) const { return *(&x + i); }

        
        vec2 operator - () const // unary minus operator
        { return vec2( -x, -y ); }
        
        vec2 operator + ( const vec2& v ) const
        { return vec2( x + v.x, y + v.y ); }
        
        vec2 operator - ( const vec2& v ) const
        { return vec2( x - v.x, y - v.y ); }
        
        vec2 operator * ( const GLfloat s ) const
        { return vec2( s*x, s*y ); }
        
        vec2 operator * ( const vec2& v ) const
        { return vec2( x*v.x, y*v.y ); }
        
        friend vec2 operator * ( const GLfloat s, const vec2& v )
        { return v * s; }
        
        vec2 operator / ( const GLfloat s ) const {

            
            GLfloat r = GLfloat(1.0) / s;
            return *this * r;
        }
        
        vec2& operator += ( const vec2& v )
        { x += v.x;  y += v.y;   return *this; }
        
        vec2& operator -= ( const vec2& v )
        { x -= v.x;  y -= v.y;  return *this; }
        
        vec2& operator *= ( const GLfloat s )
        { x *= s;  y *= s;   return *this; }
        
        vec2& operator *= ( const vec2& v )
        { x *= v.x;  y *= v.y; return *this; }
        
        vec2& operator /= ( const GLfloat s ) {
                        
            GLfloat r = GLfloat(1.0) / s;
            *this *= r;
            
            return *this;
        }
        
        //  --- Insertion and Extraction Operators ---
        
        
        friend std::ostream& operator << ( std::ostream& os, const vec2& v ) {
            return os << "( " << v.x << ", " << v.y <<  " )";
        }
        
        friend std::istream& operator >> ( std::istream& is, vec2& v )
        { return is >> v.x >> v.y ; }
        

        operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &x ); }
        
        operator GLfloat* ()
        { return static_cast<GLfloat*>( &x ); }
    };


    
    inline
    GLfloat dot( const vec2& u, const vec2& v ) {
        return u.x * v.x + u.y * v.y;
    }
    
    inline
    GLfloat length( const vec2& v ) {
        return std::sqrt( dot(v,v) );
    }
    
    inline
    vec2 normalize( const vec2& v ) {
        return v / length(v);
    }
    

    //  vec3.h - 3D vector

    
    struct vec3 {
        
        GLfloat  x;
        GLfloat  y;
        GLfloat  z;
        
        
        vec3( GLfloat s = GLfloat(0.0) ) :
        x(s), y(s), z(s) {}
        
        vec3( GLfloat x, GLfloat y, GLfloat z ) :
        x(x), y(y), z(z) {}
        
        vec3( const vec3& v ) { x = v.x;  y = v.y;  z = v.z; }
        
        vec3( const vec2& v, const float f ) { x = v.x;  y = v.y;  z = f; }
        

        
        GLfloat& operator [] ( int i ) { return *(&x + i); }
        const GLfloat operator [] ( int i ) const { return *(&x + i); }
 
        
        vec3 operator - () const  // unary minus operator
        { return vec3( -x, -y, -z ); }
        
        vec3 operator + ( const vec3& v ) const
        { return vec3( x + v.x, y + v.y, z + v.z ); }
        
        vec3 operator - ( const vec3& v ) const
        { return vec3( x - v.x, y - v.y, z - v.z ); }
        
        vec3 operator * ( const GLfloat s ) const
        { return vec3( s*x, s*y, s*z ); }
        
        vec3 operator * ( const vec3& v ) const
        { return vec3( x*v.x, y*v.y, z*v.z ); }
        
        friend vec3 operator * ( const GLfloat s, const vec3& v )
        { return v * s; }
        
        vec3 operator / ( const GLfloat s ) const {

            
            GLfloat r = GLfloat(1.0) / s;
            return *this * r;
        }
        
   
        
        vec3& operator += ( const vec3& v )
        { x += v.x;  y += v.y;  z += v.z;  return *this; }
        
        vec3& operator -= ( const vec3& v )
        { x -= v.x;  y -= v.y;  z -= v.z;  return *this; }
        
        vec3& operator *= ( const GLfloat s )
        { x *= s;  y *= s;  z *= s;  return *this; }
        
        vec3& operator *= ( const vec3& v )
        { x *= v.x;  y *= v.y;  z *= v.z;  return *this; }
        
        vec3& operator /= ( const GLfloat s ) {

            
            GLfloat r = GLfloat(1.0) / s;
            *this *= r;
            
            return *this;
        }
        
 
        
        friend std::ostream& operator << ( std::ostream& os, const vec3& v ) {
            return os << "( " << v.x << ", " << v.y << ", " << v.z <<  " )";
        }
        
        friend std::istream& operator >> ( std::istream& is, vec3& v )
        { return is >> v.x >> v.y >> v.z ; }
  
        operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &x ); }
        
        operator GLfloat* ()
        { return static_cast<GLfloat*>( &x ); }
    };
    

    
    inline
    GLfloat dot( const vec3& u, const vec3& v ) {
        return u.x*v.x + u.y*v.y + u.z*v.z ;
    }
    
    inline
    GLfloat length( const vec3& v ) {
        return std::sqrt( dot(v,v) );
    }
    
    inline
    vec3 normalize( const vec3& v ) {
        return v / length(v);
    }
    
    inline
    vec3 cross(const vec3& a, const vec3& b )
    {
        return vec3( a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x );
    }
    
    

    //  vec4 - 4D vector

    
    struct vec4 {
        
        GLfloat  x;
        GLfloat  y;
        GLfloat  z;
        GLfloat  w;
        

        
        vec4( GLfloat s = GLfloat(0.0) ) :
        x(s), y(s), z(s), w(s) {}
        
        vec4( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) :
        x(x), y(y), z(z), w(w) {}
        
        vec4( const vec4& v ) { x = v.x;  y = v.y;  z = v.z;  w = v.w; }
        
        vec4( const vec3& v, const float s = 1.0 ) : w(w)
        { x = v.x;  y = v.y;  z = v.z; }
        
        vec4( const vec2& v, const float z, const float w ) : z(z), w(w)
        { x = v.x;  y = v.y; }
        

        
        GLfloat& operator [] ( int i ) { return *(&x + i); }
        const GLfloat operator [] ( int i ) const { return *(&x + i); }

        
        vec4 operator - () const
        { return vec4( -x, -y, -z, -w ); }
        
        vec4 operator + ( const vec4& v ) const
        { return vec4( x + v.x, y + v.y, z + v.z, w + v.w ); }
        
        vec4 operator - ( const vec4& v ) const
        { return vec4( x - v.x, y - v.y, z - v.z, w - v.w ); }
        
        vec4 operator * ( const GLfloat s ) const
        { return vec4( s*x, s*y, s*z, s*w ); }
        
        vec4 operator * ( const vec4& v ) const
        { return vec4( x*v.x, y*v.y, z*v.z, w*v.z ); }
        
        friend vec4 operator * ( const GLfloat s, const vec4& v )
        { return v * s; }
        
        vec4 operator / ( const GLfloat s ) const {

            
            GLfloat r = GLfloat(1.0) / s;
            return *this * r;
        }
        

        vec4& operator += ( const vec4& v )
        { x += v.x;  y += v.y;  z += v.z;  w += v.w;  return *this; }
        
        vec4& operator -= ( const vec4& v )
        { x -= v.x;  y -= v.y;  z -= v.z;  w -= v.w;  return *this; }
        
        vec4& operator *= ( const GLfloat s )
        { x *= s;  y *= s;  z *= s;  w *= s;  return *this; }
        
        vec4& operator *= ( const vec4& v )
        { x *= v.x, y *= v.y, z *= v.z, w *= v.w;  return *this; }
        
        vec4& operator /= ( const GLfloat s ) {

            
            GLfloat r = GLfloat(1.0) / s;
            *this *= r;
            
            return *this;
        }
        

        
        friend std::ostream& operator << ( std::ostream& os, const vec4& v ) {
            return os << "( " << v.x << ", " << v.y
            << ", " << v.z << ", " << v.w << " )";
        }
        
        friend std::istream& operator >> ( std::istream& is, vec4& v )
        { return is >> v.x >> v.y >> v.z >> v.w; }
        

        operator const GLfloat* () const
        { return static_cast<const GLfloat*>( &x ); }
        
        operator GLfloat* ()
        { return static_cast<GLfloat*>( &x ); }
    };
    


    inline
    GLfloat dot( const vec4& u, const vec4& v ) {
        return u.x*v.x + u.y*v.y + u.z*v.z + u.w+v.w;
    }
    
    inline
    GLfloat length( const vec4& v ) {
        return std::sqrt( dot(v,v) );
    }
    
    inline
    vec4 normalize( const vec4& v ) {
        return v / length(v);
    }
    
    inline
    vec3 cross(const vec4& a, const vec4& b )
    {
        return vec3( a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x );
    }
    
    inline
    vec2 uv(const vec4& a)
    {
        GLfloat u = 0.5 + (atan2f(-a.z, a.x)/(2*M_PI));
        GLfloat v = 0.5 - (asinf(a.y)/M_PI);
        return vec2(u,1-v);
    }
    
    inline
    vec2 uv(const vec3& a)
    {
        GLfloat u = 0.5 + (atan2f(-a.z, a.x)/(2*M_PI));
        GLfloat v = 0.5 - (asinf(a.y)/M_PI);
        return vec2(u,1-v);
    }

    inline
    vec2 uv5(const vec4& a)
    {
        GLfloat u = 0.5 + (atan2f(-a.z, a.x)/(2*M_PI));
        GLfloat v = 0.5 - (asinf(a.y)/M_PI);
        if(fabs(1.0 - u) < .007)
        {
            u = .99;
        }
        else if(u < .0350)
        {
            u = 0.01;
        }
        if(fabs(1.0 - v) < .007)
        {
            v = .99;
        }
        else if(v < .0350)
        {
            v = 0.01;
        }
        return vec2(u,1-v);
    }
    
    inline
    vec2 uv2(const vec4& a)
    {
        GLfloat theta = atanf(-a.z/a.x);
        GLfloat phi = acosf(-a.y/1);
        GLfloat s = (theta + M_PI)/M_PI;
        GLfloat t = phi/M_PI;
        return vec2(s,t);
    }
    
    inline
    vec2 uv3(const vec4& a)
    {
        GLfloat len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        GLfloat u = acos(a.y / len) / M_PI;
        GLfloat v = (atan2(a.z, a.x) / M_PI + 1.0f) * 0.5f;
        return vec2(u,v);
    }
    
    inline
    vec2 uv3(const vec3& a)
    {
        GLfloat len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        GLfloat u = acos(a.y / len) / M_PI;
        GLfloat v = (atan2(a.z, a.x) / M_PI + 1.0f) * 0.5f;
        return vec2(u,v);
    }
    
    inline
    vec2 uv4(const vec4& a)
    {
        GLfloat u = (acos(a.x / sqrt(a.x*a.x + a.z*a.z)) + M_PI)/(2*M_PI);
        GLfloat v = 0.5 - asinf(a.y)/M_PI;
        if(u != u)//347
            u = 0.5;
        return vec2(u,v);
    }
    
    //----------------------------------------------------------------------------
    
}  // namespace Angel

#endif // __ANGEL_VEC_H__
