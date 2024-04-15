#include "../lib/base_struct.h"
#include "../lib/fonc.h"


typedef struct heroText_s heroText_t;
struct heroText_s{
	SDL_Texture * texture;
	SDL_Rect rectHero;
};

int param_open(SDL_Renderer *renderer){
	SDL_Event event;
	SDL_bool isOpen=SDL_TRUE;
	SDL_Texture *fenetre=NULL,*quit = NULL,*play = NULL,*parametre=NULL;
	SDL_Rect RectParam,position;
	int position_Y,position_X,position_Y_Play;

// load sample.png into image (fenetre de pause)
	fenetre=loadImage("../img/param_pause.png",renderer);
// load sample.png into image (quitter)
	quit=loadImage("../img/quit.jpg",renderer);
// load sample.png into image (jouer)
	play=loadImage("../img/start_maron.jpg",renderer);

	RectParam.w = WIDTHSCREEN /2;
	RectParam.h = HEIGHTSCREEN /2;
	RectParam.x = WIDTHSCREEN /2 - RectParam.w /2;
	RectParam.y = HEIGHTSCREEN /2 - RectParam.h /2;
	SDL_RenderCopy(renderer, fenetre,NULL, &RectParam);

    SDL_QueryTexture(quit, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN /2 - position.w /2;
    position.y = HEIGHTSCREEN /2 - position.h /2;
	position_X = position.x;
    position_Y = position.y;
    SDL_RenderCopy(renderer, quit, NULL, &position);

    SDL_QueryTexture(play, NULL, NULL, &(position.w), &(position.h)); // Récupere la dimension de la texture
    position.x = WIDTHSCREEN /2 - position.w /2;
    position.y = position_Y-70;
	position_Y_Play = position.y;
    SDL_RenderCopy(renderer, play, NULL, &position);

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
                    break;
			}
		}
	}
	return 1;
}

