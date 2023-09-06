#include "quat.h"
#include "constants.h"
#include <cmath>

quaternion angleAxis(float angle, const vector3& axis){
    vector3 norm = normalized(axis);
    float s = sinf(angle * 0.5f);
    return quaternion(
        norm.x * s, 
        norm.y * s, 
        norm.z * s,
        cosf(angle * 0.5f)
    );
}

quaternion fromTo(const vector3& from, const vector3& to){
    vector3 f = normalized(from);
    vector3 t = normalized(to);
    if(f == t){ return quaternion();}
    else if(f == t * -1.0f){
        vector3 ortho = vector3(1,0,0);
        if(fabsf(f.y) < fabsf(f.x)){
            ortho = vector3(0,1,0);
        }
        if(fabsf(f.z)< fabsf(f.y) && fabsf(f.z) < fabsf(f.x)){
            ortho = vector3(0,0,1);
        }
        vector3 axis = normalized(cross(f, ortho));
        return quaternion(axis.x, axis.y, axis.z, 0);
    }
    vector3 half = normalized(f + t);
    vector3 axis = cross(f, half);
    return quaternion(axis.x, axis.y, axis.z, dot(f, half));
}

vector3 getAxis(const quaternion& quat){
    return normalized(vector3(quat.x, quat.y, quat.z));
}

float getAngle(const quaternion& quat){
    return 2.0f * acosf(quat.w);
}

