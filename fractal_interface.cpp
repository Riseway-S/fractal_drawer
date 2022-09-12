int
mode_switcher(fr_state *f_st, SDL_Event e, frac_root *S, fractal *F, sdl_complex  H)
{

    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case fr_but_seqmode:
                f_st->mode = fr_mode_editseq;
                f_st->linebegin = 0;
                resize_fractal(F, 0);
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
                break;
            case fr_but_kernel:
                f_st->mode = fr_mode_editker;
                f_st->linebegin = 0;
                f_st->manualkernel = 1;
                resize_fractal(F, 0);
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
                break;
            case fr_but_fractal:
                if (f_st->mode != fr_mode_fractal) {
                    f_st->mode = fr_mode_fractal;
                    start_fractal(*S, F);
                    reset_screen(H);
                    draw_fractal(*F, H, *f_st);
                }
                break;
            case fr_but_grid:
                if (f_st->grid) {
                    f_st->grid = 0;
                    printf("grid off\n");
                } else {
                    f_st->grid = 1;
                    printf("grid on\n");
                }
                break;
            default:
                break;
        }
    }
    return 0;
}

int
seqedit_frac_root(fr_state *f_st, SDL_Event e, frac_root *S, sdl_complex H)
{
    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (f_st->linebegin) {
                add_line(S, make_line(f_st->act_p, get_cur_point(e, *f_st)));
                f_st->act_p = get_cur_point(e, *f_st);
                if (!(f_st->manualkernel)) finalize_root(S);
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            } else {
                f_st->act_p = get_cur_point(e, *f_st);
                f_st->linebegin = 1;
                draw(f_st->act_p, H, f_st->fr_col);
            }
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == fr_but_cancel) {
                cancel_last_point(f_st, S);
                if (!(f_st->manualkernel)) finalize_root(S);
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
                if (f_st->linebegin) draw(f_st->act_p, H, f_st->fr_col);
            }
            if (e.key.keysym.sym == fr_but_finkern) {
                finalize_root(S);
                f_st->manualkernel = 0;
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            }
            if (e.key.keysym.sym == fr_but_refresh) {
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            }
            break;
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            }
            break;
        default:
            break;
    }
    return 0;
}

int
kernedit_frac_root(fr_state *f_st, SDL_Event e, frac_root *S, sdl_complex H)
{
    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (f_st->linebegin) {
                S->kern = make_line(f_st->act_p, get_cur_point(e, *f_st));
                f_st->linebegin = 0;
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            } else {
                f_st->act_p = get_cur_point(e, *f_st);
                f_st->linebegin = 1;
                draw(f_st->act_p, H, f_st->fr_col);
            }
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == fr_but_cancel) {
                f_st->linebegin = 1;
                f_st->act_p = S->kern.P1;
            }
            if (e.key.keysym.sym == fr_but_finkern) {
                finalize_root(S);
                f_st->manualkernel = 0;
                f_st->linebegin = 0;
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            }
            if (e.key.keysym.sym == fr_but_refresh) {
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            }
            break;
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                reset_screen(H);
                draw_frac_root(*S, H, *f_st);
            }
            break;
        default:
            break;
    }
    return 0;
}

int
make_fractal(fr_state *f_st, SDL_Event e, frac_root S, fractal *F, sdl_complex H)
{
    switch (e.type) {
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == fr_but_fractal) {
                int a = add_fractal_layer(S, F, H.width, H.height);
                if (a == -1) {
                    printf("enough\n");
                } else if (a == -2) {
                    printf("out of the screen\n");
                } else if (a == 1) {
                    reset_screen(H);
                    draw_fractal(*F, H, *f_st);
                }
            }
            if (e.key.keysym.sym == fr_but_refresh) {
                reset_screen(H);
                draw_fractal(*F, H, *f_st);
            }
            break;
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                reset_screen(H);
                draw_fractal(*F, H, *f_st);
            }
            break;
        default:
            break;
    }
    return 0;
}
