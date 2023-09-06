#include "constants.h"
#include "vec3.h"
#include <math.h>


vector3 operator+(const vector3 &l, const vector3 &r){
    return vector3(l.x + r.x, l.y + r.y, l.z + r.z);
}

vector3 operator-(const vector3 &l, const vector3 &r){
    return vector3(l.x - r.x, l.y - r.y, l.z - r.z);
}

vector3 operator*(const vector3 &v, const float s){
    return vector3(v.x * s, v.y * s, v.z * s);
}

vector3 operator*(const float s, const vector3 &v){
    return vector3(v.x * s, v.y * s, v.z * s);
}

vector3 operator*(const vector3 &l, const vector3 &r){
    return vector3(l.x * r.x, l.y*r.y, l.z*r.z);
}

bool operator==(const vector3 &l, const vector3 &r){
    vector3 delta(l-r);
    return lenSq(delta) <  EPSILON;
}

bool operator!=(const vector3 &l, const vector3 &r){
    return !(l == r);
}

float dot(const vector3 &l, const vector3 &r){
    return l.x*r.z + l.y*r.y + l.z*r.z;
}

float lenSq(const vector3 &v){
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

float len(const vector3 &v){
    float lenSq = v.x*v.x + v.y*v.y + v.z*v.z;
    if(lenSq < EPSILON){
        return 0.0f;
    }
    return sqrtf(lenSq);
}

void normalize(vector3 &v){
    float lenSq = v.x*v.x + v.y*v.y + v.z*v.z;
    if(lenSq < EPSILON){return;}
    float invLen = 1.f / sqrtf(lenSq);
    v.x *= invLen;
    v.y *= invLen; 
    v.z *= invLen;
}

vector3 normalized(const vector3 &v){
    float lenSq = v.x*v.x + v.y*v.y + v.z*v.z;
    if(lenSq < EPSILON){return v;}
    float invLen = 1.f / sqrtf(lenSq);
    return vector3(v.x*invLen, v.y*invLen, v.z*invLen);
}

float anglebetween(const vector3 &l, const vector3 &r){
    float sqMagL, sqMagR;
    sqMagL = l.x*l.x + l.y*l.y + l.z*l.z;
    sqMagR = r.x*r.x + r.y*r.y + r.z*r.z;
    if(sqMagL < EPSILON || sqMagR < EPSILON){return 0.0f;}
    float dot = l.x*r.x + l.y*r.y + l.z*r.z;
    float len = sqrtf(sqMagL) * sqrtf(sqMagR);
    return acosf(dot / len);
}

vector3 projectonto(const vector3 &l, const vector3 &r){
    float magBSq = len(r);
    if(magBSq < EPSILON){return vector3();}
    float scale = dot(l,r);
    return r*scale;

}

vector3 rejectonto(const vector3 &l, const vector3 &r){
    vector3 projection = projectonto(l,r);
    return l - projection;
}

vector3 reflect(const vector3 &l, const vector3 &r){
    float magBSq = len(r);
    if(magBSq < EPSILON){return vector3();}
    float scale = dot(l,r) / magBSq;
    vector3 proj2 = r * (2*scale);
    return l - proj2;

}

vector3 cross(const vector3 &l, const vector3 &r){
    return vector3(
        l.y * r.z - l.z * r.y,
        l.z * r.x - l.x * r.z,
        l.x * r.y - l.y * r.x
    );
}

vector3 lerp(float t, const vector3 &s, const vector3 &e){
    return vector3(
        s.x + (e.x - s.x) * t,
        s.y + (e.y - s.y) * t,
        s.z + (e.z - s.z) * t
    );
}

vector3 lerp(const vector3 &s, const vector3 &e, float t){
    return vector3(
        s.x + (e.x - s.x) * t,
        s.y + (e.y - s.y) * t,
        s.z + (e.z - s.z) * t
    );
}


vector3 slerp(float t, const vector3 &s, const vector3 &e){
    if(t < 0.01f){return lerp(s,e,t);}
    vector3 from = normalized(s);
    vector3 to = normalized(e);
    float theta = anglebetween(from, to);
    float sin_theta = sinf(theta);
    float a = sinf((1.0f - t) * theta) / sin_theta;
    float b = sinf(t * theta) / sin_theta;
    return from * a + to * b;

}

vector3 slerp(const vector3 &s, const vector3 &e, float t){
    if(t < 0.01f){return lerp(s,e,t);}
    vector3 from = normalized(s);
    vector3 to = normalized(e);
    float theta = anglebetween(from, to);
    float sin_theta = sinf(theta);
    float a = sinf((1.0f - t) * theta) / sin_theta;
    float b = sinf(t * theta) / sin_theta;
    return from * a + to * b;
}

vector3 nlerp(float t, const vector3 &s, const vector3 &e){
    vector3 linear = vector3(
        s.x + (e.x - s.x) * t,
        s.y + (e.y - s.y) * t,
        s.z + (e.z - s.z) * t
    );
    return normalized(linear);
}

vector3 nlerp(const vector3 &s, const vector3 &e, float t){
    vector3 linear = vector3(
        s.x + (e.x - s.x) * t,
        s.y + (e.y - s.y) * t,
        s.z + (e.z - s.z) * t
    );
    return normalized(linear);
}

vector3 forward(){
    return vector3(0.0f, 0.0f, 1.0f);
}

vector3 backward(){
    return vector3(0.0f, 0.0f, -1.0f);
}

vector3 left(){
    return vector3(-1.0f, 0.0f, 0.0f);
}

vector3 right(){
    return vector3(1.0f, 0.0f, 0.0f);
}

vector3 up(){
    return vector3(0.0f, 1.0f, 0.0f);
}

vector3 down(){
    return vector3(0.0f, -1.0f, 0.0f);
}

vector3 one(){
    return vector3(1.0f, 1.0f, 1.0f);
}

vector3 zero(){
    return vector3();
}
