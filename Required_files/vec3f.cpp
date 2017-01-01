//
//  vec3f.cpp
//  3dBounce
//
//  Created by Sujal Dhungana on 2/14/16.
//  Copyright © 2016 example. All rights reserved.
//

#include "vec3f.hpp"
#include "cmath"

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

using namespace std;
Vec3f::Vec3f() {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}

Vec3f::Vec3f(float x, float y, float z = 0.0) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

float Vec3f::returnv0(){return v[0];}
float Vec3f::returnv1(){return v[1];}
float Vec3f::returnv2(){return v[2];}

float &Vec3f::operator[](int index) {
    return v[index];
}

float Vec3f::operator[](int index) const {
    return v[index];
}

Vec3f Vec3f::operator*(float scale) const {
    return Vec3f(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vec3f Vec3f::operator/(float scale) const {
    return Vec3f(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vec3f Vec3f::operator+(const Vec3f &other) const {
    return Vec3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vec3f Vec3f::operator-(const Vec3f &other) const {
    return Vec3f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vec3f Vec3f::operator-() const {
    return Vec3f(-v[0], -v[1], -v[2]);
}

const Vec3f &Vec3f::operator*=(float scale) {
    v[0] *= scale;
    v[1] *= scale;
    v[2] *= scale;
    return *this;
}

const Vec3f &Vec3f::operator/=(float scale) {
    v[0] /= scale;
    v[1] /= scale;
    v[2] /= scale;
    return *this;
}

const Vec3f &Vec3f::operator+=(const Vec3f &other) {
    v[0] += other.v[0];
    v[1] += other.v[1];
    v[2] += other.v[2];
    return *this;
}

const Vec3f &Vec3f::operator-=(const Vec3f &other) {
    v[0] -= other.v[0];
    v[1] -= other.v[1];
    v[2] -= other.v[2];
    return *this;
}

float Vec3f::magnitude() const {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vec3f::magnitudeSquared() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vec3f Vec3f::normalize() const {
    float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return Vec3f(v[0] / m, v[1] / m, v[2] / m);
}

float Vec3f::dot(const Vec3f &other) const {
    return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vec3f Vec3f::cross(const Vec3f &other) const {
    return Vec3f(v[1] * other.v[2] - v[2] * other.v[1],
                 v[2] * other.v[0] - v[0] * other.v[2],
                 v[0] * other.v[1] - v[1] * other.v[0]);
}

Vec3f operator*(float scale, const Vec3f &v) {
    return v * scale;
}

Vec3f Vec3f::rotate(float Angle, Vec3f Axis)
{
    const float SinHalfAngle = sinf(ToRadian(Angle/2));
    const float CosHalfAngle = cosf(ToRadian(Angle/2));
    
    const float Rx = Axis.v[0] * SinHalfAngle;
    const float Ry = Axis.v[1] * SinHalfAngle;
    const float Rz = Axis.v[2] * SinHalfAngle;
    const float Rw = CosHalfAngle;
    Quaternion RotationQ(Rx, Ry, Rz, Rw);
    
    Quaternion ConjugateQ = RotationQ.Conjugate();
    //  ConjugateQ.Normalize();
    Quaternion W = RotationQ * (*this) * ConjugateQ;
        return Vec3f(W.x,W.y,W.z);
}


Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}


void Quaternion::normalize()
{
    float Length = sqrtf(x * x + y * y + z * z + w * w);
    
    x /= Length;
    y /= Length;
    z /= Length;
    w /= Length;
}


Quaternion Quaternion::Conjugate()
{
    Quaternion ret(-x, -y, -z, w);
    return ret;
}


Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
    const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);
    
    Quaternion ret(x, y, z, w);
    
    return ret;
}

Quaternion operator*(const Quaternion& q, const Vec3f& v)
{
    const float w = - (q.x * v.v[0]) - (q.y * v.v[1]) - (q.z * v.v[2]);
    const float x =   (q.w * v.v[0]) + (q.y * v.v[2]) - (q.z * v.v[1]);
    const float y =   (q.w * v.v[1]) + (q.z * v.v[0]) - (q.x * v.v[2]);
    const float z =   (q.w * v.v[2]) + (q.x * v.v[1]) - (q.y * v.v[0]);
    
    Quaternion ret(x, y, z, w);
    
    return ret;
}



ostream &operator<<(ostream &output, const Vec3f &v) {
    cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
    return output;
}

