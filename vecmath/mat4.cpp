#include "mat4.h"
#include "constants.h"
#include <cmath>


//Macro to make matrix multiplication easier
#define M4D(lrow, rcol) \
    l.v[0 * 4 + lrow] * r.v[rcol * 4 + 0] + \
    l.v[1 * 4 + lrow] * r.v[rcol * 4 + 1] + \
    l.v[2 * 4 + lrow] * r.v[rcol * 4 + 2] + \
    l.v[3 * 4 + lrow] * r.v[rcol * 4 + 3]

//Macro to make vector4 calculations easier
#define M4V4D(mRow, x,y,z,w) \
    x * m.v[0 * 4 + mRow] + \
    y * m.v[1 * 4 + mRow] + \
    z * m.v[2 * 4 + mRow] + \
    w * m.v[3 * 4 + mRow]

//Macro for making transposition easier
#define M4SWAP(x,y) \
    {float t = x; x = y; y = t;}

#define M4_3X3MINOR(x, c0, c1, c2, r0, r1, r2) \
   (x[c0*4+r0]*(x[c1*4+r1]*x[c2*4+r2]-x[c1*4+r2]* \ 
   x[c2*4+r1])-x[c1*4+r0]*(x[c0*4+r1]*x[c2*4+r2]- \
   x[c0*4+r2]*x[c2*4+r1])+x[c2*4+r0]*(x[c0*4+r1]* \ 
   x[c1*4+r2]-x[c0*4+r2]*x[c1*4+r1]))

bool operator==(const matrix4x4& l, const matrix4x4& r){
    for(int i = 0; i < 16; ++i){
        if(fabsf(l.v[i] - r.v[i]) > EPSILON){
            return false;
        }
    }
    return true;
}

bool operator!=(const matrix4x4& l, const matrix4x4& r){
    return !(l==r);
}

matrix4x4 operator+(const matrix4x4& l, const matrix4x4& r){
    return matrix4x4(
        l.xx + r.xx, l.xy + r.xy, l.xz + r.xz, l.xw + r.xw,
        l.yx + r.yx, l.yy + r.yy, l.yz + r.yz, l.yw + r.yw,
        l.zx + r.zx, l.zy + r.zy, l.zz + r.zz, l.zw + r.zw,
        l.tx + r.tx, l.ty + r.ty, l.tz + r.tz, l.tw + r.tw
    );
}

matrix4x4 operator-(const matrix4x4& l, const matrix4x4& r){
    return matrix4x4(
        l.xx - r.xx, l.xy - r.xy, l.xz - r.xz, l.xw - r.xw,
        l.yx - r.yx, l.yy - r.yy, l.yz - r.yz, l.yw - r.yw,
        l.zx - r.zx, l.zy - r.zy, l.zz - r.zz, l.zw - r.zw,
        l.tx - r.tx, l.ty - r.ty, l.tz - r.tz, l.tw - r.tw
    );
}

matrix4x4 operator*(const matrix4x4& m, float f){
    return matrix4x4(
        m.xx * f, m.xy *f, m.xz *f, m.xw *f,
        m.yx * f, m.yy *f, m.yz *f, m.yw *f,
        m.zx * f, m.zy *f, m.zz *f, m.zw *f,
        m.tx * f, m.ty *f, m.tz *f, m.tw *f
    );
}

matrix4x4 operator*(float f, const matrix4x4& m){
    return matrix4x4(
        m.xx * f, m.xy *f, m.xz *f, m.xw *f,
        m.yx * f, m.yy *f, m.yz *f, m.yw *f,
        m.zx * f, m.zy *f, m.zz *f, m.zw *f,
        m.tx * f, m.ty *f, m.tz *f, m.tw *f
    );
}

matrix4x4 operator*(const matrix4x4& l, const matrix4x4& r){
    return matrix4x4(
        M4D(0,0),M4D(1,0),M4D(2,0),M4D(3,0),
        M4D(0,1),M4D(1,1),M4D(2,1),M4D(3,1),
        M4D(0,2),M4D(1,2),M4D(2,2),M4D(3,2),
        M4D(0,3),M4D(1,3),M4D(2,3),M4D(3,3)
    );
}

