#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/base_struct.h"

int main(int argc, char** argv)
{
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *texte=NULL, *fond=NULL , *hud=NULL,*case1=NULL,*case2=NULL,*case3=NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect txtDestRect,imgDestRect,imgDestRect2,imgDestRectCase1,imgDestRectCase2,imgDestRectCase3;

	// Le pointeur vers notre police
	TTF_Font *police = NULL;
	// Une variable de couleur noire
	SDL_Color couleurNoire = {0, 0, 0};

	tabCase_t * tabHero = malloc(sizeof(tabCase_t));
	for (int i = 0 ; i < MAXHERO ;i ++){
		tabHero->tab[i] = malloc(sizeof(hero_t));
	}

	int nbCaseUse = 0;

	int * tailleCaseX = 0;
	int * tailleCaseY = 0;
	int caseHero = 0;
	
	hero_t * hero1 = malloc(sizeof(hero_t));
	hero_t * hero2 = malloc(sizeof(hero_t));
	hero_t * hero3 = malloc(sizeof(hero_t));

	hero1 = initialise_hero(0);
	hero2 = initialise_hero(1);
	hero3 = initialise_hero(2);

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    } 

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}


	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Echiquier",SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  1000,
												  800,
												  SDL_WINDOW_SHOWN);

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

	// load sample.png into image (FOND)
	SDL_RWops *rwop=SDL_RWFromFile("../img/echiquier.png", "rb");
	fond=IMG_LoadPNG_RW(rwop);
	if(!fond) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, fond); 
	if(!image_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(fond); /* on a la texture, plus besoin de l'image */

	
	// load sample.png into image (HUD)
		SDL_RWops *rwop2=SDL_RWFromFile("../img/HUD.png", "rb");
		hud=IMG_LoadPNG_RW(rwop2);
		if(!hud) {
		     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
		}
		SDL_Texture *image_tex2 = SDL_CreateTextureFromSurface(renderer, hud); 
		if(!image_tex2){
			fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(hud); /* on a la texture, plus besoin de l'image */


// load sample.png into image (CASE 1)
		SDL_RWops *rwop3=SDL_RWFromFile("../img/1.png", "rb");
		case1=IMG_LoadPNG_RW(rwop3);
		if(!case1) {
		     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
		}
		SDL_Texture *image_texCase1 = SDL_CreateTextureFromSurface(renderer, case1); 
		if(!image_texCase1){
			fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(case1); /* on a la texture, plus besoin de l'image */

// load sample.png into image (CASE 1)
		SDL_RWops *rwop4=SDL_RWFromFile("../img/2.png", "rb");
		case2=IMG_LoadPNG_RW(rwop4);
		if(!case2) {
		     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
		}
		SDL_Texture *image_texCase2 = SDL_CreateTextureFromSurface(renderer, case2); 
		if(!image_texCase2){
			fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(case2); /* on a la texture, plus besoin de l'image  */


// load sample.png into image (CASE 1)
		SDL_RWops *rwop5=SDL_RWFromFile("../img/3.png", "rb");
		case3=IMG_LoadPNG_RW(rwop5);
		if(!case3) {
		     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
		}
		SDL_Texture *image_texCase3 = SDL_CreateTextureFromSurface(renderer, case3); 
		if(!image_texCase3){
			fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(case3); /* on a la texture, plus besoin de l'image */


	if( pWindow )
	{
		int running = 1; 
		while(running) { 
			SDL_Event e; 
			while(SDL_PollEvent(&e)) { 
				switch(e.type) { 
					case SDL_QUIT: running = 0; 
					break; 
					case SDL_WINDOWEVENT:
					switch(e.window.event){

							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:
                            

								/* Le fond de la fenêtre sera blanc */
                            	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderClear(renderer);
								
								//image de fond
                                imgDestRect.x = 0;
								imgDestRect.y = 0;
								SDL_QueryTexture(image_tex, NULL, NULL,&(imgDestRect.w),&(imgDestRect.h));
								SDL_RenderCopy(renderer, image_tex, NULL, NULL);

								//HUD tout moche
								imgDestRect2.x = 0;
								imgDestRect2.y = 600;
								SDL_QueryTexture(image_tex2, NULL, NULL,&(imgDestRect2.w),&(imgDestRect2.h));
								SDL_RenderCopy(renderer, image_tex2,NULL, &imgDestRect2);

								//Case1

								imgDestRectCase1.x = 50;
								imgDestRectCase1.y = 600;
								SDL_QueryTexture(image_texCase1,NULL, NULL,&(imgDestRectCase1.w),&(imgDestRectCase1.h));
								SDL_RenderCopy(renderer, image_texCase1,NULL, &imgDestRectCase1);

								//Case2

								imgDestRectCase2.x = 300;
								imgDestRectCase2.y = 600;
								SDL_QueryTexture(image_texCase2,NULL, NULL,&(imgDestRectCase2.w),&(imgDestRectCase2.h));
								SDL_RenderCopy(renderer, image_texCase2,NULL, &imgDestRectCase2);

								//Case3

								imgDestRectCase3.x = 550;
								imgDestRectCase3.y = 600;
								SDL_Log("%d",imgDestRectCase1.w);
								SDL_QueryTexture(image_texCase3,NULL, NULL,&(imgDestRectCase3.w),&(imgDestRectCase3.h));
								SDL_RenderCopy(renderer, image_texCase3,NULL, &imgDestRectCase3);

								SDL_RenderPresent(renderer); //Taille fenetre 1847 / 1015
								
							break;
						}
        if (e.window.event == SDL_WINDOWEVENT_CLOSE)
            	running = SDL_FALSE;
                break;
     	case SDL_KEYDOWN:
			SDL_Log("+key");
			break;
        case SDL_KEYUP: 
            SDL_Log("-key");
            break;
        case SDL_MOUSEMOTION: // Déplacement de souris
           //SDL_Log("Mouvement de souris (%d %d) (%d %d)", e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            break;
        case SDL_MOUSEBUTTONDOWN: // Click de souris 
			if(e.button.y < imgDestRect2.y || e.button.y > imgDestRect2.y + imgDestRect2.h){
				switch(caseHero){
					case 1:
					if(nbCaseUse < MAXHERO){
					tabHero->tab[nbCaseUse]->coordX = e.button.x;
					tabHero->tab[nbCaseUse]->coordY = e.button.y;
					tabHero->tab[nbCaseUse]->Hero = hero1;
					SDL_Log("Vous poser le héro %s en coordonnée %d , %d ",tabHero->tab[nbCaseUse]->Hero->nom,e.button.x,e.button.y);
					caseHero = 0;
					nbCaseUse++;
					}
					break;
					case 2:
					if(nbCaseUse < MAXHERO){
					tabHero->tab[nbCaseUse]->coordX = e.button.x;
					tabHero->tab[nbCaseUse]->coordY = e.button.y;
					tabHero->tab[nbCaseUse]->Hero = hero2;
					SDL_Log("Vous poser le héro %s en coordonnée %d , %d ",tabHero->tab[nbCaseUse]->Hero->nom,e.button.x,e.button.y);
					caseHero = 0;
					nbCaseUse++;
					}
					break;
					case 3:
					if(nbCaseUse < MAXHERO){
					tabHero->tab[nbCaseUse]->coordX = e.button.x;
					tabHero->tab[nbCaseUse]->coordY = e.button.y;
					tabHero->tab[nbCaseUse]->Hero = hero3;
					SDL_Log("Vous poser le héro %s en coordonnée %d , %d ",tabHero->tab[nbCaseUse]->Hero->nom,e.button.x,e.button.y);
					caseHero = 0;
					nbCaseUse++;
					}
					break;
				}
			}
			if((e.button.x >= imgDestRectCase1.x && e.button.x <= imgDestRectCase1.x + imgDestRectCase1.w) && (e.button.y >= imgDestRectCase1.y && e.button.y <= imgDestRectCase1.y + imgDestRectCase1.h)){
				SDL_Log("Réussite ca clique sur la case 1");
				SDL_Log("Hero 1 selectionner");
				caseHero = 1;
			}
			if((e.button.x >= imgDestRectCase2.x && e.button.x <= imgDestRectCase2.x + imgDestRectCase2.w) && (e.button.y >= imgDestRectCase2.y && e.button.y <= imgDestRectCase2.y + imgDestRectCase2.h)){
				SDL_Log("Réussite ca clique sur case 2");
				SDL_Log("Hero 2 selectionner");
				caseHero = 2;
			}
			if((e.button.x >= imgDestRectCase3.x && e.button.x <= imgDestRectCase3.x + imgDestRectCase3.w) && (e.button.y >= imgDestRectCase3.y && e.button.y <= imgDestRectCase3.y + imgDestRectCase3.h)){
				SDL_Log("Réussite ca clique sur case 3");
				SDL_Log("Hero 3 selectionner");
				caseHero = 3;
			}
			
            SDL_Log("Click de la souris en (%d) (%d)", e.button.x, e.button.y);// 
            break;
        case SDL_MOUSEBUTTONUP: // Click de souris relâché
            SDL_Log("-clic");
        break;
        case SDL_MOUSEWHEEL: // Scroll de la molette
            SDL_Log("wheel");
        break;
						
					break;
				} 
			} 
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

    

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

	detruireHero(&hero1);
	detruireHero(&hero2);
	detruireHero(&hero3);

	/*for(int j = 0 ; j < MAXHERO ; j++){
		detruireHero(&tabHero->tab[j]->Hero);
	}*/
	free(&tabHero->tab);

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();
	

    return 0;
}

