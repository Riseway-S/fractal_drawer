struct rgb_color
{
    Uint8 r = 0x00;
    Uint8 g = 0x00;
    Uint8 b = 0x00;
    Uint8 t = 0xFF;
};

rgb_color
make_rgb_color(Uint8 r, Uint8 g, Uint8 b, Uint8 t);

int
set_color(sdl_complex H, rgb_color col);

int
draw(point P, sdl_complex H, rgb_color col);

int
draw(line L, sdl_complex H, rgb_color col);

//int
//draw_vec(line L, sdl_complex H, rgb_color col);

int
draw(vec<line> L, sdl_complex H, rgb_color col);


