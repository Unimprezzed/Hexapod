#pragma once

struct vector3{
    union{
        struct{
            float x;
            float y;
            float z;
        };
        float v[3];
    };
    inline vector3() : x(0.0f), y(0.0f), z(0.0f){ }
    inline vector3(float _x, float _y, float _z):  x(_x), y(_y), z(_z) { }
    inline vector3(float *fv) :  x(fv[0]), y(fv[1]), z(fv[2]) { }
};
//operators
vector3 operator+(const vector3 &l, const vector3 &r);
vector3 operator-(const vector3 &l, const vector3 &r);
vector3 operator*(const vector3 &v, const float s);
vector3 operator*(const float s, const vector3 &v);
vector3 operator*(const vector3 &l, const vector3 &r);
bool operator==(const vector3 &l, const vector3 &r);
bool operator!=(const vector3 &l, const vector3 &r);
//vector dot product
float dot(const vector3 &l, const vector3 &r);
//magitude 
float lenSq(const vector3 &v);
float len(const vector3 &v);
//vector normalization
void normalize(vector3 &v);
vector3 normalized(const vector3 &v);
//angle between two vectors
float anglebetween(const vector3 &l, const vector3 &r);
//vector projection / rejection / reflection
vector3 projectonto(const vector3 &l, const vector3 &r);
vector3 rejectonto(const vector3 &l, const vector3 &r);
vector3 reflect(const vector3 &l, const vector3 &r);
//vector cross product
vector3 cross(const vector3 &l, const vector3 &r);
//vector interpolation
vector3 lerp(float t, const vector3 &s, const vector3 &e);
vector3 slerp(float t, const vector3 &s, const vector3 &e);
vector3 nlerp(float t, const vector3 &s, const vector3 &e);
vector3 lerp(const vector3 &s, const vector3 &e, float t);
vector3 slerp(const vector3 &s, const vector3 &e, float t);
vector3 nlerp(const vector3 &s, const vector3 &e, float t);
//constants 
vector3 forward();
vector3 backward();
vector3 left();
vector3 right();
vector3 up();
vector3 down();
vector3 one();
vector3 zero();

