#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

extern DECLSPEC int SDLCALL TTF_Init(void);

#define WIDTH 255
#define HEIGHT 255
#define SDL_BUTTON_LEFT     1
#define SDL_BUTTON_MIDDLE   2
#define SDL_BUTTON_RIGHT    3
#define SDL_BUTTON_X1       4
#define SDL_BUTTON_X2       5
#define TTF_GetError    SDL_GetError
#define WIDTHSCREEN 1600 
#define HEIGHTSCREEN 900 
#define TOTAL_POINTS 5000 



/**
 * @brief Charge un texte dans une texture SDL.
 * 
 * @param renderer Le renderer SDL.
 * @param text Le texte à afficher.
 * @param taille_text La taille du texte.
 * @return SDL_Texture* La texture du texte chargé.
 */
SDL_Texture *load_text(SDL_Renderer *renderer, char *text, int taille_text);

/**
 * @brief Initialise la fenêtre et le renderer SDL.
 * 
 * @param window Pointeur vers la fenêtre SDL.
 * @param renderer Pointeur vers le renderer SDL.
 * @param w La largeur de la fenêtre.
 * @param h La hauteur de la fenêtre.
 * @return int Retourne 0 en cas de réussite, -1 en cas d'échec.
 */
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

/**
 * @brief Charge une image dans une texture SDL.
 * 
 * @param path Le chemin vers l'image à charger.
 * @param renderer Le renderer SDL.
 * @return SDL_Texture* La texture de l'image chargée.
 */
void loadImage(const char path[], SDL_Renderer *renderer,SDL_Texture **texture);

/**
 * @brief Crée une surface à partir d'une texture SDL.
 * 
 * @param texture La texture SDL.
 * @return SDL_Surface* La surface créée.
 */
SDL_Surface *createSurfaceFromTexture(SDL_Texture *texture);


/**
 * @brief Initialise l'icône de la fenêtre.
 * 
 * @param window La fenêtre SDL.
 */
void init_icon(SDL_Window *window);

/**
 * @brief Affiche le menu du jeu.
 * 
 * @return int Retourne l'option sélectionnée dans le menu.
 */
int menu();

/**
 * @brief Affiche les paramètres du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 * @param largeur La largeur de l'écran.
 * @param hauteur La hauteur de l'écran.
 * @param background La texture du fond d'écran.
 * @return int Retourne l'option sélectionnée dans les paramètres.
 */
int param(SDL_Renderer *renderer, SDL_Window *window, int largeur, int hauteur, SDL_Texture *background);


/**
 * @brief La fonction principale du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 * @return int Retourne 0 en cas de réussite.
 */
int jeu(SDL_Renderer *renderer, SDL_Window *window);

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
int param(SDL_Renderer *renderer,SDL_Window *window,int largeur, int hauteur,SDL_Texture *background);

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
void accueil(SDL_Renderer *renderer,int gris,SDL_Texture *quit ,SDL_Texture *play ,SDL_Texture*background,SDL_Texture*quit_des,SDL_Texture*play_des,SDL_Texture*parametre,SDL_Texture*parametre_des,int largeur, int hauteur);

/**
 * @brief Affiche le menu principal.
 *
 * Affiche le menu principal avec les boutons jouer, paramètres et quitter.
 *
 * @return Le statut de sortie.
 */
int menu();