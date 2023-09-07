#pragma once
#include "interpmethod.h"
template <typename T> 
class BezierCubicInterpolation : public InterpolationMethod<T>{
    public: 
        T evaluate(std::vector<T> P, float t);
};