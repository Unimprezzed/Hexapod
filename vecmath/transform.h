#pragma once
#include "vec3.h"
#include "mat4.h"
#include "quat.h"

struct Transform{
    vector3 position; 
    quaternion rotation; 
    vector3 scale;

    Transform(const vector3& p, const quaternion& r, const vector3& s) : position(p), rotation(r), scale(s){}
    Transform(): position(vector3(0,0,0)), rotation(quaternion(0,0,0,1)), scale(vector3(1,1,1)){}
};

Transform combine(const Transform& a, const Transform& b);
Transform inverse(const Transform& t);
Transform mix(const Transform& a, const Transform& b, float t);
matrix4x4 transformToMatrix(const Transform& t);
Transform matrixToTransform(const matrix4x4& m);
vector3 transformPoint(const Transform& a, const vector3& b);
vector3 transformVector(const Transform& a, const vector3& b);