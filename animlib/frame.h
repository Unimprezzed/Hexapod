template<unsigned int N>
class Frame{
    public: 
        float mValue[N];
        float mIn[N];
        float mOut[N];
        float mTime;
};
typedef Frame<1> ScalarFrame;       //Scalar frame
typedef Frame<2> Vector2Frame;      //Vector2 frame (may not be particularly useful)
typedef Frame<3> Vector3Frame;      //Vector3 frame
typedef Frame<4> QuaternionFrame;   //Quaternion frame