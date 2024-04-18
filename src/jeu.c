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
	loadImage("../img/euro.png",renderer,&argent);
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
void affiche_PV(SDL_Renderer *renderer,int hauteur,int largeur,SDL_Texture *texte){
	SDL_Rect position;

	SDL_QueryTexture(texte, NULL, NULL,&(position.w),&(position.h));
	position.x = position.x/2;
	position.y = 0;
	SDL_RenderCopy(renderer, texte,NULL, &position);

}

Uint32 attendre(Uint32 interval,void* parametre){
	*(int*)parametre=1;
	return interval;
}
ennemie_t * avancerHorizontal(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord){
		if(indice == 0){
			if(((WIDTHSCREEN/ABS)*coord[indiceChemin+1].x + (WIDTHSCREEN/ABS)/4) > ennemie[indice]->imgDestRectEnnemie.x){
				ennemie[indice]->imgDestRectEnnemie.x += 1;
			}
		}
		else if(indice > 0){
			if(ennemie[indice]->imgDestRectEnnemie.x < ennemie[indice-1]->imgDestRectEnnemie.x - ennemie[indice-1]->imgDestRectEnnemie.w || (ennemie[indice]->imgDestRectEnnemie.y < ennemie[indice-1]->imgDestRectEnnemie.y  || ennemie[indice]->imgDestRectEnnemie.y > ennemie[indice-1]->imgDestRectEnnemie.y )){
					ennemie[indice]->imgDestRectEnnemie.x += 1;
			}
		}
	//SDL_Log("AVANCER = Coord X et Y de l'ennemie : %d | %d / %d",ennemie[indice]->imgDestRectEnnemie.x,ennemie[indice]->imgDestRectEnnemie.y,indice);
	return ennemie[indice];
}

ennemie_t * reculerHorizontal(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord){
		if(indice == 0){
			
			if(((WIDTHSCREEN/ABS)*coord[indiceChemin+1].x + (WIDTHSCREEN/ABS)/4) < ennemie[indice]->imgDestRectEnnemie.x){
				ennemie[indice]->imgDestRectEnnemie.x -= 1;
			}
		}
		else if(indice > 0 ){
			if(ennemie[indice]->imgDestRectEnnemie.x > ennemie[indice-1]->imgDestRectEnnemie.x - ennemie[indice-1]->imgDestRectEnnemie.w || (ennemie[indice]->imgDestRectEnnemie.y < ennemie[indice-1]->imgDestRectEnnemie.y || ennemie[indice]->imgDestRectEnnemie.y > ennemie[indice-1]->imgDestRectEnnemie.y)){
				ennemie[indice]->imgDestRectEnnemie.x -= 1;
			}
		}
	//SDL_Log("RECULER = Coord X et Y de l'ennemie : %d | %d / %d",ennemie[indice]->imgDestRectEnnemie.x,ennemie[indice]->imgDestRectEnnemie.y,indice);
	return ennemie[indice];
}

ennemie_t * descendreVertical(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord){
		if(indice == 0){
			if((ennemie[indice]->imgDestRectEnnemie.y < ((HEIGHTSCREEN-200)/ORD)*coord[indiceChemin+1].y + ((HEIGHTSCREEN-200)/ORD)/4)){
				ennemie[indice]->imgDestRectEnnemie.y += 1;
			}
		}
		else if(indice > 0){
				if((ennemie[indice]->imgDestRectEnnemie.y < ennemie[indice-1]->imgDestRectEnnemie.y - ennemie[indice-1]->imgDestRectEnnemie.h) || (ennemie[indice]->imgDestRectEnnemie.x < ennemie[indice-1]->imgDestRectEnnemie.x || ennemie[indice]->imgDestRectEnnemie.x > ennemie[indice-1]->imgDestRectEnnemie.x)){
					ennemie[indice]->imgDestRectEnnemie.y +=1 ;
				}
		}
	return ennemie[indice];
}

ennemie_t * monterVertical(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord){
		if(indice == 0){
			if((ennemie[indice]->imgDestRectEnnemie.y > ((HEIGHTSCREEN-200)/ORD)*coord[indiceChemin+1].y + ((HEIGHTSCREEN-200)/ORD)/4)){
				ennemie[indice]->imgDestRectEnnemie.y -= 1;
			}
		}
		else if(indice > 0){
				if((ennemie[indice]->imgDestRectEnnemie.y > ennemie[indice-1]->imgDestRectEnnemie.y + ennemie[indice-1]->imgDestRectEnnemie.h) || (ennemie[indice]->imgDestRectEnnemie.x < ennemie[indice-1]->imgDestRectEnnemie.x || ennemie[indice]->imgDestRectEnnemie.x > ennemie[indice-1]->imgDestRectEnnemie.x)){
					ennemie[indice]->imgDestRectEnnemie.y -=1 ;
				}
		}
	return ennemie[indice];
}

