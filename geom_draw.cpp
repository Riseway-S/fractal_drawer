rgb_color
make_rgb_color(Uint8 r, Uint8 g, Uint8 b, Uint8 t)
{
    rgb_color col;
    col.r = r; col.g = g; col.b = b; col.t = t;
    return col;
}

int
set_color(sdl_complex H, rgb_color col)
{
    SDL_SetRenderDrawColor(H.renderer, col.r, col.g, col.b, col.t);
}

int
draw(point P, sdl_complex H, rgb_color col)
{
    set_color(H, col);
    SDL_RenderDrawPoint(H.renderer, P.x, P.y);
    return 0;
}

int
draw(line L, sdl_complex H, rgb_color col)
{
    set_color(H, col);;
    SDL_RenderDrawLine(H.renderer, L.P1.x, L.P1.y, L.P2.x, L.P2.y);
    return 0;
}

//int
//draw_vec(line L, sdl_complex H)
//{
//    SDL_SetRenderDrawColor(H.renderer, fr_kerncolor);
//    SDL_RenderDrawLine(H.renderer, L.P1.x, L.P1.y, L.P2.x, L.P2.y);
//    return 0;
//}

int
draw(vec<line> L, sdl_complex H, rgb_color col)
{
    set_color(H, col);
    line *p = L.val, *pend = L.val + L.siz;
    while (p < pend) {
        SDL_RenderDrawLine(H.renderer, p->P1.x, p->P1.y, p->P2.x, p->P2.y);
        p++;
    }
    return 0;
}