vector4_f operator*(const matrix4x4& m, const vector4_f& v){
    return vector4_f(
        M4V4D(0, v.x, v.y, v.z, v.w),
        M4V4D(1, v.x, v.y, v.z, v.w),
        M4V4D(2, v.x, v.y, v.z, v.w),
        M4V4D(3, v.x, v.y, v.z, v.w)
    );
}

vector3 transformVector(const matrix4x4& m, const vector3& v){
    return vector3(
        M4V4D(0, v.x, v.y, v.z, 0.0f),
        M4V4D(1, v.x, v.y, v.z, 0.0f),
        M4V4D(2, v.x, v.y, v.z, 0.0f)
    );
}

vector3 transformPoint(const matrix4x4& m, const vector3& v){
    return vector3(
        M4V4D(0, v.x, v.y, v.z, 1.0f),
        M4V4D(1, v.x, v.y, v.z, 1.0f),
        M4V4D(2, v.x, v.y, v.z, 1.0f)
    );
}

vector3 transformPoint(const matrix4x4& m, const vector3& v, float& w){
    float _w = w;
    w = M4V4D(3, v.x, v.y, v.z, _w);

    return vector3(
        M4V4D(0, v.x, v.y, v.z, _w),
        M4V4D(1, v.x, v.y, v.z, _w),
        M4V4D(2, v.x, v.y, v.z, _w)
    );
}

void transpose(matrix4x4& m){
    M4SWAP(m.yx, m.xy);
    M4SWAP(m.zx, m.xz);
    M4SWAP(m.tx, m.xw);
    M4SWAP(m.zy, m.yz);
    M4SWAP(m.ty, m.yw);
    M4SWAP(m.tz, m.zw);
}

matrix4x4 transposed(const matrix4x4& m){
    return matrix4x4(
        m.xx, m.yx, m.zx, m.tx,
        m.xx, m.yx, m.zx, m.tx,
        m.xx, m.yx, m.zx, m.tx,
        m.xx, m.yx, m.zx, m.tx
    );
}

float determinant(const matrix4x4& m){
    return m.v[0] * M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3) - m.v[4] *M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3) + m.v[8] *M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3) - m.v[12]*M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3);
}

matrix4x4 adjugate(const matrix4x4& m){
    //Cof (M[i, j]) = Minor(M[i, j]] * pow(-1, i + j) 
    matrix4x4 cofactor; 
    cofactor.v[0] = M4_3X3MINOR(m.v, 1, 2, 3, 1, 2, 3); 
    cofactor.v[1] =-M4_3X3MINOR(m.v, 1, 2, 3, 0, 2, 3); 
    cofactor.v[2] = M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 3); 
    cofactor.v[3] =-M4_3X3MINOR(m.v, 1, 2, 3, 0, 1, 2); 
    cofactor.v[4] =-M4_3X3MINOR(m.v, 0, 2, 3, 1, 2, 3); 
    cofactor.v[5] = M4_3X3MINOR(m.v, 0, 2, 3, 0, 2, 3); 
    cofactor.v[6] =-M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 3); 
    cofactor.v[7] = M4_3X3MINOR(m.v, 0, 2, 3, 0, 1, 2); 
    cofactor.v[8] = M4_3X3MINOR(m.v, 0, 1, 3, 1, 2, 3); 
    cofactor.v[9] =-M4_3X3MINOR(m.v, 0, 1, 3, 0, 2, 3); 
    cofactor.v[10]= M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 3); 
    cofactor.v[11]=-M4_3X3MINOR(m.v, 0, 1, 3, 0, 1, 2); 
    cofactor.v[12]=-M4_3X3MINOR(m.v, 0, 1, 2, 1, 2, 3); 
    cofactor.v[13]= M4_3X3MINOR(m.v, 0, 1, 2, 0, 2, 3); 
    cofactor.v[14]=-M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 3); 
    cofactor.v[15]= M4_3X3MINOR(m.v, 0, 1, 2, 0, 1, 2); 
    return transposed(cofactor);
}

matrix4x4 inverse(const matrix4x4& m){
     float det = determinant(m); 
    if (det == 0.0f) { 
        
        return matrix4x4(); 
    } 
    matrix4x4 adj = adjugate(m); 
    return adj * (1.0f / det);
}

void invert(matrix4x4& m){
     float det = determinant(m); 
    if (det == 0.0f) {  
        m = matrix4x4(); 
        return; 
    } 
    m = adjugate(m) * (1.0f / det);
}