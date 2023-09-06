#pragma once
#include "vec4.h"
#include "vec3.h"
struct matrix4x4{
    union{
        float v[16];
        struct{ 
            float xx; float xy; float xz; float xw; //Column 1
            float yx; float yy; float yz; float yw; //Column 2
            float zx; float zy; float zz; float zw; //Column 3
            float tx; float ty; float tz; float tw; //Column 4
        };
        struct{
            float c0r0; float c0r1; float c0r2; float c0r3; 
            float c1r0; float c1r1; float c1r2; float c1r3;
            float c2r0; float c2r1; float c2r2; float c2r3;
            float c3r0; float c3r1; float c3r2; float c3r3;
        };
        struct{
            float r0c0; float r1c0; float r2c0; float r3c0;
            float r0c1; float r1c1; float r2c1; float r3c1;
            float r0c2; float r1c2; float r2c2; float r3c2;
            float r0c3; float r1c3; float r2c3; float r3c3;
        };
    };
    inline matrix4x4():
        xx(1), xy(0), xz(0), xw(0),
        yx(0), yy(1), yz(0), yw(0),
        zx(0), zy(0), zz(1), zw(0),
        tx(0), ty(0), tz(0), tw(1) {}

    inline matrix4x4(float *fv):
        xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
        yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
        zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
        tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) {}
    
    inline matrix4x4(
        float _00, float _01, float _02, float _03,
        float _10, float _11, float _12, float _13,
        float _20, float _21, float _22, float _23,
        float _30, float _31, float _32, float _33
    ) : xx(_00), xy(_01), xz(_02), xw(_03),
        yx(_10), yy(_11), yz(_12), yw(_13),
        zx(_20), zy(_21), zz(_22), zw(_23),
        tx(_30), ty(_31), tz(_32), tw(_33) {}
};
bool operator==(const matrix4x4& l, const matrix4x4& r);
bool operator!=(const matrix4x4& l, const matrix4x4& r);
matrix4x4 operator+(const matrix4x4& l, const matrix4x4& r);
matrix4x4 operator-(const matrix4x4& l, const matrix4x4& r);
matrix4x4 operator*(const matrix4x4& m, float f);
matrix4x4 operator*(float f, const matrix4x4& m);
matrix4x4 operator*(const matrix4x4& l, float r);
vector4_f operator*(const matrix4x4& m, const vector4_f& v);
matrix4x4 operator*(const matrix4x4& l, const matrix4x4& r);
vector3 transformVector(const matrix4x4& m, const vector3& v);
vector3 transformPoint(const matrix4x4& m, const vector3& v);
vector3 transformPoint(const matrix4x4& m, const vector3& v, float& w);
void transpose(matrix4x4& m);
matrix4x4 transposed(const matrix4x4& m);
float determinant(const matrix4x4& m);
matrix4x4 adjugate(const matrix4x4& m);
matrix4x4 inverse(const matrix4x4& m);
void invert(matrix4x4& m);



