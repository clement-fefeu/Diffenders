#include "../lib/base_struct.h"
#include "../lib/fonc.h"


/**
 * @struct heroText_s
 * @brief Structure représentant la texture et la position d'un héros.
 */
typedef struct heroText_s {
	SDL_Texture *texture; /**< La texture du héros. */
	SDL_Rect rectHero;    /**< La position et la taille du héros. */
} heroText_t;

/**
 * @brief Affiche le montant d'argent et une texture donnée à l'écran.
 * 
 * @param renderer Le renderer SDL.
 * @param hauteur La hauteur de l'écran.
 * @param largeur La largeur de l'écran.
 * @param texte La texture à afficher.
 */
void affiche_argent(SDL_Renderer *renderer,int hauteur,int largeur,SDL_Texture *texte){
	SDL_Texture *argent;
	SDL_Rect position;
	argent=loadImage("../img/euro.png",renderer);

	position.x = largeur-20;
	position.y = 10;
	SDL_QueryTexture(argent, NULL, NULL,&(position.w),&(position.h));
	position.w/=25;
	position.h/=25;
	SDL_RenderCopy(renderer, argent,NULL, &position);


	SDL_QueryTexture(texte, NULL, NULL,&(position.w),&(position.h));
	position.x = position.x-position.w;
	position.y = 0;
	SDL_RenderCopy(renderer, texte,NULL, &position);



	SDL_DestroyTexture(argent);
}

/**
 * @brief La boucle principale du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 * @return int Retourne 0 en cas de réussite.
 */
int jeu(SDL_Renderer *renderer,SDL_Window *window)
{
    //Le pointeur vers la fenetre
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Rect txtDestRect,imgDestRect,imgDestRect2,imgDestRectCase1,imgDestRectCase2,imgDestRectCase3,imgDestRectpause;
	SDL_Texture *background = NULL,*hud=NULL,*texte=NULL ,*case1=NULL,*case2=NULL,*case3=NULL,*pause=NULL,*textHero1=NULL,*textHero2=NULL,*textHero3=NULL;
	// Le pointeur vers notre police
  	int tab[ABS][ORD];
	int largeur,hauteur;
	// Une variable de couleur noire
	int map=0;
	char nb_argent[20];
	if(map==0){
		creation_map(renderer,tab);
		map=1;
	}
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

	background=loadImage("../img/map_pixel_v2.png",renderer);
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
		SDL_GetWindowSize(window,&largeur,&hauteur);
		imgDestRect.x=0;
		imgDestRect.y=0;
		imgDestRect.h=hauteur-200;
		imgDestRect.w=largeur;
		SDL_RenderCopy(renderer, background,NULL, &imgDestRect);

		affiche_map_2(tab,renderer,window);
		//HUD tout moche
		imgDestRect2.x = 0;
		imgDestRect2.y = hauteur-200;
		SDL_QueryTexture(hud, NULL, NULL,&(imgDestRect2.w),&(imgDestRect2.h));
		SDL_RenderCopy(renderer, hud,NULL, &imgDestRect2);
		//Case1
		imgDestRectCase1.x = 50;
		imgDestRectCase1.y = hauteur-155;
		SDL_QueryTexture(case1,NULL, NULL,&(imgDestRectCase1.w),&(imgDestRectCase1.h));
		SDL_RenderCopy(renderer, case1,NULL, &imgDestRectCase1);
		//Case2
		imgDestRectCase2.x = 300;
		imgDestRectCase2.y = hauteur-155;
		SDL_QueryTexture(case2,NULL, NULL,&(imgDestRectCase2.w),&(imgDestRectCase2.h));
		SDL_RenderCopy(renderer, case2,NULL, &imgDestRectCase2);
		//Case3
		imgDestRectCase3.x = 550;
		imgDestRectCase3.y = hauteur-155;
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

		SDL_itoa(joueur->argent,nb_argent,10);
		texte=load_text(renderer,nb_argent,30);
		affiche_argent(renderer,hauteur,largeur,texte);
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
				case SDL_KEYUP: // Événement de relâchement d'une touche clavier
					if ( e.key.keysym.sym == SDLK_ESCAPE ) // C'est la touche Échap
					{
						SDL_Log("PAUSE");
						switch(param(renderer,window,largeur,hauteur,background)){
							case 0:running=SDL_FALSE;break;
							case 2:SDL_GetWindowSize(window,&largeur,&hauteur);break;
							case 1:
							largeur=WIDTHSCREEN;
							hauteur=HEIGHTSCREEN;
							break;
						}
					}
						break;
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
						switch(param(renderer,window,largeur,hauteur,background)){
							case 0:running=SDL_FALSE;break;
							case 2:SDL_GetWindowSize(window,&largeur,&hauteur);break;
							case 1:
							largeur=WIDTHSCREEN;
							hauteur=HEIGHTSCREEN;
							break;
						}
						
					}
					
					SDL_Log("Click de la souris en (%d) (%d)", e.button.x, e.button.y);// 
					break;
				case SDL_MOUSEBUTTONUP: // Click de souris relâché
					SDL_Log("-clic");
					break;
				case SDL_MOUSEWHEEL: // Scroll de la molette
					SDL_Log("wheel");
					break;
								
				} 
		} 
	}
	
	SDL_DestroyTexture(case1);
	SDL_DestroyTexture(case2);
	SDL_DestroyTexture(case2);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(hud);
	SDL_DestroyTexture(pause);
	SDL_DestroyTexture(textHero1);
	SDL_DestroyTexture(textHero2);
	SDL_DestroyTexture(textHero3);
	SDL_DestroyTexture(texte);

	detruireHero(&hero1);
	detruireHero(&hero2);
	detruireHero(&hero3);

	/*for(int j = 0 ; j < MAXHERO ; j++){
		detruireHero(&tabHero->tab[j]->Hero);
	}*/
	free(&tabHero->tab);

    return 0;
}

