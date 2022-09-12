struct sdl_complex{
    SDL_Window *window;
    int height;
    int width;
    SDL_Renderer *renderer;
};

sdl_complex
make_sdl_complex();

int
init(sdl_complex *H, const char name[]);

int
close_all(sdl_complex *H);

int
reset_screen(sdl_complex H);

int
window_change(SDL_Event e, sdl_complex *H);

int
quit_monitor(int *run, SDL_Event e);