#include <stdarg.h>

template <typename T>
struct vec{
    int siz;
    T *val;
    T &operator[](int n) {return val[n];}
    T first() {return *val;}
    T last() {return *(val + siz - 1);}
};

template <typename T>
vec<T> init_vec(int siz);

template <typename T> // only basic types (int, double, ...)
vec<T> make_vec(int siz, ...);

template <typename T>
int free(vec<T> f);

template <typename T>
int resize_vec(vec<T> *f, int N);

template <typename T>
struct matrix{
    private:
        T *val;
    public:
        int height;
        int width;
        matrix<T>(int a_height, int a_width) {
            height = a_height;
            width = a_width;
            val = (T*) malloc(height * width * sizeof(T));
            debug_alloc_memory += height * width * sizeof(T);
        }
        vec<T> operator[](int n);
};

template <typename T>
int free(matrix<T> H);

template <typename T>
vec<T> take_vec(vec<T> f, int first, int last);

template <typename T>
int zero_vec(vec<T> f);

template <typename T>
int uni_vec(vec<T> f, T x);

template <typename T>
int copy_vec(vec<T> in, vec<T> out);

template <typename T>
int multiply(vec<T> f, vec<T> h, vec<T> fh);

template <typename T1, typename T2, typename T3>
int multiply_asym(vec<T1> f, vec<T2> h, vec<T3> fh);

template <typename T>
int uni_matrix(matrix<T> H, T x);

template <typename T>
int multiply(matrix<T> A, matrix<T> B, matrix<T> AB);

template <typename T>
int disp_vec(vec<T> f);

template <typename T>
int disp(vec<T> f, const char delim[]);

template <typename T>
int disp(matrix<T> H);

template <typename T>
int disp(matrix<T> H, const char delim[]);

int
disp(int x);

int
disp(double x);

template <typename T>
int dispe(T H);

template <typename T>
int dispe(T H, const char delim[]);
