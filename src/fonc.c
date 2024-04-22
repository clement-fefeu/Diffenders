#include "../lib/fonc.h"

//
//  fonc.c
//
//  Created by Gabriel Dubois.
/**
 *  \file fonc.c
 * \brief Programme principal
 * \details Fichier qui contient toutes les fonction pour l'affichage.
 * \author Gabriel Dubois
*/

/**
 * @brief Initialise la fenêtre et le renderer SDL.
 * 
 * @param window Pointeur vers la fenêtre SDL.
 * @param renderer Pointeur vers le renderer SDL.
 * @param w La largeur de la fenêtre.
 * @param h La hauteur de la fenêtre.
 * @return int Retourne 0 en cas de réussite, -1 en cas d'échec.
 */
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

/**
 * @brief Charge une image dans une texture SDL.
 * 
 * @param path Le chemin vers l'image à charger.
 * @param renderer Le renderer SDL.
 * @return SDL_Texture* La texture de l'image chargée.
 */
void loadImage(const char path[], SDL_Renderer *renderer,SDL_Texture **texture)
{
    SDL_Surface *tmp = NULL;
    tmp = IMG_Load(path);
    if(!tmp)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
    }
    *texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == *texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
    }
}
/**
 * @brief Crée une surface à partir d'une texture SDL.
 * 
 * @param texture La texture SDL.
 * @return SDL_Surface* La surface créée.
 */
SDL_Surface *createSurfaceFromTexture(SDL_Texture *texture)
{
    Uint32 format_pixels;
    SDL_Surface *surface = NULL;
    void *pixels = NULL;
    int pitch, w, h;

    if (SDL_QueryTexture(texture, &format_pixels, NULL, &w, &h) != 0)
    {
        fprintf(stderr, "SDL_QueryTexture: %s.\n", SDL_GetError());
        goto query_texture_fail;
    }

    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0)
    {
        fprintf(stderr, "SDL_LockTexture: %s.\n", SDL_GetError());
        goto lock_texture_fail;
    }

    surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 32, w * sizeof(Uint32),format_pixels);
    if(NULL == surface)
        fprintf(stderr, "Erreur SDL_CreateSurfaceFrom : %s.\n", SDL_GetError());

    SDL_UnlockTexture(texture);
lock_texture_fail:
query_texture_fail:
    return surface;
}

/**
 * @brief Initialise l'icône de la fenêtre.
 * 
 * @param window La fenêtre SDL.
 */
void init_icon(SDL_Window *window){
    SDL_Surface *surface = IMG_Load("../img/tower_def.jpg");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}

/**
 * @brief Charge un texte dans une texture SDL.
 * 
 * @param renderer Le renderer SDL.
 * @param text Le texte à afficher.
 * @param taille_text La taille du texte.
 * @return SDL_Texture* La texture du texte chargé.
 */
SDL_Texture *load_text(SDL_Renderer *renderer,char *text,int taille_text,SDL_Color textColor){
    SDL_Texture *texture = NULL;

	if( TTF_Init() == -1 ) { 
		return 0; 
	}
	TTF_Font *police = NULL;
	police=TTF_OpenFont("../font/Quick_Peach.ttf",taille_text);
	if( police == NULL ) { 
		return 0; 
	}
	SDL_Surface *texte=TTF_RenderText_Blended(police, text, textColor) ;

    texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    TTF_CloseFont(police);
    return texture;
}



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