int jeu(SDL_Renderer *renderer)
{
    //Le pointeur vers la fenetre
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Rect txtDestRect,imgDestRect,imgDestRect2,imgDestRectCase1,imgDestRectCase2,imgDestRectCase3,imgDestRectpause;
	SDL_Texture *background = NULL,*hud=NULL,*texte=NULL ,*case1=NULL,*case2=NULL,*case3=NULL,*pause=NULL,*textHero1=NULL,*textHero2=NULL,*textHero3=NULL;
	// Le pointeur vers notre police
	TTF_Font *police = NULL;
	// Une variable de couleur noire
	SDL_Color couleurNoire = {0, 0, 0};
	tabCase_t * tabHero = malloc(sizeof(tabCase_t));
	for (int i = 0 ; i < MAXHERO ;i ++){
		tabHero->tab[i] = malloc(sizeof(hero_t));
	}

	heroText_t * lesHeros[MAXHERO];
	for(int tailleTab = 0 ; tailleTab < MAXHERO ; tailleTab++){
		lesHeros[tailleTab] = malloc(sizeof(heroText_t));
	}
	
	int nbCaseUse = 0;

	int * tailleCaseX = 0;
	int * tailleCaseY = 0;
	int caseHero = 0;
	
	hero_t * hero1 = malloc(sizeof(hero_t));
	hero_t * hero2 = malloc(sizeof(hero_t));
	hero_t * hero3 = malloc(sizeof(hero_t));

	int etat = 1;

	player_t * joueur = malloc(sizeof(player_t));

	joueur = initialise_joueur();

	hero1 = initialise_hero(0);
	hero2 = initialise_hero(1);
	hero3 = initialise_hero(2);

	// load sample.png into image (FOND)
	background=loadImage("../img/map_v1.png",renderer);

	hud=loadImage("../img/HUD.png",renderer);

// load sample.png into image (CASE 1)
	case1=loadImage("../img/1.png",renderer);

// load sample.png into image (CASE 2)
	case2=loadImage("../img/2.png",renderer);

// load sample.png into image (CASE 3)
	case3=loadImage("../img/3.png",renderer);

// load sample.png into image (pause)
	pause=loadImage("../img/pause.png",renderer);
// load lehero.png inti impage (HERO1)
	textHero1=loadImage("../img/sprite/Hero1.png",renderer);
// load lehero.png inti impage (HERO2)
	textHero2=loadImage("../img/sprite/Hero2.png",renderer);
// load lehero.png inti impage (HERO3)
	textHero3=loadImage("../img/lehero.png",renderer);

	
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
		imgDestRect2.y = HEIGHTSCREEN-200;
		SDL_QueryTexture(hud, NULL, NULL,&(imgDestRect2.w),&(imgDestRect2.h));
		SDL_SetTextureBlendMode(hud,SDL_BLENDMODE_ADD);
		SDL_RenderCopy(renderer, hud,NULL, &imgDestRect2);
		//Case1
		imgDestRectCase1.x = 50;
		imgDestRectCase1.y = HEIGHTSCREEN-155;
		SDL_QueryTexture(case1,NULL, NULL,&(imgDestRectCase1.w),&(imgDestRectCase1.h));
		SDL_RenderCopy(renderer, case1,NULL, &imgDestRectCase1);
		//Case2
		imgDestRectCase2.x = 300;
		imgDestRectCase2.y = HEIGHTSCREEN-155;
		SDL_QueryTexture(case2,NULL, NULL,&(imgDestRectCase2.w),&(imgDestRectCase2.h));
		SDL_RenderCopy(renderer, case2,NULL, &imgDestRectCase2);
		//Case3
		imgDestRectCase3.x = 550;
		imgDestRectCase3.y = HEIGHTSCREEN-155;
		SDL_QueryTexture(case3,NULL, NULL,&(imgDestRectCase3.w),&(imgDestRectCase3.h));
		SDL_RenderCopy(renderer, case3,NULL, &imgDestRectCase3);
		//bouton pause
		imgDestRectpause.x = 5;
		imgDestRectpause.y = 5;
		imgDestRectpause.w = 30;
		imgDestRectpause.h = 30;
		SDL_RenderCopy(renderer, pause,NULL, &imgDestRectpause);

		if(nbCaseUse - 1 >= 0){
		SDL_QueryTexture(lesHeros[nbCaseUse-1]->texture,NULL, NULL,&(lesHeros[nbCaseUse-1]->rectHero.w),&(lesHeros[nbCaseUse-1]->rectHero.h));
				int parcoursTab = 0;
				SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
				parcoursTab++;
				if(nbCaseUse >= 2){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 3){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 4){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 5){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 6){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 7){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 8){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 9){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				if(nbCaseUse >= 10){
					SDL_RenderCopy(renderer, lesHeros[parcoursTab]->texture,NULL, &lesHeros[parcoursTab]->rectHero);
					parcoursTab++;
				}
				
		}

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
			etat =1;;
			switch(caseHero){
				case 1:
				lesHeros[nbCaseUse]->texture = textHero1;
				for(int indice = 0 ; indice < nbCaseUse ; indice++){
						if(((e.button.x > tabHero->tab[indice]->coordX - (lesHeros[indice]->rectHero.w))&&(e.button.x < tabHero->tab[indice]->coordX + (lesHeros[indice]->rectHero.w)))&&((e.button.y > tabHero->tab[indice]->coordY - (lesHeros[indice]->rectHero.h))&&(e.button.y < tabHero->tab[indice]->coordY + (lesHeros[indice]->rectHero.h)) )){
							etat = 0;
						}
					}
				if(nbCaseUse < MAXHERO && etat == 1){
					if(joueur->argent >= hero1->prix){		
						tabHero->tab[nbCaseUse]->coordX = e.button.x;
						tabHero->tab[nbCaseUse]->coordY = e.button.y;
						tabHero->tab[nbCaseUse]->Hero = hero1;
						joueur->argent -= hero1->prix;
						SDL_Log("Vous poser le héro %s en coordonnée %d , %d et il coute %d pièce il vous en reste donc %d ",tabHero->tab[nbCaseUse]->Hero->nom,e.button.x,e.button.y,hero1->prix,joueur->argent);
						caseHero = 0;


						lesHeros[nbCaseUse]->rectHero.x = e.button.x - 32;
						lesHeros[nbCaseUse]->rectHero.y = e.button.y - 30 ;





						nbCaseUse++;

						SDL_Log("Le nombre de case utilisé : %d !",nbCaseUse);
						}
					else{
					SDL_Log("Vous n'avez pas assez d'argent pour acheter ce héros");
					}
				}
				else if(etat == 0)SDL_Log("Vous ne pouvez pas placer un héros sur un héros déjà existant ! ");
				else if(nbCaseUse >= MAXHERO){
					SDL_Log("Nombre de heros maximum atteins !");
				}	
				break;
						case 2:
						lesHeros[nbCaseUse]->texture = textHero2;
				for(int indice = 0 ; indice < nbCaseUse ; indice++){
						if(((e.button.x > tabHero->tab[indice]->coordX - (lesHeros[indice]->rectHero.w))&&(e.button.x < tabHero->tab[indice]->coordX + (lesHeros[indice]->rectHero.w)))&&((e.button.y > tabHero->tab[indice]->coordY - (lesHeros[indice]->rectHero.h))&&(e.button.y < tabHero->tab[indice]->coordY + (lesHeros[indice]->rectHero.h)) )){
							etat = 0;
						}
					}
				if(nbCaseUse < MAXHERO && etat == 1){
					if(joueur->argent >= hero2->prix){		
						tabHero->tab[nbCaseUse]->coordX = e.button.x;
						tabHero->tab[nbCaseUse]->coordY = e.button.y;
						tabHero->tab[nbCaseUse]->Hero = hero2;
						joueur->argent -= hero1->prix;
						SDL_Log("Vous poser le héro %s en coordonnée %d , %d et il coute %d pièce il vous en reste donc %d ",tabHero->tab[nbCaseUse]->Hero->nom,e.button.x,e.button.y,hero1->prix,joueur->argent);
						caseHero = 0;


						lesHeros[nbCaseUse]->rectHero.x = e.button.x - 32;
						lesHeros[nbCaseUse]->rectHero.y = e.button.y - 30 ;





						nbCaseUse++;

						SDL_Log("Le nombre de case utilisé : %d !",nbCaseUse);
						}
					else{
					SDL_Log("Vous n'avez pas assez d'argent pour acheter ce héros");
					}
				}
				else if(etat == 0)SDL_Log("Vous ne pouvez pas placer un héros sur un héros déjà existant ! ");
				else if(nbCaseUse >= MAXHERO){
					SDL_Log("Nombre de heros maximum atteins !");
				}	
				break;
						case 3:
						lesHeros[nbCaseUse]->texture = textHero3;
				for(int indice = 0 ; indice < nbCaseUse ; indice++){
						if(((e.button.x > tabHero->tab[indice]->coordX - (lesHeros[indice]->rectHero.w))&&(e.button.x < tabHero->tab[indice]->coordX + (lesHeros[indice]->rectHero.w)))&&((e.button.y > tabHero->tab[indice]->coordY - (lesHeros[indice]->rectHero.h))&&(e.button.y < tabHero->tab[indice]->coordY + (lesHeros[indice]->rectHero.h)) )){
							etat = 0;
						}
					}
				if(nbCaseUse < MAXHERO && etat == 1){
					if(joueur->argent >= hero3->prix){		
						tabHero->tab[nbCaseUse]->coordX = e.button.x;
						tabHero->tab[nbCaseUse]->coordY = e.button.y;
						tabHero->tab[nbCaseUse]->Hero = hero3;
						joueur->argent -= hero3->prix;
						SDL_Log("Vous poser le héro %s en coordonnée %d , %d et il coute %d pièce il vous en reste donc %d ",tabHero->tab[nbCaseUse]->Hero->nom,e.button.x,e.button.y,hero1->prix,joueur->argent);
						caseHero = 0;


						lesHeros[nbCaseUse]->rectHero.x = e.button.x - 32;
						lesHeros[nbCaseUse]->rectHero.y = e.button.y - 30 ;





						nbCaseUse++;

						SDL_Log("Le nombre de case utilisé : %d !",nbCaseUse);
						}
					else{
					SDL_Log("Vous n'avez pas assez d'argent pour acheter ce héros");
					}
				}
				else if(etat == 0)SDL_Log("Vous ne pouvez pas placer un héros sur un héros déjà existant ! ");
				else if(nbCaseUse >= MAXHERO){
					SDL_Log("Nombre de heros maximum atteins !");
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
		if((e.button.x >= imgDestRectpause.x && e.button.x <= imgDestRectpause.x + imgDestRectpause.w) && (e.button.y >= imgDestRectpause.y && e.button.y <= imgDestRectpause.y + imgDestRectpause.h)){
			SDL_Log("PAUSE");
			if(param_open(renderer)==0)running=0;
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

