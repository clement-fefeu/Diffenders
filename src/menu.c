#include "../lib/fonc.h"
#include "../lib/base_struct.h"

//
//  menu.c
//
//  Created by Gabriel Dubois.
/**
 *  \file menu.c
 * \brief Programme principal
 * \details Programme qui utilise les fonctions qui permettent l'affichage des menus.
 * \author Gabriel Dubois
*/

int menu()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *quit = NULL,*play = NULL,*background = NULL,*quit_des = NULL,*play_des = NULL,*parametre=NULL,*parametre_des=NULL;
    SDL_Event event;
    SDL_bool isOpen = SDL_TRUE;
    Uint32 boutons;
    SDL_Rect pos_quit,pos_play,pos_param;
    int statut = EXIT_FAILURE;
    /* Initialisation simple */
    printf("\n1\n");
    init(&window,&renderer,WIDTHSCREEN,HEIGHTSCREEN);
    printf("\n2\n");
    init_icon(window);
    int largeur=WIDTHSCREEN,hauteur=HEIGHTSCREEN;

    loadImage("../img/tower_def.jpg",renderer,&background);
    loadImage("../img/jouer_m.png",renderer,&play);
    loadImage("../img/quitter_m.png",renderer,&quit);
    loadImage("../img/jouer_g.png",renderer,&play_des);
    loadImage("../img/quitter_g.png",renderer,&quit_des);
    loadImage("../img/parametre.png",renderer,&parametre);
    loadImage("../img/parametre_g.png",renderer,&parametre_des);

    SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
    pos_quit.x = largeur /2 - pos_quit.w /2;
    pos_quit.y = hauteur /2 - pos_quit.h /2;
    SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
    pos_play.x = largeur /2 - pos_play.w /2;
    pos_play.y = pos_quit.y-140;
    SDL_QueryTexture(parametre, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
    pos_param.x = largeur /2 - pos_param.w /2;
    pos_param.y = pos_quit.y-70;

    accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
    while (isOpen)
    {
        while(SDL_PollEvent(&event)){
        
            
            switch (event.type)
            {
                case SDL_QUIT:
                    isOpen = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_Log("%d %d",event.button.x,event.button.y);
                    if((event.button.x>=pos_quit.x && event.button.x<=pos_quit.x+pos_quit.w) && (event.button.y>=pos_quit.y && event.button.y<=pos_quit.y+pos_quit.h)){
                        isOpen = SDL_FALSE;
                    }
                    else if((event.button.x>=pos_play.x && event.button.x<=pos_play.x+pos_play.w) && (event.button.y>=pos_play.y && event.button.y<=pos_play.y+pos_play.h)){
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        jeu(renderer,window);
                        
                        SDL_GetWindowSize(window,&largeur,&hauteur);
                        SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
                        pos_quit.x = largeur /2 - pos_quit.w /2;
                        pos_quit.y = hauteur /2 - pos_quit.h /2;
                        SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
                        pos_play.x = largeur /2 - pos_play.w /2;
                        pos_play.y = pos_quit.y-140;
                        SDL_QueryTexture(parametre, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
                        pos_param.x = largeur /2 - pos_param.w /2;
                        pos_param.y = pos_quit.y-70;
                        accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
                    }
                    else if((event.button.x>=pos_param.x && event.button.x<=pos_param.x+pos_param.w) && (event.button.y>=pos_param.y && event.button.y<=pos_param.y+pos_param.h)){
                        SDL_Log("PARAMETRE");
                        switch(param(renderer,window,largeur,hauteur,background)){
                            case 0:isOpen=SDL_FALSE;break;
                            case 2:SDL_GetWindowSize(window,&largeur,&hauteur);break;
                            case 1:
                            largeur=WIDTHSCREEN;
                            hauteur=HEIGHTSCREEN;
                            break;
                        }
                        SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
                        pos_quit.x = largeur /2 - pos_quit.w /2;
                        pos_quit.y = hauteur /2 - pos_quit.h /2;
                        SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
                        pos_play.x = largeur /2 - pos_play.w /2;
                        pos_play.y = pos_quit.y-140;
                        SDL_QueryTexture(parametre, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
                        pos_param.x = largeur /2 - pos_param.w /2;
                        pos_param.y = pos_quit.y-70;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if((event.button.x>=pos_quit.x && event.button.x<=pos_quit.x+pos_quit.w) && (event.button.y>=pos_quit.y && event.button.y<=pos_quit.y+pos_quit.h)){
                        accueil(renderer,1,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
                    }
                    else if((event.button.x>=pos_play.x && event.button.x<=pos_play.x+pos_play.w) && (event.button.y>=pos_play.y && event.button.y<=pos_play.y+pos_play.h)){
                        accueil(renderer,2,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
                    }
                    else if((event.button.x>=pos_param.x && event.button.x<=pos_param.x+pos_param.w) && (event.button.y>=pos_param.y && event.button.y<=pos_param.y+pos_param.h)){
                        accueil(renderer,3,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
                    }
                    else{
                        accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
                    }
                break;
                
                
            }

        }
            
        
    }
    

    statut = EXIT_SUCCESS;
    
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(quit);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(play_des);
    SDL_DestroyTexture(quit_des);
    SDL_DestroyTexture(parametre);
    SDL_DestroyTexture(parametre_des);
    SDL_DestroyTexture(background);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return statut;
}