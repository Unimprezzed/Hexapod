#include "track.h"

template Track<float, 1>; 
template Track<vector3, 3>;
template Track<quaternion, 4>;

namespace TrackHelpers{
    inline float Interpolate(float a, float b, float t){
        return a + (b-a)*t;
    }
    inline vector3 Interpolate(const vector3& a, const vector3& b, float t){
        return lerp(a,b,t);
    }
    inline quaternion Interpolate(const quaternion& a, const quaternion& b, float t){
        quaternion result = mix(a,b,t);
        if(dot(a,b) < 0){
            result = mix(a, -b, t);
        }
        return normalized(result);
    }
    inline float AdjustHermiteResult(float f){ return f;}
    inline vector3 AdjustHermiteResult(const vector3& v){ return v;}
    inline quaternion AdjustHermiteResult(const quaternion& q){ return normalized(q);}
    inline void Neighborhood(const float& a, float& b){}
    inline void Neighborhood(const vector3& a, vector3& b){}
    inline void Neighborhood(const quaternion& a, quaternion& b){
        if (dot(a,b) < 0){
            b = -b;
        }
    }
};

