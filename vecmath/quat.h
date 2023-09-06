#pragma once

#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

struct quaternion{
    union{
        struct{
            float x;
            float y;
            float z; 
            float w;
        };
        //GCC / Clang / whatever doesn't like it when you try to do this with anonymous structs in anonymous unions. 
        //struct{
        //    vector3 vector;
        //    float scalar;
        //};
        float v[4];
    };
    inline quaternion():
        x(0), y(0), z(0), w(1) { }
    inline quaternion(float _x, float _y, float _z, float _w): 
        x(_x), y(_y), z(_z), w(_w) { }
};

quaternion angleAxis(float angle, const vector3& axis);
quaternion fromTo(const vector3& from, const vector3& to);
vector3 getAxis(const quaternion& quat);
float getAngle(const quaternion& quat);
quaternion operator+(const quaternion& a, const quaternion& b);
quaternion operator-(const quaternion& a, const quaternion& b);
quaternion operator*(const quaternion& a, float b);
quaternion operator*(float a, const quaternion& b);
quaternion operator-(const quaternion& q);
quaternion operator*(const quaternion& Q1, const quaternion& Q2);
vector3 operator*(const quaternion& q, const vector3& v);
vector3 operator*(const vector3& v, const quaternion& q);
quaternion operator^(const quaternion& q, float f);
bool operator==(const quaternion& l, const quaternion& r);
bool operator!=(const quaternion& l, const quaternion& r);
bool sameOrientation(const quaternion& l, const quaternion& r);
float dot(const quaternion& a, const quaternion& b);
float lenSq(const quaternion& q);
float len(const quaternion& q);
void normalize(quaternion& q);
quaternion normalized(const quaternion& q);
quaternion conjugate(const quaternion& q);
quaternion inverse(const quaternion& q);
quaternion mix(const quaternion& from, const quaternion& to, float t);
quaternion nlerp(const quaternion& from, const quaternion& to, float t);
quaternion slerp(const quaternion& start, const quaternion& end, float t);
quaternion lookRotation(const vector3& direction, const vector3& up);
matrix4x4 quaternionToMatrix(const quaternion& q);
quaternion matrixToQuaternion(const matrix4x4& m);

