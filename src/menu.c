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

 /**
 * @brief Affiche l'écran d'accueil avec les différents boutons.
 *
 * Affiche les boutons de jeu, de paramètres et de quitter sur l'écran d'accueil.
 *
 * @param[in] renderer Le renderer SDL pour afficher les textures.
 * @param[in] gris L'état des boutons : 0 pour normal, 1 pour grisés, 2 pour jouer en surbrillance, 3 pour paramètres en surbrillance.
 * @param[in] quit La texture du bouton quitter.
 * @param[in] play La texture du bouton jouer.
 * @param[in] background La texture de l'arrière-plan.
 * @param[in] quit_des La texture du bouton quitter en surbrillance.
 * @param[in] play_des La texture du bouton jouer en surbrillance.
 * @param[in] parametre La texture du bouton paramètres.
 * @param[in] parametre_des La texture du bouton paramètres en surbrillance.
 * @param[in] largeur La largeur de la fenêtre.
 * @param[in] hauteur La hauteur de la fenêtre.
 */

void accueil(SDL_Renderer *renderer,int gris,SDL_Texture *quit ,SDL_Texture *play ,SDL_Texture*background,SDL_Texture*quit_des,SDL_Texture*play_des,SDL_Texture*parametre,SDL_Texture*parametre_des,int largeur, int hauteur){
    SDL_Rect pos_quit,pos_play,pos_param;;


    switch(gris){
        case 0:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
            pos_quit.x = largeur /2 - pos_quit.w /2;
            pos_quit.y = hauteur /2 - pos_quit.h /2;
            SDL_RenderCopy(renderer, quit, NULL, &pos_quit);

            SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
            pos_play.x = largeur /2 - pos_play.w /2;
            pos_play.y = pos_quit.y-140;
            SDL_RenderCopy(renderer, play, NULL, &pos_play);

            SDL_QueryTexture(parametre, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
            pos_param.x = largeur /2 - pos_param.w /2;
            pos_param.y = pos_quit.y-70;
            SDL_RenderCopy(renderer, parametre, NULL, &pos_param);

            SDL_RenderPresent(renderer);
            break;
        case 1:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit_des, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
            pos_quit.x = largeur /2 - pos_quit.w /2;
            pos_quit.y = hauteur /2 - pos_quit.h /2;
            SDL_RenderCopy(renderer, quit_des, NULL, &pos_quit);

            SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
            pos_play.x = largeur /2 - pos_play.w /2;
            pos_play.y = pos_quit.y-140;
            SDL_RenderCopy(renderer, play, NULL, &pos_play);

            SDL_QueryTexture(parametre, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
            pos_param.x = largeur /2 - pos_param.w /2;
            pos_param.y = pos_quit.y-70;
            SDL_RenderCopy(renderer, parametre, NULL, &pos_param);

            SDL_RenderPresent(renderer);
            break;
        case 2:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
            pos_quit.x = largeur /2 - pos_quit.w /2;
            pos_quit.y = hauteur /2 - pos_quit.h /2;
            SDL_RenderCopy(renderer, quit, NULL, &pos_quit);

            SDL_QueryTexture(play_des, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
            pos_play.x = largeur /2 - pos_play.w /2;
            pos_play.y = pos_quit.y-140;
            SDL_RenderCopy(renderer, play_des, NULL, &pos_play);

            SDL_QueryTexture(parametre, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
            pos_param.x = largeur /2 - pos_param.w /2;
            pos_param.y = pos_quit.y-70;
            SDL_RenderCopy(renderer, parametre, NULL, &pos_param);

            SDL_RenderPresent(renderer);
            break;
        case 3:
            SDL_RenderCopy(renderer, background, NULL, NULL );
            SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
            pos_quit.x = largeur /2 - pos_quit.w /2;
            pos_quit.y = hauteur /2 - pos_quit.h /2;
            SDL_RenderCopy(renderer, quit, NULL, &pos_quit);

            SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
            pos_play.x = largeur /2 - pos_play.w /2;
            pos_play.y = pos_quit.y-140;
            SDL_RenderCopy(renderer, play, NULL, &pos_play);

            SDL_QueryTexture(parametre_des, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
            pos_param.x = largeur /2 - pos_param.w /2;
            pos_param.y = pos_quit.y-70;
            SDL_RenderCopy(renderer, parametre_des, NULL, &pos_param);

            SDL_RenderPresent(renderer);
            break;

    }
        
}


/**
 * @brief Affiche le menu des paramètres.
 *
 * Affiche les options de paramètres comme le plein écran, la fenêtre et le retour.
 *
 * @param[in] renderer Le renderer SDL pour afficher les textures.
 * @param[in] window La fenêtre SDL pour les modifications de fenêtre.
 * @param[in] largeur La largeur de la fenêtre.
 * @param[in] hauteur La hauteur de la fenêtre.
 * @param[in] background La texture de l'arrière-plan.
 * @return 1 pour fenêtré, 2 pour plein écran, 0 pour quitter.
 */
int param(SDL_Renderer *renderer,SDL_Window *window,int largeur, int hauteur,SDL_Texture *background){
	SDL_Event event;
	SDL_bool isOpen=SDL_TRUE;
	SDL_Texture *menu=NULL,*full = NULL,*retour = NULL,*quitter=NULL,*fenetrer=NULL;
	SDL_Rect RectParam,position;
    SDL_bool fullscreen=SDL_FALSE;
    int grand=1;
// load sample.png into image (fenetre de pause)
	loadImage("../img/menu.png",renderer,&menu);
// load sample.png into image (quitter)
	loadImage("../img/retour_b.png",renderer,&retour);
// load sample.png into image (retour)
	loadImage("../img/quitter_b.png",renderer,&quitter);
// load sample.png into image (plein ecran)
	loadImage("../img/plein_ecran_b.png",renderer,&full);
// load sample.png into image (fenetrer)
	loadImage("../img/fenetrer_b.png",renderer,&fenetrer);


    SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, background,NULL, NULL);
    SDL_QueryTexture(menu,NULL,NULL,&RectParam.w,&RectParam.h);
	RectParam.x = largeur /2 - RectParam.w /2;
	RectParam.y = hauteur /2 - RectParam.h /2;
	SDL_RenderCopy(renderer, menu,NULL, &RectParam);
	SDL_RenderPresent(renderer);
	while(isOpen){

		while(SDL_PollEvent(&event)){
            SDL_GetWindowSize(window,&largeur,&hauteur);
                switch (event.type){
                case SDL_QUIT:
                    isOpen = SDL_FALSE;
                    break;
                case SDL_MOUSEMOTION:
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, background,NULL, NULL);
                    //mode retour en blanc
                    if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+85 && event.button.y<=RectParam.y+128)){
                        
                        SDL_QueryTexture(retour,NULL,NULL,&RectParam.w,&RectParam.h);
                        RectParam.x = largeur /2 - RectParam.w /2;
                        RectParam.y = hauteur /2 - RectParam.h /2;
                        SDL_RenderCopy(renderer, retour,NULL, &RectParam);
                        SDL_RenderPresent(renderer);
                    }
                    //mode plein ecran en blanc
                    else if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+185 && event.button.y<=RectParam.y+230)){

                        SDL_QueryTexture(full,NULL,NULL,&RectParam.w,&RectParam.h);
                        RectParam.x = largeur /2 - RectParam.w /2;
                        RectParam.y = hauteur /2 - RectParam.h /2;
                        SDL_RenderCopy(renderer, full,NULL, &RectParam);
                        SDL_RenderPresent(renderer);
                    }
                    //mode fenetré en blanc
                    else if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+285 && event.button.y<=RectParam.y+335)){

                        SDL_QueryTexture(fenetrer,NULL,NULL,&RectParam.w,&RectParam.h);
                        RectParam.x = largeur /2 - RectParam.w /2;
                        RectParam.y = hauteur /2 - RectParam.h /2;
                        SDL_RenderCopy(renderer, fenetrer,NULL, &RectParam);
                        SDL_RenderPresent(renderer);
                    }
                    //mode quitter en blanc
                    else if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+400 && event.button.y<=RectParam.y+440)){

                        SDL_QueryTexture(quitter,NULL,NULL,&RectParam.w,&RectParam.h);
                        RectParam.x = largeur /2 - RectParam.w /2;
                        RectParam.y = hauteur /2 - RectParam.h /2;
                        SDL_RenderCopy(renderer, quitter,NULL, &RectParam);
                        SDL_RenderPresent(renderer);
                    }
                    else{

                        SDL_QueryTexture(menu,NULL,NULL,&RectParam.w,&RectParam.h);
                        RectParam.x = largeur /2 - RectParam.w /2;
                        RectParam.y = hauteur /2 - RectParam.h /2;
                        SDL_RenderCopy(renderer, menu,NULL, &RectParam);
                        SDL_RenderPresent(renderer);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    
                    if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+400 && event.button.y<=RectParam.y+440)){
                        return 0;
                    }
                    else if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+85 && event.button.y<=RectParam.y+128)){
                        
                        SDL_RenderClear(renderer);
                        isOpen = SDL_FALSE;
                    }
                    else if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+185 && event.button.y<=RectParam.y+230)){
                        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
                        grand=2;
                        SDL_RenderClear(renderer);
                    }
                    else if((event.button.x>=RectParam.x  && event.button.x<=RectParam.w+RectParam.x) && (event.button.y>=RectParam.y+285 && event.button.y<=RectParam.y+335)){
                        SDL_SetWindowFullscreen(window,0);
                        grand=1;
                        SDL_RenderClear(renderer);
                    }
                    
                    break;
            }
            
        }
		
	}
    SDL_DestroyTexture(full);
    SDL_DestroyTexture(fenetrer);
    SDL_DestroyTexture(quitter);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(menu);
	return grand;
}

/**
 * @brief Affiche le menu principal.
 *
 * Affiche le menu principal avec les boutons jouer, paramètres et quitter.
 *
 * @return Le statut de sortie.
 */
int menu()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *quit = NULL,*play = NULL,*background = NULL,*quit_des = NULL,*play_des = NULL,*parametre=NULL,*parametre_des=NULL;
    SDL_Event event;
    SDL_bool isOpen = SDL_TRUE;
    struct Input in;
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