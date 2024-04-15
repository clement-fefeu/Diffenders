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

int param(SDL_Renderer *renderer,SDL_Window *window,int *largeur, int *hauteur){
	SDL_Event event;
	SDL_bool isOpen=SDL_TRUE;
	SDL_Texture *fenetre=NULL,*quit = NULL,*play = NULL,*plein_ecran=NULL,*fenetrer=NULL;
	SDL_Rect RectParam,position;
	int position_Y,position_X,position_Y_Play,position_Y_param1,position_Y_param2;
    SDL_bool fullscreen=SDL_FALSE;
// load sample.png into image (fenetre de pause)
	fenetre=loadImage("../img/menu.png",renderer);
// load sample.png into image (quitter)
	quit=loadImage("../img/quitter_m.png",renderer);
// load sample.png into image (retour)
	play=loadImage("../img/jouer_m.png",renderer);
// load sample.png into image (plein ecran)
	plein_ecran=loadImage("../img/full_screen.png",renderer);
// load sample.png into image (fenetrer)
	fenetrer=loadImage("../img/fenetrer.png",renderer);

	RectParam.w = *largeur /2;
	RectParam.h = *hauteur /2;
	RectParam.x = *largeur /2 - RectParam.w /2;
	RectParam.y = *hauteur /2 - RectParam.h /2;
	SDL_RenderCopy(renderer, fenetre,NULL, &RectParam);

    SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = *largeur /2 - position.w /2;
    position.y = *hauteur /2 - position.h /2;
	position_X = position.x;
    position_Y = position.y;
    SDL_RenderCopy(renderer, quit, NULL, &position);

    SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = *largeur /2 - position.w /2;
    position.y = position_Y-70;
	position_Y_Play = position.y;
    SDL_RenderCopy(renderer, play, NULL, &position);

    SDL_QueryTexture(plein_ecran, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = *largeur /2 - position.w /2;
    position.y = position_Y+150;
	position_Y_param1 = position.y;
    SDL_RenderCopy(renderer, plein_ecran, NULL, &position);

    SDL_QueryTexture(fenetrer, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = *largeur /2 - position.w /2;
    position.y = position_Y+70;
	position_Y_param2 = position.y;
    SDL_RenderCopy(renderer, fenetrer, NULL, &position);

	SDL_RenderPresent(renderer);
	while(isOpen){
		while (SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					isOpen = SDL_FALSE;
					break;
				case SDL_MOUSEBUTTONDOWN:
                    SDL_Log("%d %d",event.button.x,event.button.y);
                    if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y && event.button.y<=position_Y+35)){
                        return 0;
                    }
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_Play && event.button.y<=position_Y_Play+35)){
						isOpen = SDL_FALSE;
					}
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_param1 && event.button.y<=position_Y_param1+35)){
                        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
                        SDL_GetWindowSize(window,largeur,hauteur);
                        isOpen = SDL_FALSE;
                    }
                    else if((event.button.x>=position_X && event.button.x<=position_X+85) && (event.button.y>=position_Y_param2 && event.button.y<=position_Y_param2+35)){
                        SDL_SetWindowFullscreen(window,0);
                        SDL_GetWindowSize(window,largeur,hauteur);
                        isOpen = SDL_FALSE;
                    }
                    
                    break;
			}
		}
	}
	return 1;
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
         while (SDL_PollEvent(&event))
        {
            
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
                        jeu(renderer);

                        accueil(renderer,0,quit,play,background,quit_des,play_des,parametre,parametre_des,largeur,hauteur);
                    }
                    else if((event.button.x>=pos_param.x && event.button.x<=pos_param.x+pos_param.w) && (event.button.y>=pos_param.y && event.button.y<=pos_param.y+pos_param.h)){
                        SDL_Log("PARAMETRE");
                        if(param(renderer,window,&largeur,&hauteur)==0) isOpen=SDL_FALSE;
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