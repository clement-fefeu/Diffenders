#include "fonc.h"

int main(int argc, char** argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *mots = NULL,*background = NULL;
    SDL_PixelFormat *format;
    SDL_Event event;
    SDL_bool isOpen = SDL_TRUE;
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color gris = {255, 255, 255, 150};
    struct Input in;
    Uint8 *clavier;
    Uint32 boutons;
    SDL_Rect position;
    int statut = EXIT_FAILURE;
    /* Initialisation simple */
    init(&window,&renderer,1024,768);
    init_icon(window);

    background=loadImage("../img/lane.png",renderer);

    while (isOpen)
    {
         while (SDL_PollEvent(&event))
        {
            
            switch (event.type)
            {
                case SDL_QUIT:
                    isOpen = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_Log("%d %d",event.button.x,event.button.y);
                    if((event.button.x>=470 && event.button.x<=570) && (event.button.y>=370 && event.button.y<=410)){
                        isOpen = SDL_FALSE;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if((event.button.x>=488 && event.button.x<=540) && (event.button.y>=375 && event.button.y<=400)){
                        cree_mots(renderer,gris,"Quick_Peach.ttf","Quit");
                        afficher(renderer,background);
                    }
                    else{
                        cree_mots(renderer,blanc,"Quick_Peach.ttf","Quit");
                        afficher(renderer,background);
                }
                break;
                
                
            }
            

            
        }
    }
    

    statut = EXIT_SUCCESS;
Quit:
    if(NULL != mots)
        SDL_DestroyTexture(mots);
    if(NULL != background)
        SDL_DestroyTexture(mots);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return statut;
}