int detruireLesHeros(ennemie_t ** ennemie , int indice , int nbMax){
		ennemie_t * temp;

		temp = ennemie[indice];

		
		ennemie[nbMax-1] = temp;

		for(int i = 0 ; i < nbMax-1 ; i++){
			ennemie[i] = ennemie[i+1];
		}
		detruireEnem(&ennemie[nbMax-1]);
		ennemie[nbMax-1] = NULL;

		return nbMax;
}


int appelTextEnnemie(SDL_Renderer * renderer, SDL_Texture *texture , SDL_Rect * drect , int *w,int * h){
	SDL_QueryTexture(texture,NULL, NULL,w,h);
	SDL_RenderCopy(renderer, texture,NULL, drect);
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
	SDL_Rect txtDestRect,imgDestRect,imgDestRect2,imgDestRectCase1,imgDestRectCase2,imgDestRectCase3,imgDestRectpause,position;
	SDL_Texture *background = NULL,*hud=NULL,*texte=NULL ,*case1=NULL,*case2=NULL,*case3=NULL,*pause=NULL,*textHero1=NULL,*textHero2=NULL,*textHero3=NULL,*textEnnemie=NULL;
	SDL_Texture *boule=NULL,*PV=NULL;
  	int tab[ABS][ORD];
	int largeur,hauteur;
	int vague=0;
	int map=0;
  	chemin_t suite;
	char nb_argent[20],pv_base[20];
	int nb_timer=0;
	SDL_TimerID timer[MAXHERO];
	if(map==0){
		suite=creation_map(renderer,tab);
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

	int indice = 0;

	int delay = 10;

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

	int indiceChemin = 0;

	loadImage("../img/map_pixel_v2.png",renderer,&background);
	loadImage("../img/HUD.png",renderer,&hud);

// load sample.png into image (CASE 1)
	loadImage("../img/1.png",renderer,&case1);

// load sample.png into image (CASE 2)
	loadImage("../img/2.png",renderer,&case2);

// load sample.png into image (CASE 3)
	loadImage("../img/3.png",renderer,&case3);

// load sample.png into image (pause)
	loadImage("../img/pause.png",renderer,&pause);
// load lehero.png inti impage (HERO1)
	loadImage("../img/sprite/Hero1.png",renderer,&textHero1);
// load lehero.png inti impage (HERO2)
	loadImage("../img/sprite/Hero2.png",renderer,&textHero2);
// load lehero.png inti impage (HERO3)
	loadImage("../img/lehero.png",renderer,&textHero3);
	 
	loadImage("../img/sprite/ennemie.png",renderer,&textEnnemie);

// load boule.png into image (boule de feu)
	loadImage("../img/boule.png",renderer,&boule);

	int nbEnnemie ;
	int base=500;

	
	
	while(vague<MAX_Vague){
		int running = 1; 
		nbEnnemie = 6+vague;
		joueur->argent+=500;
		ennemie_t * temp=NULL;

		ennemie_t * tabEnnemie[nbEnnemie];
		SDL_GetWindowSize(window,&largeur,&hauteur);
		tabEnnemie[0] = malloc(sizeof(ennemie_t));
		tabEnnemie[0]->pv = 100+50*vague;
		tabEnnemie[0]->texture = textEnnemie;
		tabEnnemie[0]->imgDestRectEnnemie.x = (largeur/ABS)*suite.chemin[0].x + (largeur/ABS)/4;
		tabEnnemie[0]->imgDestRectEnnemie.y = ((hauteur-200)/ORD)*suite.chemin[0].y + ((hauteur-200)/ORD)/4;
		
		for(int i = nbEnnemie - (nbEnnemie -1); i < nbEnnemie ; i++){
			tabEnnemie[i] = NULL;
		}

		int palierX = 0;
		while(running) { 
			SDL_Event e;
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
			SDL_itoa(base,pv_base,10);
			texte=load_text(renderer,nb_argent,30);
			PV=load_text(renderer,pv_base,30);
			affiche_argent(renderer,hauteur,largeur,texte);
			affiche_PV(renderer,hauteur,largeur,PV);
			/*SDL_Log("ICI 1 ");*/
			
			for(indice = 0; indice < nbEnnemie ; indice++){
				
				if(tabEnnemie[indice+1]== NULL && indice < nbEnnemie-1){
					tabEnnemie[indice+1] = malloc(sizeof(ennemie_t)); 
					tabEnnemie[indice+1]->texture = textEnnemie;
					tabEnnemie[indice+1]->pv = 100+50*vague;
					tabEnnemie[indice+1]->palier = 0;
					tabEnnemie[indice+1]->imgDestRectEnnemie.x = (largeur/ABS)*suite.chemin[0].x + (largeur/ABS)/4;
					tabEnnemie[indice+1]->imgDestRectEnnemie.y = ((hauteur-200)/ORD)*suite.chemin[0].y + (((hauteur-200)/ORD)/4);
				}
				/*SDL_Log(" %d ",indiceChemin);*/
				if(tabEnnemie[indice] != NULL){	
					//SDL_Log("L'indice du chemin est %d pour l'ennemie %d ", tabEnnemie[indice]->palier,indice);
						if(tabEnnemie[indice]->imgDestRectEnnemie.x < (WIDTHSCREEN/ABS)*suite.chemin[(tabEnnemie[indice]->palier+1)].x + (WIDTHSCREEN/ABS)/4){
							tabEnnemie[indice] = avancerHorizontal(tabEnnemie,nbEnnemie,indice,tabEnnemie[indice]->palier,suite.chemin);
						}
						else if(tabEnnemie[indice]->imgDestRectEnnemie.x > (WIDTHSCREEN/ABS)*suite.chemin[(tabEnnemie[indice]->palier+1)].x + (WIDTHSCREEN/ABS)/4){
							tabEnnemie[indice] = reculerHorizontal(tabEnnemie,nbEnnemie,indice,tabEnnemie[indice]->palier,suite.chemin);
						}
						else if(tabEnnemie[indice]->imgDestRectEnnemie.y < (((HEIGHTSCREEN-200)/ORD))*suite.chemin[(tabEnnemie[indice]->palier+1)].y + (((HEIGHTSCREEN-200)/ORD)/4)){
							tabEnnemie[indice] = descendreVertical(tabEnnemie,nbEnnemie,indice,tabEnnemie[indice]->palier,suite.chemin);
						}
						else if(tabEnnemie[indice]->imgDestRectEnnemie.y > (((HEIGHTSCREEN-200)/ORD))*suite.chemin[(tabEnnemie[indice]->palier+1)].y + (((HEIGHTSCREEN-200)/ORD)/4)){
							tabEnnemie[indice] = monterVertical(tabEnnemie,nbEnnemie,indice,tabEnnemie[indice]->palier,suite.chemin);
						}
					if((tabEnnemie[indice]->imgDestRectEnnemie.x == (WIDTHSCREEN/ABS)*suite.chemin[tabEnnemie[indice]->palier+1].x + (WIDTHSCREEN/ABS)/4) && (tabEnnemie[indice]->imgDestRectEnnemie.y == (((HEIGHTSCREEN-200)/ORD))*suite.chemin[tabEnnemie[indice]->palier+1].y + (((HEIGHTSCREEN-200)/ORD)/4))){
						tabEnnemie[indice]->palier++;	
					}
				}
				
				
				/*SDL_Log("Le max en X et Y est : %d | %d ",suite.chemin[indiceChemin+1].x,suite.chemin[indiceChemin+1].y);*/
				if(suite.chemin[(tabEnnemie[indice]->palier)+1].x == -1 && suite.chemin[(tabEnnemie[indice]->palier)+1].y == -1){
					if(tabEnnemie[indice]!=NULL){					
					
						for(int j = 0 ; j < nbEnnemie-1 ; j++){
							tabEnnemie[j] = tabEnnemie[j+1];
							if(j >= nbEnnemie-1){
								tabEnnemie[j+1] = NULL;
							}
						}

						base-=tabEnnemie[0]->pv;
						SDL_Log("%d",base);
						tabEnnemie[nbEnnemie]= temp;
						free(tabEnnemie[nbEnnemie]);
						nbEnnemie--;
						SDL_Log("mort");
						if(base<=0){
							running = 0; 
							SDL_Log("Defaite");
							vague=MAX_Vague;
						}
						if(nbEnnemie==0){
							running=0;
						}
					}
				}
				SDL_Delay(0.5);
				if(tabEnnemie[indice] != NULL){
					appelTextEnnemie(renderer,tabEnnemie[indice]->texture,&tabEnnemie[indice]->imgDestRectEnnemie,&tabEnnemie[indice]->imgDestRectEnnemie.w,&tabEnnemie[indice]->imgDestRectEnnemie.h);
				}
				if(nbCaseUse>=1){
					for(int i=0;i<nbCaseUse;i++){
						if(hero1->cooldown==1 && tabHero->tab[i]->Hero==hero1){
							tabEnnemie[0]->pv-=hero1->degat;
							hero1->cooldown=0;
							imgDestRect2.x = tabEnnemie[0]->imgDestRectEnnemie.x;
							imgDestRect2.y = tabEnnemie[0]->imgDestRectEnnemie.y;
							imgDestRect2.w = tabEnnemie[0]->imgDestRectEnnemie.w;
							imgDestRect2.h= tabEnnemie[0]->imgDestRectEnnemie.h;
							SDL_RenderCopy(renderer, boule,NULL, &imgDestRect2);
							if(tabEnnemie[0]->pv<=0){
								for(int j = 0 ; j < nbEnnemie-1 ; j++){
									tabEnnemie[j] = tabEnnemie[j+1];
								}
								tabEnnemie[nbEnnemie-1]=temp;
								free(tabEnnemie[nbEnnemie-1]);
								nbEnnemie--;
								SDL_Log("mort");
							}

							if(nbEnnemie==0 && vague==MAX_Vague){
								running = 0; 
								SDL_Log("Victoire");
							}
						}
						if(hero2->cooldown==1 && tabHero->tab[i]->Hero==hero2){
							tabEnnemie[0]->pv-=hero2->degat;
							hero2->cooldown=0;
							imgDestRect2.x = tabEnnemie[0]->imgDestRectEnnemie.x;
							imgDestRect2.y = tabEnnemie[0]->imgDestRectEnnemie.y;
							imgDestRect2.w = tabEnnemie[0]->imgDestRectEnnemie.w;
							imgDestRect2.h= tabEnnemie[0]->imgDestRectEnnemie.h;
							SDL_RenderCopy(renderer, boule,NULL, &imgDestRect2);
							if(tabEnnemie[0]->pv<=0){
								for(int j = 0 ; j < nbEnnemie-1 ; j++){
									tabEnnemie[j] = tabEnnemie[j+1];
								}
								tabEnnemie[nbEnnemie-1]=temp;
								free(tabEnnemie[nbEnnemie-1]);
								nbEnnemie--;
								SDL_Log("mort");
							}

							if(nbEnnemie==0){
								running = 0; 
								SDL_Log("Victoire");
							}
						}
						if(hero3->cooldown==1 && tabHero->tab[i]->Hero==hero3){
							tabEnnemie[0]->pv-=hero3->degat;
							hero3->cooldown=0;
							imgDestRect2.x = tabEnnemie[0]->imgDestRectEnnemie.x;
							imgDestRect2.y = tabEnnemie[0]->imgDestRectEnnemie.y;
							imgDestRect2.w = tabEnnemie[0]->imgDestRectEnnemie.w;
							imgDestRect2.h= tabEnnemie[0]->imgDestRectEnnemie.h;
							SDL_RenderCopy(renderer, boule,NULL, &imgDestRect2);
							if(tabEnnemie[0]->pv<=0){
								for(int j = 0 ; j < nbEnnemie-1 ; j++){
									tabEnnemie[j] = tabEnnemie[j+1];
								}
								tabEnnemie[nbEnnemie-1]=temp;
								free(tabEnnemie[nbEnnemie-1]);
								nbEnnemie--;
								SDL_Log("mort");
							}

							if(nbEnnemie==0){
								running = 0; 
								SDL_Log("Victoire");
							}
						}

					}
					

				}
		
			}
			
			/*SDL_Log("ICI 2 ");*/
			SDL_RenderPresent(renderer); //Taille fenetre 1847 / 1015
			while(SDL_PollEvent(&e)) { 
				switch(e.type) { 
					case SDL_QUIT: 
						vague=MAX_Vague;
						running = 0; 
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
								case 0:running=SDL_FALSE;vague=MAX_Vague;break;
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
											timer[nb_timer]=SDL_AddTimer(1000,attendre,&(hero1->cooldown));
											nb_timer++;
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
											timer[nb_timer]=SDL_AddTimer(1000,attendre,&(hero2->cooldown));
											nb_timer++;
											tabHero->tab[nbCaseUse]->coordX = e.button.x;
											tabHero->tab[nbCaseUse]->coordY = e.button.y;
											tabHero->tab[nbCaseUse]->Hero = hero2;
											joueur->argent -= hero2->prix;
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
											timer[nb_timer]=SDL_AddTimer(1000,attendre,&(hero3->cooldown));
											SDL_Log("%d",hero3->cooldown);
											nb_timer++;
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

		vague++;
	}
	

	
	for(int i=0;i<nb_timer;i++){
		SDL_RemoveTimer(timer[i]);
	}
	SDL_DestroyTexture(case1);
	SDL_DestroyTexture(case2);
	SDL_DestroyTexture(case3);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(hud);
	SDL_DestroyTexture(pause);
	SDL_DestroyTexture(textHero1);
	SDL_DestroyTexture(textHero2);
	SDL_DestroyTexture(textHero3);
	SDL_DestroyTexture(texte);
	SDL_DestroyTexture(boule);

	detruireHero(&hero1);
	detruireHero(&hero2);
	detruireHero(&hero3);

	detruire_joueur(joueur);

	int i=0;
	for(i=0;i<MAXHERO;i++){
		free(lesHeros[i]);
		free(tabHero->tab[i]);
	}
	

    return 0;
}
