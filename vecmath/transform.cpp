#include "transform.h"
#include "constants.h"
#include <cmath>

Transform combine(const Transform& a, const Transform& b){
    Transform out; 
    out.scale = a.scale * b.scale;
    out.rotation = b.rotation * a.rotation;
    out.position = a.rotation * (a.scale * b.position);
    out.position = a.position * out.position; 
    return out;
}

Transform inverse(const Transform& t){
    Transform inv; 
    inv.rotation = inverse(t.rotation);

    inv.scale.x = fabs(t.scale.x) < EPSILON ? 0.0f : 1.0f / t.scale.x;
    inv.scale.y = fabs(t.scale.y) < EPSILON ? 0.0f : 1.0f / t.scale.y;
    inv.scale.z = fabs(t.scale.z) < EPSILON ? 0.0f : 1.0f / t.scale.z;
    vector3 invTrans = t.position * -1.0f;
    inv.position = inv.rotation * (inv.scale * invTrans);
    return inv;
}

Transform mix(const Transform& a, const Transform& b, float t){
    quaternion bRot = b.rotation;
    if(dot(a.rotation, bRot) < 0.0f){bRot = -bRot;}
    return Transform(
        lerp(a.position, b.position, t),
        nlerp(a.rotation, bRot, t),
        lerp(a.scale, b.scale, t)
    );
}

matrix4x4 transformToMatrix(const Transform& t){
    vector3 x = t.rotation * vector3(1,0,0);
    vector3 y = t.rotation * vector3(0,1,0);
    vector3 z = t.rotation * vector3(0,0,1);
    x = x * t.scale.x; //Shouldn't I make a *= operator in vector3 to handle this in a less clunky way? 
    y = y * t.scale.y; 
    z = z * t.scale.z; 
    //Extract position of the transform
    vector3 p = t.position;
    return matrix4x4(
        x.x, x.y, x.z, 0,   // X basis vector (with scale)
        y.x, y.y, y.z, 0,   // Y basis vector (with scale)
        z.x, z.y, z.z, 0,   // Z basis vector (with scale)
        p.x, p.y, p.z, 1    // Position vector
    );
}

Transform matrixToTransform(const matrix4x4& m){
    Transform out; 
    out.position = vector3(m.v[12], m.v[13], m.v[14]);
    out.rotation = matrixToQuaternion(m);
    matrix4x4 rotScaleMatrix(
        m.v[0], m.v[1], m.v[2], 0,
        m.v[4], m.v[5], m.v[6], 0,
        m.v[8], m.v[9], m.v[10], 0,
        0, 0, 0, 1
    );
    matrix4x4 invRotMatrix = quaternionToMatrix(inverse(out.rotation));
    matrix4x4 scaleSkewMatrix = rotScaleMatrix * invRotMatrix;
    out.scale = vector3(
        scaleSkewMatrix.v[0],
        scaleSkewMatrix.v[5],
        scaleSkewMatrix.v[10]
    );
    return out;
}
//Transform a point with respect to its original position
vector3 transformPoint(const Transform& a, const vector3& b){
    vector3 out; 
    out = a.rotation * (a.scale * b);
    out = a.position + out; // += ?
    return out; 
}
//Transform a vector (similar operation)
vector3 transformVector(const Transform& a, const vector3& b){
    vector3 out; 
    out = a.rotation * (a.scale * b);
    return out; 
}