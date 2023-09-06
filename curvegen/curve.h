#include <vector>
#include "interpmethod.h"
template<typename T>
class Curve{
    protected: 
        std::vector<T> P;
        InterpolationMethod interpolation;
    public:
        Curve(std::vector<T> _P, InterpolationMethod interpolation);
        T evaluate(float t);
};