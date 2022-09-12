sdl_complex
make_sdl_complex()
{
    sdl_complex H;
    H.window = NULL;
    H.renderer = NULL;
    H.height = HEIGHT_DEFAULT;
    H.width = WIDTH_DEFAULT;
    return H;
}

//SDL_Window *window = NULL;
//int height = HEIGHT_DEFAULT;
//int width = WIDTH_DEFAULT;
//SDL_Renderer *renderer = NULL;


int
init(sdl_complex *H, const char name[])
{
	int r_SDL_Init = 0;

	if ((r_SDL_Init = SDL_Init(SDL_INIT_FLAGS)) < 0) {
		fprintf(stderr, "error: init: SDL_Init() < 0; r_SDL_Init = %i\n", r_SDL_Init);
		return -1;
	} else if (!((*H).window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (*H).width, (*H).height, SDL_WINDOW_FLAGS))) {
		fprintf(stderr, "error: init: SDL_CreateWindow() == NULL\n");
		return -2;
	} else if (!((*H).renderer = SDL_CreateRenderer((*H).window, -1, SDL_RENDERER_FLAGS))) {
		fprintf(stderr, "error: init: SDL_CreateRenderer() == NULL\n");
		return -3;
	} else {
		SDL_SetRenderDrawColor((*H).renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear((*H).renderer);
	}
	return 0;
}

int
close_all(sdl_complex *H)
{
	if ((*H).renderer) {
		SDL_DestroyRenderer((*H).renderer);
		(*H).renderer = NULL;
	}
	if ((*H).window) {
		SDL_DestroyWindow((*H).window);
		(*H).window = NULL;
	}
	SDL_Quit();
	return 0;
}

int
reset_screen(sdl_complex H)
{
    SDL_SetRenderDrawColor(H.renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(H.renderer);
    return 0;
}

int
window_change(SDL_Event e, sdl_complex *H)
{
    if (e.type == SDL_WINDOWEVENT) {
        if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            int w = 0, h = 0;
            SDL_GetWindowSize(H->window, &w, &h);
            H->width = w;
            H->height = h;
        }
    }
    return 0;
}

int
quit_monitor(int *run, SDL_Event e){
    switch (e.type) {
        case SDL_QUIT:
            *run = 0;
			break;
       	case SDL_KEYDOWN:
       	    if (e.key.keysym.sym == SDLK_q) *run = 0;
        default:
            break;
    }
    return 0;
}
