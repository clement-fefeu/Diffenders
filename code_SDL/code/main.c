#include "fonc.h"

int main(int argc, char** argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_PixelFormat *format;
    SDL_Event event;
    SDL_bool isOpen = SDL_TRUE;
    SDL_Color blanc = {255, 255, 255, 255};
    struct Input in;
    Uint8 *clavier;
    Uint32 boutons;
    SDL_Rect position;
    int statut = EXIT_FAILURE;
    /* Initialisation simple */
    init(&window,&renderer,1024,768);
    init_icon(window);

    aff_mots(renderer,blanc,"Quick_Peach.ttf","ui");

    

    statut = EXIT_SUCCESS;
Quit:
    if(NULL != texture)
        SDL_DestroyTexture(texture);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return statut;
}