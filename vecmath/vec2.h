template<typename T>
struct TV2{
    union{
        struct{
            T x;
            T y; 
        };
        T v[2];
    };
    inline TV2() : x(T(0)), y(T(0)) {}
    inline TV2(T _x, T _y): x(_x), y(_y) { }
    inline TV2(T* fv) : x(fv[0]), y(fv[1]) {} 
};

typedef TV2<float> vector2_f;
typedef TV2<int> vector2_int;
typedef TV2<unsigned int> vector2_uint;