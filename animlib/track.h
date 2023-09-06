#include <vector>
#include "vec3.h"
#include "quat.h"
#include "interp.h"
#include "frame.h"
template<typename T, int N>
class Track{
    protected: 
        std::vector<Frame<N>> mFrames; 
        InterpMethod mInterpolation;
        T SampleConstant(float time, bool looping);
        T SampleLinear(float time, bool looping);
        T SampleCubic(float time, bool looping);
        T Hermite(float time, const T& p1, const T& s1, const T& p2, const T& s2);
        int FrameIndex(float time, bool looping);
        float AdjustTimeToFitTrack(float t, bool looping);
        T Cast(float* value);

    public: 
        Track();
        void Resize(unsigned int size);
        unsigned int size();
        InterpMethod getInterpolation();
        void setInterpolation(InterpMethod interpolation);
        float getStartTime();
        float getEndTime();
        T Sample(float time, bool looping);
        Frame<N>& operator[](unsigned int index);
};
typedef Track<float, 1> ScalarTrack;
typedef Track<vector3, 3> VectorTrack;
typedef Track<quaternion, 4> QuaternionTrack;