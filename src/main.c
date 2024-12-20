#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WINDOW_FLAGS (SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY)

/* We will use this renderer to draw into this window every frame. */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} AppState;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    *appstate = malloc(sizeof(AppState));
    AppState *app = *appstate;

    SDL_SetAppMetadata("Example HUMAN READABLE NAME", "1.0", "com.example.CATEGORY-NAME");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());

        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/CATEGORY/NAME", 640, 480, WINDOW_FLAGS, &app->window, &app->renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent([[maybe_unused]] void *appstate, SDL_Event *event)
{
    switch (event->type) {
        case SDL_EVENT_QUIT: return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
        default: return SDL_APP_CONTINUE;  /* carry on with the program! */
    }
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate([[maybe_unused]] void *appstate)
{
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    AppState *app = appstate;

    free(app);
}