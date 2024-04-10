#include "../lib/fonc.h"
#include "../lib/base_struct.h"


#define WIDTHSCREEN 1600 

#define HEIGHTSCREEN 900 

#define TOTAL_POINTS 5000 

void accueil(SDL_Renderer *renderer,int gris,SDL_Texture *quit ,SDL_Texture *play ,SDL_Texture*background,SDL_Texture*quit_des,SDL_Texture*play_des,SDL_Texture*parametre,SDL_Texture*parametre_des){
    SDL_Rect position;
    int position_X,position_Y,position_X_Play,position_Y_Play,position_X_param,position_Y_param;

    switch(gris){
        case 0:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = HEIGHTSCREEN /2 - position.h /2;
            position_X=position.x;
            position_Y=position.y;
            SDL_RenderCopy(renderer, quit, NULL, &position);

            SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-150;
            position_X_Play=position.x;
            position_Y_Play=position.y;
            SDL_RenderCopy(renderer, play, NULL, &position);

            SDL_QueryTexture(parametre, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-70;
            position_X_param=position.x;
            position_Y_param=position.y;
            SDL_RenderCopy(renderer, parametre, NULL, &position);

            SDL_RenderPresent(renderer);
            break;
        case 1:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit_des, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = HEIGHTSCREEN /2 - position.h /2;
            position_X=position.x;
            position_Y=position.y;
            SDL_RenderCopy(renderer, quit_des, NULL, &position);

            SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-150;
            position_X_Play=position.x;
            position_Y_Play=position.y;
            SDL_RenderCopy(renderer, play, NULL, &position);

            SDL_QueryTexture(parametre, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-70;
            position_X_param=position.x;
            position_Y_param=position.y;
            SDL_RenderCopy(renderer, parametre, NULL, &position);

            SDL_RenderPresent(renderer);
            break;
        case 2:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = HEIGHTSCREEN /2 - position.h /2;
            position_X=position.x;
            position_Y=position.y;
            SDL_RenderCopy(renderer, quit, NULL, &position);

            SDL_QueryTexture(play_des, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-150;
            position_X_Play=position.x;
            position_Y_Play=position.y;
            SDL_RenderCopy(renderer, play_des, NULL, &position);

            SDL_QueryTexture(parametre, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-70;
            position_X_param=position.x;
            position_Y_param=position.y;
            SDL_RenderCopy(renderer, parametre, NULL, &position);

            SDL_RenderPresent(renderer);
            break;
        case 3:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = HEIGHTSCREEN /2 - position.h /2;
            position_X=position.x;
            position_Y=position.y;
            SDL_RenderCopy(renderer, quit, NULL, &position);

            SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-150;
            position_X_Play=position.x;
            position_Y_Play=position.y;
            SDL_RenderCopy(renderer, play, NULL, &position);

            SDL_QueryTexture(parametre_des, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
            position.x = WIDTHSCREEN /2 - position.w /2;
            position.y = position_Y-70;
            position_X_param=position.x;
            position_Y_param=position.y;
            SDL_RenderCopy(renderer, parametre_des, NULL, &position);

            SDL_RenderPresent(renderer);
            break;

    }
        
}
/*
void param(SDL_Renderer *renderer){
    SDL_Rect position;
    SDL_bool isOpen = SDL_TRUE;
    SDL_Event event;
    SDL_Texture *fenetrer = NULL,*fenetrer_des = NULL,*Full = NULL,*Full_des = NULL,*fenetrer_sb = NULL,*fenetrer_sb_des=NULL,*croix=NULL;
    
    fenetrer=loadImage("../img/fenetrer.png",renderer);
    fenetrer_des=loadImage("../img/fenetrer_des.png",renderer);
    Full=loadImage("../img/full_screen.png",renderer);
    Full_des=loadImage("../img/full_screen_des.png",renderer);
    fenetrer_sb=loadImage("../img/fenetrer_sb.png",renderer);
    fenetrer_sb_des=loadImage("../img/fenetrer_sb_des.png",renderer);
    croix=loadImage("../img/croix.png",renderer);

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
                    break;
                case SDL_MOUSEMOTION:
                break;
                
                
            }
            
        }
    }

    SDL_DestroyTexture(fenetrer);
    SDL_DestroyTexture(fenetrer_des);
    SDL_DestroyTexture(Full);
    SDL_DestroyTexture(Full_des);
    SDL_DestroyTexture(fenetrer_sb);
    SDL_DestroyTexture(fenetrer_sb_des);
}
*/

/* modifier zone à cliquer et positionner les bouton */
int menu()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *quit = NULL,*play = NULL,*background = NULL,*quit_des = NULL,*play_des = NULL,*parametre=NULL,*parametre_des=NULL;
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
    int position_X,position_Y,position_Y_Play,position_Y_param;
    /* Initialisation simple */
    init(&window,&renderer,WIDTHSCREEN,HEIGHTSCREEN);
    init_icon(window);

    background=loadImage("../img/tower_def.jpg",renderer);
    play=loadImage("../img/start_maron.jpg",renderer);
    quit=loadImage("../img/quit_maron.jpg",renderer);
    play_des=loadImage("../img/start_gris.jpg",renderer);
    quit_des=loadImage("../img/quit.jpg",renderer);
    parametre=loadImage("../img/parametre.png",renderer);
    parametre_des=loadImage("../img/param_des.png",renderer);

    SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN /2 - position.w /2;
    position.y = HEIGHTSCREEN /2 - position.h /2;
    position_X=position.x;
    position_Y=position.y;
    SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN /2 - position.w /2;
    position.y = position_Y-150;
    position_Y_Play=position.y; 
    SDL_QueryTexture(parametre, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN /2 - position.w /2;
    position.y = position_Y-70;
    position_Y_param=position.y;

    accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des);
    printf("%d\n",position_X);
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
                    if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y && event.button.y<=position_Y+35)){
                        isOpen = SDL_FALSE;
                    }
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_Play && event.button.y<=position_Y_Play+35)){
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        jeu(renderer);

                        accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des);
                    }
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_param && event.button.y<=position_Y_param+35)){

                    }
                    break;
                case SDL_MOUSEMOTION:
                    if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y && event.button.y<=position_Y+35)){
                        accueil(renderer,1,quit,play,background,quit_des,play_des,parametre,parametre_des);
                    }
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_Play && event.button.y<=position_Y_Play+35)){
                        accueil(renderer,2,quit,play,background,quit_des,play_des,parametre,parametre_des);
                    }
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_param && event.button.y<=position_Y_param+35)){
                        accueil(renderer,3,quit,play,background,quit_des,play_des,parametre,parametre_des);
                    }
                    else{
                        accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des);
                    }
                break;
                
                
            }
            
        }
    }
    

    statut = EXIT_SUCCESS;
Quit:
    SDL_DestroyTexture(quit);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(play_des);
    SDL_DestroyTexture(quit_des);
    SDL_DestroyTexture(parametre);
    SDL_DestroyTexture(parametre_des);
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