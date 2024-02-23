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
    SDL_Surface *texte=NULL, *image=NULL , *image2=NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect txtDestRect,imgDestRect;

	// Le pointeur vers notre police
	TTF_Font *police = NULL;
	// Une variable de couleur noire
	SDL_Color couleurNoire = {0, 0, 0};

	hero_t * hero = NULL;
	
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
												  1847,
												  1015,
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

	// load sample.png into image
	SDL_RWops *rwop=SDL_RWFromFile("../img/echiquier.png", "rb");
	image=IMG_LoadPNG_RW(rwop);
	if(!image) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image); 
	if(!image_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */


	// load sample.png into image
	SDL_RWops *rwop2=SDL_RWFromFile("../img/HUD.png", "rb");
	image2=IMG_LoadPNG_RW(rwop2);
	if(!image2) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_tex2 = SDL_CreateTextureFromSurface(renderer, image2); 
	if(!image_tex2){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(image2); /* on a la texture, plus besoin de l'image */
	


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
								
                                
                                imgDestRect.x = 10;
								imgDestRect.y = 50;
								SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, image_tex, NULL, NULL);

								 imgDestRect.x = 0;
								imgDestRect.y = 800;
								SDL_QueryTexture(image_tex2, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, image_tex2, NULL,&imgDestRect);
								
							break;
						}
                    if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                                running = SDL_FALSE;
                                break;
                    case SDL_KEYDOWN:
            SDL_Log("+key");

            if (e.key.keysym.scancode == SDL_SCANCODE_D)
                SDL_Log("Scancode D");

            if (e.key.keysym.scancode == SDL_SCANCODE_W)
                SDL_Log("Scancode W");

            if (e.key.keysym.scancode == SDL_SCANCODE_A)
                SDL_Log("Scancode A");
			if (e.key.keysym.scancode == SDL_SCANCODE_S)
                SDL_Log("Scancode S");

            break;
        case SDL_KEYUP: 
            //SDL_Log("-key");
            break;
        case SDL_MOUSEMOTION: // Déplacement de souris
           //SDL_Log("Mouvement de souris (%d %d) (%d %d)", e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            break;
        case SDL_MOUSEBUTTONDOWN: // Click de souris 
			if((e.button.x >= 117 && e.button.y >= 844) && (e.button.x <= 320 && e.button.y <= 956)){
				SDL_Log("Le hero 1 à été saisie");
				hero = initialise_hero(0);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
			if((e.button.x >= 321 && e.button.y >= 844) && (e.button.x <= 523 && e.button.y <= 956)){
				SDL_Log("Le hero 2 à été saisie");
				hero = initialise_hero(1);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
			if((e.button.x >= 525 && e.button.y >= 844) && (e.button.x <= 725 && e.button.y <= 956)){
				SDL_Log("Le hero 3 à été saisie");
				hero = initialise_hero(2);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
			if((e.button.x >= 726 && e.button.y >= 844) && (e.button.x <= 932 && e.button.y <= 956)){
				SDL_Log("Le hero 4 à été saisie");
				hero = initialise_hero(3);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
			if((e.button.x >= 932 && e.button.y >= 844) && (e.button.x <= 1136 && e.button.y <= 956)){
				SDL_Log("Le hero 5 à été saisie");
				hero = initialise_hero(4);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
			if((e.button.x >= 1137 && e.button.y >= 844) && (e.button.x <=1341 && e.button.y <= 956)){
				SDL_Log("Le hero 6 à été saisie");
				hero = initialise_hero(5);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
				
			}
			if((e.button.x >= 1341 && e.button.y >= 844) && (e.button.x <= 1544 && e.button.y <= 956)){
				SDL_Log("Le hero 7 à été saisie");
				hero = initialise_hero(6);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
			if((e.button.x >= 1545 && e.button.y >= 844) && (e.button.x <= 1745 && e.button.y <= 956)){
				SDL_Log("Le hero 8 à été saisie");
				hero = initialise_hero(7);
				afficheHero(hero);
				detruireHero(&hero);
				printf("\n");
			}
            //SDL_Log("Click de la souris en (%d) (%d)", e.button.x, e.button.y);// 
            break;
        case SDL_MOUSEBUTTONUP: // Click de souris relâché
            //SDL_Log("-clic");
            break;
        case SDL_MOUSEWHEEL: // Scroll de la molette
            //SDL_Log("wheel");
            break;
						
					break;
				} 
                SDL_RenderPresent(renderer); //Taille fenetre 1847 / 1015
				// 0 - 1847 / 800 - 1015
			} 
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

    

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();

    return 0;
}

