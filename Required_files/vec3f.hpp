//
//  vec3f.hpp
//  3dBounce
//
//  Created by Sujal Dhungana on 2/14/16.
//  Copyright © 2016 example. All rights reserved.
//

#ifndef vec3f_hpp
#define vec3f_hpp

#include <iostream>
using std::ostream;

class Vec3f {
    
public:
    float v[3];
    Vec3f();
    Vec3f(float x, float y, float z);
    
    float returnv0();
    float returnv1();
    float returnv2();
    
    float &operator[](int index);
    float operator[](int index) const;
    
    Vec3f operator*(float scale) const;
    Vec3f operator/(float scale) const;
    Vec3f operator+(const Vec3f &other) const;
    Vec3f operator-(const Vec3f &other) const;
    Vec3f operator-() const;
    
    const Vec3f &operator*=(float scale);
    const Vec3f &operator/=(float scale);
    const Vec3f &operator+=(const Vec3f &other);
    const Vec3f &operator-=(const Vec3f &other);
    
    float magnitude() const;
    float magnitudeSquared() const;
    Vec3f normalize() const;
    float dot(const Vec3f &other) const;
    Vec3f cross(const Vec3f &other) const;
    Vec3f rotate(float Angle, Vec3f Axis);
    
};

Vec3f operator*(float scale, const Vec3f &v);
ostream &operator<<(ostream &output, const Vec3f &v);

struct Quaternion
{
    float x, y, z, w;
    
    Quaternion(float _x, float _y, float _z, float _w);
    
    void normalize();
    
    Quaternion Conjugate();
    
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vec3f& v);

#endif /* vec3f_hpp */
