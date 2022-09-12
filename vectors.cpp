template <typename T>
vec<T> init_vec(int siz)
{
    vec<T>  f;
    f.siz = siz;
    f.val = (T*) malloc(siz * sizeof(T));
    debug_alloc_memory += siz * sizeof(T);
    return f;
}

template <typename T>
vec<T> make_vec(int siz, ...)
{
    vec<T> f = init_vec<T>(siz);
    va_list valist;
    va_start(valist, siz);
    for (int n = 0 ; n < siz; n++) {
        f.val[n] = va_arg(valist, T);
    }
    return f;
}

template <typename T>
int free(vec<T> f)
{
    free(f.val);
    debug_alloc_memory -= sizeof(T) * f.siz;
    return 0;
}

template <typename T>
int resize_vec(vec<T> *f, int N)
{
    debug_alloc_memory += sizeof(T) * (N - f->siz);
    (*f).val = (T *) realloc((*f).val, sizeof(T) * N);
    (*f).siz = N;
    return 0;
}

template <typename T>
int free(matrix<T> H)
{
    debug_alloc_memory -= sizeof(T) * H.height * H.width;
    free(H.val);
    return 0;
}

template <typename T>
vec<T> take_vec(vec<T> f, int first, int last)
{
    if (last > f.siz - 1) {
        printf("error in take_vec: last > f.siz - 1\n");
        exit(-1);
    } else if (first < 0) {
        printf("error in take_vec: first < 0\n");
        exit(-2);
    } else {
        vec<T> out;
        out.val = f.val + first;
        if (last < first) {
            out.siz = 0;
        } else {
            out.siz = last - first + 1;
        }
        return out;
    }
}

template <typename T>
vec<T> matrix<T>::operator[](int n)
{
    if ((n < 0) || (n >= height)) {
        printf("error in vec<T> matrix<T>::operator[](int n): (n < 0) || (n >= height)\n");
        exit(-1);
    } else {
        vec<T> f;
    f.siz = width;
    f.val = val + width * n;
    return f;
    }
}

template <typename T>
int zero_vec(vec<T> f)
{
    return uni_vec(f, 0);
}

template <typename T>
int uni_vec(vec<T> f, T x)
{
    T *p = f.val, *pend = f.val + f.siz;
    while(p < pend) {
        *p = x;
        p++;
    }
    return 0;
}

template <typename T>
int copy_vec(vec<T> in, vec<T> out)
{
    if (in.siz != out.siz) {
        printf("error in copy_vec: in.siz != out.siz");
        exit(-1);
    } else {
        T *pi = in.val, *piend = in.val + in.siz;
        T *po = out.val;
        while (pi < piend) {
            *po = *pi;
            pi++; po++;
        }
        return 0;
    }
}

template <typename T>
int multiply(vec<T> f, vec<T> h, vec<T> fh)
{
    if (f.siz != h.siz) {
        printf("error in multiply(vec<T> f, vec<T> h, vec<T> fh): f.siz != h.siz\n");
        exit(-1);
    } else if (f.siz != fh.siz) {
        printf("error in multiply(vec<T> f, vec<T> h, vec<T> fh): f.siz != fh.siz\n");
        exit(-1);
    } else {
        T *pf = f.val, *ph = h.val, *pfh = fh.val;
        T *pendf = f.val + f.siz;
        while (pf < pendf) {
            *pfh = (*pf) * (*ph);
            pf++; ph++; pfh++;
        }
        return 0;
    }
}

template <typename T1, typename T2, typename T3>
int multiply_asym(vec<T1> f, vec<T2> h, vec<T3> fh)
{
    if (f.siz != h.siz) {
        printf("error in multiply(vec<T1> f, vec<T2> h, vec<T3> fh): f.siz != h.siz\n");
        exit(-1);
    } else if (f.siz != fh.siz) {
        printf("error in multiply(vec<T1> f, vec<T2> h, vec<T3> fh): f.siz != fh.siz\n");
        exit(-1);
    } else {
        T1 *pf = f.val, *pendf = f.val + f.siz;
        T2 *ph = h.val;
        T3 *pfh = fh.val;
        while (pf < pendf) {
            *pfh = (*pf) * (*ph);
            pf++; ph++; pfh++;
        }
        return 0;
    }
}

template <typename T>
int uni_matrix(matrix<T> H, T x)
{
    for (int n = 0; n < H.height; n++) {
        uni_vec(H[n], x);
    }
    return 0;
}

template <typename T>
int multiply(matrix<T> A, matrix<T> B, matrix<T> AB)
{
    if ((A.height != B.height) || (A.width != B.width)) {
        printf("error in multiply(matrix<T> A, matrix<T> B, matrix<T> AB): A and B matrix sizes are different\n");
        exit(-1);
    } else if ((A.height != AB.height) || (A.width != AB.width)) {
        printf("error in multiply(matrix<T> A, matrix<T> B, matrix<T> AB): A and AB matrix sizes are different\n");
        exit(-1);
    } else {
        for (int n = 0; n < A.height; n++) {
            multiply(A[n], B[n], AB[n]);
        }
        return 0;
    }
}

template <typename T>
int disp(vec<T> f)
{
    T *p = f.val, *pend = f.val + f.siz;
    while (p < pend) {
        disp(*p);
        p++;
    }
    return 0;
}

template <typename T>
int disp(vec<T> f, const char delim[])
{
    T *p = f.val, *pend = f.val + f.siz;
    while (p < pend - 1) {
        disp(*p);
        printf("%s", delim);
        p++;
    }
    if (p < pend) disp(*p);
    return 0;
}

template <typename T>
int disp(matrix<T> H)
{
    for (int m = 0; m < H.height; m++) {
        disp(H[m]);
        printf("\n");
    }
    return 0;
}

template <typename T>
int disp(matrix<T> H, const char delim[])
{
    for (int m = 0; m < H.height; m++) {
        disp(H[m], delim);
        printf("\n");
    }
    return 0;
}

int
disp(int x)
{
    return printf("%d", x);
}

int
disp(double x)
{
    return printf("%g", x);
}

template <typename T>
int dispe(T H)
{
    int a = disp(H);
    printf("\n");
    return a;
}

template <typename T>
int dispe(T H, const char delim[])
{
    int a = disp(H, delim);
    printf("\n");
    return a;
}
