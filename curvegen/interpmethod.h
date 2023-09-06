#pragma once
#include <vector>
template <typename T> 
class InterpolationMethod{
    public: 
        T evaluate(std::vector<T> P, float t) = 0;
};