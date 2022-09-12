//-------------------------------------------------------
//-------------------------------------------------------
fractal
init_fractal()
{
    return init_fractal(0);
}

fractal
init_fractal(int N)
{
    fractal F;
    F.lines = init_vec<line>(N);
    return F;
}

int
resize_fractal(fractal *F, int N)
{
    fractal newF = init_fractal(N);
    if (N > (F->siz())) {
        copy_vec(F->lines, take_vec(newF.lines, 0, F->siz() - 1));
    } else {
        copy_vec(take_vec(F->lines, 0, newF.siz() - 1), newF.lines);
    }
    free(*F);
    *F = newF;
    return 0;
}

int
free(fractal F)
{
    free(F.lines);
    return 0;
}

frac_root
init_frac_root()
{
    return init_frac_root(0);
}

frac_root
init_frac_root(int N)
{
    frac_root S;
    S.lines = init_vec<line>(N);
    return S;
}

int
resize_frac_root(frac_root *S, int N)
{
    frac_root newS = init_frac_root(N);
    if (N > (S->siz())) {
        copy_vec(S->lines, take_vec(newS.lines, 0, S->siz() - 1));
    } else {
        copy_vec(take_vec(S->lines, 0, newS.siz() - 1), newS.lines);
    }
    newS.kern = S->kern;
    free(*S);
    *S = newS;
    return 0;
}

int
free(frac_root S)
{
    return free(S.lines);
}

int
disp(fractal F)
{
    return disp(F.lines);
}

//--------------------------------------------------

int
add_line(frac_root *S, line L)
{
    resize_frac_root(S, S->siz() + 1);
    S->lines[S->siz() - 1] = L;
    return 0;
}

int
cancel_last_point(fr_state *f_st, frac_root *S)
{
    if (S->siz() == 0) {
        f_st->linebegin = 0;
    } else if (f_st->linebegin == 0) {
        f_st->linebegin = 1;
        f_st->act_p = S->lines.last().P2;
    } else if (f_st->act_p != S->lines.last().P2) {
        f_st->act_p = S->lines.last().P2;
    } else {
        f_st->act_p = S->lines.last().P1;
        resize_frac_root(S, S->siz() - 1);
    }
    return 0;
}

int
finalize_root(frac_root *S)
{
    if (S->siz() > 0) {
        S->kern = make_line(S->lines[0].P1, S->lines.last().P2);
    }
    return 0;
}

int
draw_frac_root(frac_root S, sdl_complex H, fr_state f_st)
{
    draw(S.lines, H, f_st.fr_col);
    draw(S.kern, H, f_st.kern_col);
    return 0;
}

//--------------------------------------------------

int
start_fractal(frac_root Sample, fractal *F)
{
    *F = init_fractal(Sample.siz());
    copy_vec(Sample.lines, F->lines);
    return 0;
}

int
add_fractal_layer(frac_root Sample, fractal *F, int width, int height)
{
    int N = F->siz();
    int M = Sample.siz();
    if (M * N == 0) {
        return 0;
    } else if (M * N > fr_limit_line_num){
        return -1;
    } else if (check_fractal_size(*F, width, height)) {
        return -2;
    } else {
        fractal newF = add_fractal_layer(Sample, *F);
        free(*F);
        *F = newF;
        return 1;
    }
}

fractal
add_fractal_layer(frac_root Sample, fractal F0)
{
    int N = F0.siz();
    int M = Sample.siz();
    fractal F = init_fractal(M * N);
    line *p = F.lines.val, *p0 = F0.lines.val, *p0end = F0.lines.val + N;
    while (p0 < p0end) {
        insert_segment(Sample, *p0, p);
        p0++; p += M;
    }
    return F;
}


int
insert_segment(frac_root Sample, line L0, line *L)
{
    //point shift = L0.P1 - Sample.kern.P1;
    double a = 0, b = 0;
    make_ab(&a, &b, Sample.kern, L0);
    line *p = L;
    line *s = Sample.lines.val, *send = Sample.lines.val + Sample.lines.siz;
    point S0 = Sample.kern.P1, P0 = L0.P1;
    while (s < send) {
        insert_line(S0, *s, P0, p, a, b);
        p++; s++;
    }
    return 0;
}

int
make_ab(double *a, double *b, line L0, line L)
{
    *a = double(L0.dx() * L.dx() + L0.dy() * L.dy()) / double(L0.dx() * L0.dx() + L0.dy() * L0.dy());
    *b = double(L0.dx() * L.dy() - L0.dy() * L.dx()) / double(L0.dx() * L0.dx() + L0.dy() * L0.dy());
    return 0;
}

int
insert_line(point in0, line in, point out0, line *out, double a, double b)
{
    out->P1 = out0 + rotate_point(in.P1 - in0, a, b);
    out->P2 = out0 + rotate_point(in.P2 - in0, a, b);
    return 0;
}

point
rotate_point(point V0, double a, double b)
{
    point V;
    V.x = a * V0.x - b * V0.y;
    V.y = b * V0.x + a * V0.y;
    return V;
}

int
draw_fractal(fractal F, sdl_complex H, fr_state f_st)
{
    draw(F.lines, H, f_st.fr_col);
    return 0;
}

int
check_fractal_size(fractal F, int width, int height)
{
    line *p = F.lines.val, *pend = F.lines.val + F.lines.siz;
    while (p < pend) {
        if (check_point_dist(p->P1, width, height)) return 1;
        if (check_point_dist(p->P2, width, height)) return 1;
        p++;
    }
    return 0;
}

int
check_point_dist(point P, int width, int height)
{
    if (P.x > (fr_limit_size_k + 1) * width ) return 1;
    if (P.x < - fr_limit_size_k * width ) return 1;
    if (P.y > (fr_limit_size_k + 1) * height ) return 1;
    if (P.y < - fr_limit_size_k * height ) return 1;
    return 0;
}

//---------------------------------------------

point
get_cur_point(SDL_Event e, fr_state f_st)
{
    if (f_st.grid) {
        int x = round(double(e.button.x) / double(fr_pitch)) * fr_pitch;
        int y = round(double(e.button.y) / double(fr_pitch)) * fr_pitch;
        return make_point(x, y);
    } else {
        return make_point(e.button.x, e.button.y);
    }
}
