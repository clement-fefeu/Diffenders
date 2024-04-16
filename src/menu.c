#include "../lib/fonc.h"
#include "../lib/base_struct.h"



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
            pos_play.y = pos_quit.y-150;
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
            pos_play.y = pos_quit.y-150;
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
            pos_play.y = pos_quit.y-150;
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
            pos_play.y = pos_quit.y-150;
            SDL_RenderCopy(renderer, play, NULL, &pos_play);

            SDL_QueryTexture(parametre_des, NULL, NULL, &(pos_param.w), &(pos_param.h)); // Récupere la dimension de la texture
            pos_param.x = largeur /2 - pos_param.w /2;
            pos_param.y = pos_quit.y-70;
            SDL_RenderCopy(renderer, parametre_des, NULL, &pos_param);

            SDL_RenderPresent(renderer);
            break;

    }
        
}

int param(SDL_Renderer *renderer,SDL_Window *window,int largeur, int hauteur,SDL_Texture *background){
	SDL_Event event;
	SDL_bool isOpen=SDL_TRUE;
	SDL_Texture *menu=NULL,*full = NULL,*retour = NULL,*quitter=NULL,*fenetrer=NULL;
	SDL_Rect RectParam,position;
	int position_Y,position_X,position_Y_Play,position_Y_param1,position_Y_param2;
    SDL_bool fullscreen=SDL_FALSE;
    int grand=1;
// load sample.png into image (fenetre de pause)
	menu=loadImage("../img/menu.png",renderer);
// load sample.png into image (quitter)
	retour=loadImage("../img/retour_b.png",renderer);
// load sample.png into image (retour)
	quitter=loadImage("../img/quitter_b.png",renderer);
// load sample.png into image (plein ecran)
	full=loadImage("../img/plein_ecran_b.png",renderer);
// load sample.png into image (fenetrer)
	fenetrer=loadImage("../img/fenetrer_b.png",renderer);


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
	return grand;
}

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
    SDL_Rect pos_quit,pos_play,pos_param;
    int statut = EXIT_FAILURE;
    int position_X,position_Y,position_Y_Play,position_Y_param;
    /* Initialisation simple */
    init(&window,&renderer,WIDTHSCREEN,HEIGHTSCREEN);
    init_icon(window);
    int largeur=WIDTHSCREEN,hauteur=HEIGHTSCREEN;

    background=loadImage("../img/tower_def.jpg",renderer);
    play=loadImage("../img/jouer_m.png",renderer);
    quit=loadImage("../img/quitter_m.png",renderer);
    play_des=loadImage("../img/jouer_g.png",renderer);
    quit_des=loadImage("../img/quitter_g.png",renderer);
    parametre=loadImage("../img/parametre.png",renderer);
    parametre_des=loadImage("../img/parametre_g.png",renderer);

    SDL_QueryTexture(quit, NULL, NULL, &(pos_quit.w), &(pos_quit.h)); // Récupere la dimension de la texture
    pos_quit.x = largeur /2 - pos_quit.w /2;
    pos_quit.y = hauteur /2 - pos_quit.h /2;
    SDL_QueryTexture(play, NULL, NULL, &(pos_play.w), &(pos_play.h)); // Récupere la dimension de la texture
    pos_play.x = largeur /2 - pos_play.w /2;
    pos_play.y = pos_quit.y-150;
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
                        pos_play.y = pos_quit.y-150;
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
                        pos_play.y = pos_quit.y-150;
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