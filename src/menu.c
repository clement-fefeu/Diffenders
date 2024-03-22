#include "../lib/fonc.h"
#include "../lib/base_struct.h"


#define WIDTHSCREEN 1600 

#define HEIGHTSCREEN 900 

#define TOTAL_POINTS 5000 


/* modifier zone à cliquer et positionner les bouton */
int menu()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *quit = NULL,*play = NULL,*background = NULL,*quit_des = NULL,*play_des = NULL;
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
    init(&window,&renderer,WIDTHSCREEN,HEIGHTSCREEN);
    init_icon(window);

    background=loadImage("../img/tower_def.jpg",renderer);
    play=loadImage("../img/start_maron.jpg",renderer);
    quit=loadImage("../img/quit_maron.jpg",renderer);
    play_des=loadImage("../img/start_gris.jpg",renderer);
    quit_des=loadImage("../img/quit.jpg",renderer);

    SDL_RenderCopy(renderer, background, NULL, NULL );

    SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN / 2- position.w /2;
    position.y = HEIGHTSCREEN / 2 - position.h /2;
    SDL_RenderCopy(renderer, play, NULL, &position);

    SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN /2 - position.w /2;
    position.y = HEIGHTSCREEN /2 - position.h /2;
    SDL_RenderCopy(renderer, quit, NULL, &position);

    SDL_RenderPresent(renderer);
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
                    else if((event.button.x>=470 && event.button.x<=570) && (event.button.y>=285 && event.button.y<=315)){
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        jeu(renderer);

                        SDL_RenderCopy(renderer, background, NULL, NULL );

                        SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN / 2- position.w /2;
                        position.y = HEIGHTSCREEN / 2 - position.h /2;
                        SDL_RenderCopy(renderer, play, NULL, &position);

                        SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN /2 - position.w /2;
                        position.y = HEIGHTSCREEN /2 - position.h /2;
                        SDL_RenderCopy(renderer, quit, NULL, &position);

                        SDL_RenderPresent(renderer);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if((event.button.x>=470 && event.button.x<=570) && (event.button.y>=370 && event.button.y<=410)){
                        SDL_RenderCopy(renderer, background, NULL, NULL );
                        SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN / 2- position.w /2;
                        position.y = HEIGHTSCREEN / 2 - position.h /2;
                        SDL_RenderCopy(renderer, play, NULL, &position);

                        SDL_QueryTexture(quit_des, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN /2 - position.w /2;
                        position.y = HEIGHTSCREEN /2 - position.h /2;
                        SDL_RenderCopy(renderer, quit_des, NULL, &position);
                        
                        SDL_RenderPresent(renderer);
                    }
                    else if((event.button.x>=470 && event.button.x<=570) && (event.button.y>=285 && event.button.y<=315)){
                        SDL_RenderCopy(renderer, background, NULL, NULL );
                        SDL_QueryTexture(play_des, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN / 2- position.w /2;
                        position.y = HEIGHTSCREEN / 2 - position.h /2;
                        SDL_RenderCopy(renderer, play_des, NULL, &position);

                        SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN /2 - position.w /2;
                        position.y = HEIGHTSCREEN /2 - position.h /2;
                        SDL_RenderCopy(renderer, quit, NULL, &position);
                        
                        SDL_RenderPresent(renderer);
                    }
                    else{
                        SDL_RenderCopy(renderer, background, NULL, NULL );

                        SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN / 2- position.w /2;
                        position.y = HEIGHTSCREEN / 2 - position.h /2;
                        SDL_RenderCopy(renderer, play, NULL, &position);

                        SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
                        position.x = WIDTHSCREEN /2 - position.w /2;
                        position.y = HEIGHTSCREEN /2 - position.h /2;
                        SDL_RenderCopy(renderer, quit, NULL, &position);

                        SDL_RenderPresent(renderer);
                    }
                break;
                
                
            }
            
        }
    }
    

    statut = EXIT_SUCCESS;
Quit:
    if(NULL != play)
        SDL_DestroyTexture(play);
    if(NULL != quit)
        SDL_DestroyTexture(quit);
    if(NULL != background)
        SDL_DestroyTexture(background);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return statut;
}