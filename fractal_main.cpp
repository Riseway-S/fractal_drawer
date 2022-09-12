#include <SDL.h>
#include <stdio.h>
#include <math.h>

#include "fractal_config.h"

int debug_alloc_memory = 0;

#include "vectors.h"
#include "geometry.h"
#include "window_work.h"
#include "geom_draw.h"
#include "fractal_drawer2.h"
#include "fractal_interface.h"


#include "vectors.cpp"
#include "geometry.cpp"
#include "window_work.cpp"
#include "geom_draw.cpp"
#include "fractal_drawer2.cpp"
#include "fractal_interface.cpp"




int
cycle(sdl_complex *H)
{
    fractal F = init_fractal();
    frac_root S = init_frac_root();
	SDL_Event e;
    fr_state f_st;
    int run = -1;
	while (run) {
		while (!!SDL_PollEvent(&e)) {
            quit_monitor(&run, e);
            window_change(e, H);
            mode_switcher(&f_st, e, &S, &F, *H);
            switch (f_st.mode) {
                case fr_mode_editseq:
                    seqedit_frac_root(&f_st, e, &S, *H);
                    break;
                case fr_mode_editker:
                    kernedit_frac_root(&f_st, e, &S, *H);
                    break;
                case fr_mode_fractal:
                    make_fractal(&f_st, e, S, &F, *H);
                    break;
                default:
                    break;
            }
		}
		SDL_RenderPresent(H->renderer);
	}
	free(F); free(S);
	return 0;
}

int
main( int argc, char* args[] )
{
	int r_init = 0, r_cycle = 0, r_end = 0;
	sdl_complex H = make_sdl_complex();
	if ((r_init = init(&H, "fractal v2.1")) < 0) {
		fprintf(stderr, "error: main: init() < 0; r_init = %i\n", r_init);
		return 1;
	} else if ((r_cycle = cycle(&H)) < 0) {
		fprintf(stderr, "error: main: cycle() < 0; r_cycle = %i\n", r_cycle);
		return 2;
	} else if ((r_end = close_all(&H)) < 0) {
		fprintf(stderr, "error: main: close_all() < 0; r_end = %i\n", r_end);
		return 3;
	}
    //printf("memory leaks (bytes): %d\n", debug_alloc_memory);
	return 0;
}

