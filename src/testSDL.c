#include "../lib/base_struct.h"
#include "../lib/fonc.h"

int jeu(SDL_Renderer *renderer)
{
    //Le pointeur vers la fenetre
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Rect txtDestRect,imgDestRect,imgDestRect2,imgDestRectCase1,imgDestRectCase2,imgDestRectCase3;
	SDL_Texture *background = NULL,*hud=NULL,*texte=NULL ,*case1=NULL,*case2=NULL,*case3=NULL;;
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
	// load sample.png into image (FOND)
	background=loadImage("../img/map_v1.png",renderer);

	hud=loadImage("../img/HUD.png",renderer);


	case1=loadImage("../img/1.png",renderer);

// load sample.png into image (CASE 1)
	case2=loadImage("../img/2.png",renderer);


// load sample.png into image (CASE 1)
	case3=loadImage("../img/3.png",renderer);


	
	int running = 1; 
	while(running) { 
		SDL_Event e; 
		/* Le fond de la fenêtre sera blanc */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		
		//image de fond
		imgDestRect.x = 0;
		imgDestRect.y = 0;
		SDL_QueryTexture(background, NULL, NULL,&(imgDestRect.w),&(imgDestRect.h));
		SDL_RenderCopy(renderer, background, NULL, NULL);
		//HUD tout moche
		imgDestRect2.x = 0;
		imgDestRect2.y = 600;
		SDL_QueryTexture(hud, NULL, NULL,&(imgDestRect2.w),&(imgDestRect2.h));
		SDL_RenderCopy(renderer, hud,NULL, &imgDestRect2);
		//Case1
		imgDestRectCase1.x = 50;
		imgDestRectCase1.y = 600;
		SDL_QueryTexture(case1,NULL, NULL,&(imgDestRectCase1.w),&(imgDestRectCase1.h));
		SDL_RenderCopy(renderer, case1,NULL, &imgDestRectCase1);
		//Case2
		imgDestRectCase2.x = 300;
		imgDestRectCase2.y = 600;
		SDL_QueryTexture(case2,NULL, NULL,&(imgDestRectCase2.w),&(imgDestRectCase2.h));
		SDL_RenderCopy(renderer, case2,NULL, &imgDestRectCase2);
		//Case3
		imgDestRectCase3.x = 550;
		imgDestRectCase3.y = 600;
		SDL_QueryTexture(case3,NULL, NULL,&(imgDestRectCase3.w),&(imgDestRectCase3.h));
		SDL_RenderCopy(renderer, case3,NULL, &imgDestRectCase3);
		SDL_RenderPresent(renderer); //Taille fenetre 1847 / 1015
		while(SDL_PollEvent(&e)) { 
			switch(e.type) { 
				case SDL_QUIT: running = 0; 
				break; 
				
					
							
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
	


	detruireHero(&hero1);
	detruireHero(&hero2);
	detruireHero(&hero3);

	/*for(int j = 0 ; j < MAXHERO ; j++){
		detruireHero(&tabHero->tab[j]->Hero);
	}*/
	free(&tabHero->tab);

    return 0;
}