quaternion operator+(const quaternion& a, const quaternion& b){
    return quaternion(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
}

quaternion operator-(const quaternion& a, const quaternion& b){
    return quaternion(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
}

quaternion operator*(const quaternion& a, float b){
    return quaternion(a.x*b, a.y*b, a.z*b, a.w*b);
}

quaternion operator*(float a, const quaternion& b){
    return quaternion(a*b.x, a*b.y, a*b.z, a*b.w);
}

quaternion operator-(const quaternion& q){
    return quaternion(-q.x, -q.y, -q.z, -q.w);
}

quaternion operator*(const quaternion& Q1, const quaternion& Q2){
    return quaternion(
         Q2.x*Q1.w + Q2.y*Q1.z - Q2.z*Q1.y + Q2.w*Q1.x,
        -Q2.x*Q1.z + Q2.y*Q1.w + Q2.z*Q1.x + Q2.w*Q1.y,
         Q2.x*Q1.y - Q2.y*Q1.x + Q2.z*Q1.w + Q2.w*Q1.z,
        -Q2.x*Q1.x - Q2.y*Q1.y - Q2.z*Q1.z + Q2.w*Q1.w
    );
}

vector3 operator*(const quaternion& q, const vector3& v){
    vector3 qVector = vector3(q.x,q.y,q.z);
    float qScalar = q.w;
    return qVector * 2.0f * dot(qVector,v) + v*(qScalar*qScalar - dot(qVector, qVector)) + cross(qVector, v) * 2.0f * qScalar;
}

vector3 operator*(const vector3& v, const quaternion& q){
    vector3 qVector = vector3(q.x,q.y,q.z);
    float qScalar = q.w;
    return qVector * 2.0f * dot(qVector,v) + v*(qScalar*qScalar - dot(qVector, qVector)) + cross(qVector, v) * 2.0f * qScalar;
}

quaternion operator^(const quaternion& q, float f){
    float angle = 2.0f * acosf(q.w);
    vector3 axis = normalized(vector3(q.x, q.y, q.z));

    float halfCos = cosf(f * angle * 0.5f);
    float halfSin = sinf(f * angle * 0.5f);
    return quaternion(axis.x * halfSin, axis.y*halfSin, axis.z*halfSin, halfCos);
}

bool operator==(const quaternion& l, const quaternion& r){
    return(
        fabsf(l.x - r.x) <= EPSILON && fabsf(l.y - r.y) <= EPSILON && fabsf(l.z - r.z) <= EPSILON && fabsf(l.w - r.w) <= EPSILON);
}

bool operator!=(const quaternion& l, const quaternion& r){
    return !(l == r);
}

bool sameOrientation(const quaternion& l, const quaternion& r){
    return (
        (fabsf(l.x - r.x) <= EPSILON && fabsf(l.y - r.y) <= EPSILON && fabsf(l.z - r.z) <= EPSILON && fabsf(l.w - r.w) <= EPSILON) || 
        (fabsf(l.x + r.x) <= EPSILON && fabsf(l.y + r.y) <= EPSILON && fabsf(l.z + r.z) <= EPSILON && fabsf(l.w + r.w) <= EPSILON));
}

float dot(const quaternion& a, const quaternion& b){
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

float lenSq(const quaternion& q){
    return q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
}

float len(const quaternion& q){
    float lenSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
    if(lenSq < EPSILON){return 0.0f;}
    return sqrtf(lenSq);
}
void normalize(quaternion& q){
    float lenSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
    if(lenSq < EPSILON){return;}
    float i_len = 1.0f / sqrtf(lenSq);
    q.x *= i_len;
    q.y *= i_len;
    q.z *= i_len; 
    q.w *= i_len;
}

quaternion normalized(const quaternion& q){
    float lenSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
    if(lenSq < EPSILON){return quaternion();}
    float i_len = 1.0f / sqrtf(lenSq);
    return quaternion(q.x * i_len, q.y * i_len, q.z * i_len, q.w * i_len);
}

quaternion conjugate(const quaternion& q){
    return quaternion(
        -q.x, 
        -q.y,
        -q.z, 
        -q.w
    );
}

quaternion inverse(const quaternion& q){
    float lenSq = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
    if(lenSq < EPSILON){return quaternion();}
    float i_len = 1.0f / lenSq;
    return quaternion(
        -q.x * i_len, 
        -q.y * i_len,
        -q.z * i_len,
        -q.w * i_len
    );
}

quaternion mix(const quaternion& from, const quaternion& to, float t){
    return from * (1.0f - t) + to*t;
}

quaternion nlerp(const quaternion& from, const quaternion& to, float t){
    return normalized(from + (to - from)*t);
}

quaternion slerp(const quaternion& start, const quaternion& end, float t){
    if(fabsf(dot(start,end)) > 1.0f - EPSILON){
        return nlerp(start, end, t);
    }
    quaternion delta = inverse(start) * end; 
    return normalized((delta^t)*start);
}

quaternion lookRotation(const vector3& direction, const vector3& up){
    vector3 f = normalized(direction);  //Local forward
    vector3 u = normalized(up);         //Desired up
    vector3 r = cross(u,f);             //Local Right
    u = cross(f,r);                     //Local Up
    //World forward --> Object forward
    quaternion worldToLocal = fromTo(vector3(0,0,1), f);
    //Calculate new object up
    vector3 localUp = worldToLocal * vector3(0,1,0);
    //Local up --> desired up
    quaternion u2u = fromTo(localUp, u);

    //Rotate to forward direction first, then twist to correct up
    quaternion result = worldToLocal * u2u;
    return normalized(result);
}

matrix4x4 quaternionToMatrix(const quaternion& q){
    vector3 r = q * vector3(1,0,0);
    vector3 u = q * vector3(0,1,0);
    vector3 f = q * vector3(0,0,1);
    return matrix4x4(r.x, r.y, r.z, 0,
                     u.x, u.y, u.z, 0,
                     f.x, f.y, f.z, 0,
                     0,   0,   0,   1);  
}

quaternion matrixToQuaternion(const matrix4x4& m){
    vector3 up = normalized(vector3(m.yx, m.yy, m.yz));
    vector3 forward = normalized(vector3(m.zx, m.zy, m.zz));
    vector3 right = cross(up, forward);
    up = cross(forward, right);
    return lookRotation(forward, up);
}