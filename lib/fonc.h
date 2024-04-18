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

#define ABS 30
#define ORD 15
#define NB_ENTREE 1

#define MAX_Vague 5
/**
 * @brief Structure représentant les entrées utilisateur.
 */
struct Input {
    SDL_bool key[SDL_NUM_SCANCODES]; /**< Les touches du clavier. */
    SDL_bool quit; /**< Booléen pour quitter le jeu. */
    int x, y, xrel, yrel; /**< Coordonnées de la souris et de son déplacement. */
    int xwheel, ywheel; /**< Position de la molette de la souris. */
    SDL_bool mouse[6]; /**< Les boutons de la souris. */
};

/*structure de coordonnée pour obtenir un point précis dans le tableau*/
typedef struct coord_s{
  int x;
  int y;
} coord_t;

/* structure de tableau de coordonné retournant un chemin que peuvent suivrent les ennemis*/
typedef struct chemin_s{
  coord_t chemin[(ABS)+(ORD)];
} chemin_t;

/*structure de definition des projectile*/
typedef struct proj_s{
  int damage;
  int sensY;
  SDL_Rect coor;
  SDL_Texture * text;
}proj_t;

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
 * @brief Teste si un point est à l'intérieur d'un rectangle.
 * 
 * @param point Le point à tester.
 * @param rect Le rectangle dans lequel tester le point.
 * @return SDL_bool Retourne SDL_TRUE si le point est à l'intérieur du rectangle, sinon SDL_FALSE.
 */
SDL_bool test(SDL_Point point, SDL_Rect rect);

/**
 * @brief Change la couleur de la fenêtre.
 * 
 * @param renderer Le renderer SDL.
 * @param color La couleur à appliquer.
 * @return int Retourne 0 en cas de réussite, -1 en cas d'échec.
 */
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

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
 * @brief Crée une texture de dégradé pour le fond.
 * 
 * @param renderer Le renderer SDL.
 * @return SDL_Texture* La texture du dégradé.
 */
SDL_Texture *degrade(SDL_Renderer *renderer);

/**
 * @brief Modifie un pixel dans une surface SDL.
 * 
 * @param surface La surface SDL.
 * @param r La composante rouge du pixel.
 * @param g La composante verte du pixel.
 * @param b La composante bleue du pixel.
 * @param a La composante alpha du pixel.
 * @param x La coordonnée en x du pixel.
 * @param y La coordonnée en y du pixel.
 */
void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y);

/**
 * @brief Crée une surface à partir d'une texture SDL.
 * 
 * @param texture La texture SDL.
 * @return SDL_Surface* La surface créée.
 */
SDL_Surface *createSurfaceFromTexture(SDL_Texture *texture);

/**
 * @brief Met à jour les événements d'entrée utilisateur.
 * 
 * @param input Structure d'entrée utilisateur.
 */
void updateEvent(struct Input *input);

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
 * @brief Crée la carte du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param tab Tableau représentant la carte.
 */
chemin_t creation_map(SDL_Renderer *renderer, int tab[ABS][ORD]);

/**
 * @brief Affiche la carte du jeu.
 * 
 * @param tab Tableau représentant la carte.
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 */
void affiche_map_2(int tab[ABS][ORD], SDL_Renderer *renderer, SDL_Window *window);

/**
 * @brief La fonction principale du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 * @return int Retourne 0 en cas de réussite.
 */
int jeu(SDL_Renderer *renderer, SDL_Window *window);