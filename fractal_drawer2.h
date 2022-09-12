//-------------------------------------------------------
#define fr_mode_fractal 0
#define fr_mode_editseq 1
#define fr_mode_editker 2
struct fr_state
{
    int mode = fr_mode_editseq; // fr_mode_fractal, fr_mode_editseq, fr_mode_editker
    int linebegin = 0; //1, 0
    int manualkernel = 0; //1, 0
    int grid = 0; //1, 0
    point act_p;
    rgb_color fr_col = make_rgb_color(fr_color);
    rgb_color kern_col = make_rgb_color(fr_kerncolor);
};

//-------------------------------------------------------
struct fractal
{
    vec<line> lines;
    int siz() {return lines.siz;}
};

struct frac_root
{
    vec<line> lines;
    line kern = make_line(0,0,0,0);
    int siz() {return lines.siz;}
};

fractal
init_fractal();

fractal
init_fractal(int N);

int
resize_fractal(fractal *F, int N);

int
free(fractal F);

frac_root
init_frac_root();

frac_root
init_frac_root(int N);

int
resize_frac_root(frac_root *S, int N);

int
free(frac_root S);

int
disp(fractal F);

//--------------------------------------------------

int
add_line(frac_root *S, line L);

int
cancel_last_point(fr_state *f_st, frac_root *S);

int
finalize_root(frac_root *S);

int
draw_frac_root(frac_root S, sdl_complex H, fr_state f_st);

//--------------------------------------------------

int
start_fractal(frac_root S, fractal *F);

int
add_fractal_layer(frac_root Sample, fractal *F, int width, int height);

fractal
add_fractal_layer(frac_root Sample, fractal F0);

int
insert_segment(frac_root Sample, line L0, line *L);

int
make_ab(double *a, double *b, line L0, line L);

int
insert_line(point in0, line in, point out0, line *out, double a, double b);

point
rotate_point(point V0, double a, double b);

int
draw_fractal(fractal F, sdl_complex H, fr_state f_st);

int
check_fractal_size(fractal F, int width, int height);

int
check_point_dist(point P, int width, int height);

//--------------------------------------------------

point
get_cur_point(SDL_Event e, fr_state f_st);
