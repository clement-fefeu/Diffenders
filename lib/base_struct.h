#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define MAXHERO 10
#define N 6
#define TailleMap 30

#define MAXENNEMIE 30

typedef struct ennemie_s ennemie_t;
typedef struct hero_s hero_t;
typedef struct typeEnemie_s typeEnemie_t;
typedef struct typeHero_s typeHero_t;
typedef struct caseHero_s caseHero_t;
typedef struct tabCase_s tabCase_t;
typedef struct player_s player_t;

#define ABS 30
#define ORD 15
#define NB_ENTREE 1

#define MAX_Vague 15

/**
 * @struct coord_t
 * @brief structure de coordonnée pour obtenir un point précis dans le tableau.
 */
typedef struct coord_s{
  int x;
  int y;
} coord_t;

/**
 * @struct chemin_t
 * @brief structure de tableau de coordonné retournant un chemin que peuvent suivrent les ennemis.
 */
typedef struct chemin_s{
  coord_t chemin[(ABS)+(ORD)];
} chemin_t;


/**
 * @struct heroText_s
 * @brief Structure représentant la texture et la position d'un héros.
 */
typedef struct heroText_s {
	SDL_Texture *texture; /**< La texture du héros. */
	SDL_Rect rectHero;    /**< La position et la taille du héros. */
} heroText_t;

/**
 * @struct typeEnemie_t
 * @brief structure qui contient les informations d'un ennemi.
 */
struct typeEnemie_s{
    char * nom;
    int idenType;
};

/**
 * @struct typeHero_t
 * @brief structure qui contient les informations d'un hero.
 */
struct typeHero_s{
    char * nom;
    int idenType;
};

/**
 * @struct ennemie_s
 * @brief structure d'ennemi.
 */
struct ennemie_s{
    char * nom;
    int pv;
    int palier;
    SDL_Rect imgDestRectEnnemie;
    SDL_Texture *texture;
};

/**
 * @struct hero_t
 * @brief structure de hero.
 */
struct hero_s{
    char * nom;
    int degat;
    int cooldown;
    int etat;
    int prix;
    typeHero_t typehero;
};


/**
 * @struct caseHero_t
 * @brief structure de coordonnée pour les heros.
 */
struct caseHero_s{
    int coordX;
    int coordY;
    hero_t * Hero;
};

/**
 * @struct tabCase_t
 * @brief structure qui contient les cases ou sont posé les héros.
 */
struct tabCase_s{
    caseHero_t * tab[MAXHERO];
};

/**
 * @struct player_t
 * @brief structure pour le joueur.
 */
struct player_s{
    int argent;
};

/**
 * @brief Affiche la carte du jeu.
 * 
 * @param tab Tableau représentant la carte.
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 */
void affiche_map_2(int tab[ABS][ORD], SDL_Renderer *renderer, SDL_Window *window);

/**
 * @brief Crée la carte du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param tab Tableau représentant la carte.
 */
chemin_t creation_map(SDL_Renderer *renderer, int tab[ABS][ORD]);

/**
 * @brief Initialise un ennemi
 * @return Pointeur vers l'ennemi initialisé
 */
ennemie_t * initialise_enemie();         //Fonction pour la structure enemie_t

/**
 * @brief Détruit un ennemi
 * @param ennemie Pointeur vers le pointeur de l'ennemi
 * @return 1 si la destruction réussit, sinon 0
 */
int detruireEnem(ennemie_t **  ennemie);

/**
 * @brief Initialise un héros
 * @param nb Indice du héros
 * @return Pointeur vers le héros initialisé
 */
hero_t * initialise_hero(int nb);             //Fonctions pour la structure hero_t

/**
 * @brief Affiche les informations d'un héros
 * @param hero Pointeur vers le héros
 */
void afficheHero(hero_t * hero);

/**
 * @brief Détruit un héros
 * @param hero Pointeur vers le pointeur du héros
 * @return 1 si la destruction réussit, sinon 0
 */
int detruireHero(hero_t **  hero);

/**
 * @brief initialise le joueur
 * @param joueur Pointeur vers le pointeur du joueur
 * @return le joueur créé
 */
player_t * initialise_joueur();

/**
 * @brief detruit la structure joueur
 * @param joueur 
 */
void detruire_joueur(player_t *joueur);

/**
 * @brief Affiche le montant d'argent et une texture donnée à l'écran.
 * 
 * @param renderer Le renderer SDL.
 * @param hauteur La hauteur de l'écran.
 * @param largeur La largeur de l'écran.
 * @param texte La texture à afficher.
 */
void affiche_argent(SDL_Renderer *renderer,int hauteur,int largeur,SDL_Texture *texte);

/**
 * @brief Affiche le montant de point de vie.
 * 
 * @param renderer Le renderer SDL.
 * @param hauteur La hauteur de l'écran.
 * @param largeur La largeur de l'écran.
 * @param texte La texture à afficher.
 */
void affiche_PV(SDL_Renderer *renderer,int hauteur,int largeur,SDL_Texture *texte);

/**
 * @brief Affiche le prix des heros.
 * 
 * @param renderer Le renderer SDL.
 * @param hauteur La hauteur de l'écran.
 * @param largeur La largeur de l'écran.
 * @param texte La texture à afficher.
 * @param posX La largeur de l'écran.
 * @param posY La texture à afficher.
 */
void affiche_Prix(SDL_Renderer *renderer,int hauteur,int largeur,SDL_Texture *texte,int posX,int posY);

/**
 * @brief Attend un certain temps avant de faire une action.
 * 
 * @param interval Le temps à attendre.
 * @param parametre La valeur à modifier.
 */
Uint32 attendre(Uint32 interval,void* parametre);

/**
 * @brief Avance de droite à gauche la texture de l'ennemi.
 * 
 * @param ennemie L'ennemie a faire avancer.
 * @param nbEnnemie Le nombre d'ennemi.
 * @param indice L'indice de l'ennemi actuel.
 * @param indiceChemin L'indice de la position du chemin.
 * @param coord Coordonnées.
 * @param largeur Largeur de l'écran.
 * @param hauteur Hauteur de l'écran.
 */
ennemie_t * avancerHorizontal(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord,int largeur,int hauteur);

/**
 * @brief Avance de gauche à droite la texture de l'ennemi.
 * 
 * @param ennemie L'ennemie a faire avancer.
 * @param nbEnnemie Le nombre d'ennemi.
 * @param indice L'indice de l'ennemi actuel.
 * @param indiceChemin L'indice de la position du chemin.
 * @param coord Coordonnées.
 * @param largeur Largeur de l'écran.
 * @param hauteur Hauteur de l'écran.
 */
ennemie_t * reculerHorizontal(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord,int largeur,int hauteur);

/**
 * @brief Avance de haut en bas la texture de l'ennemi.
 * 
 * @param ennemie L'ennemie a faire avancer.
 * @param nbEnnemie Le nombre d'ennemi.
 * @param indice L'indice de l'ennemi actuel.
 * @param indiceChemin L'indice de la position du chemin.
 * @param coord Coordonnées.
 * @param largeur Largeur de l'écran.
 * @param hauteur Hauteur de l'écran.
 */
ennemie_t * descendreVertical(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord,int largeur,int hauteur);

/**
 * @brief Avance de bas en haut la texture de l'ennemi.
 * 
 * @param ennemie L'ennemie a faire avancer.
 * @param nbEnnemie Le nombre d'ennemi.
 * @param indice L'indice de l'ennemi actuel.
 * @param indiceChemin L'indice de la position du chemin.
 * @param coord Coordonnées.
 * @param largeur Largeur de l'écran.
 * @param hauteur Hauteur de l'écran.
 */
ennemie_t * monterVertical(ennemie_t ** ennemie , int nbEnnemie,int indice,int indiceChemin,coord_t * coord,int largeur,int hauteur);

/**
 * @brief Affiche l'ennemi actuel.
 * 
 * @param renderer Le renderer SDL.
 * @param texture La texture a afficher.
 * @param drect La position de la texture.
 * @param w La largeur de l'écran.
 * @param h La texture à afficher.
 */
int appelTextEnnemie(SDL_Renderer * renderer, SDL_Texture *texture , SDL_Rect * drect , int *w,int * h);

/**
 * @brief La boucle principale du jeu.
 * 
 * @param renderer Le renderer SDL.
 * @param window La fenêtre SDL.
 * @return int Retourne 0 en cas de réussite.
 */
int jeu(SDL_Renderer *renderer,SDL_Window *window);

/**
 * @brief initialisation de matrice de map a 0
 * 
 * @param tab 
 */
void initialise(int tab[ABS][ORD]);

/**
 * @brief initialise la matrice de chemin a -1
 * 
 * @param pathfind 
 */
void init_chemin(chemin_t pathfind[NB_ENTREE+1]);

/**
 * @brief initialise la matrice de chemin a -1
 * 
 * @param pathfind 
 */
void init_chemin2(chemin_t * pathfind);

/**
 * @brief pose la base aléatoirement sur la carte
 * 
 * @param a 
 * @param b 
 * @param tab 
 */
void genere_base(int *a, int *b, int tab[ABS][ORD]);

/**
 * @brief verifie qu'une case est vide
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @return int 
 */
int vide(int a, int b, int tab[ABS][ORD]);

/**
 * @brief verifie si une case du bord donnée en parametre n'est pas a coté d'une autre
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @return int 
 */
int adjacent(int a, int b, int tab[ABS][ORD]);

/**
 * @brief verifie que la case du bord n'est pas en face ou diagonal d'une case non-vide 
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @return int 
 */
int devant(int a, int b, int tab[ABS][ORD]);

/**
 * @brief retourne le resultat du calcul de fonction pour savoir si l'entree est acceptable
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @return int 
 */
int test_bord(int a, int b, int tab[ABS][ORD]);

/**
 * @brief fonction de calculs des entree des ennemis retourne en parametre les coordonné
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @param c 
 * @param d 
 */
void calc_bord(int a, int b, int tab[ABS][ORD], int *c, int *d);

/**
 * @brief calcul les bord et met dans la matrice les coordonnees de ceux ci
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @param mat 
 */
void mat_bord(int a, int b, int tab[ABS][ORD], int mat[NB_ENTREE][2]);

/**
 * @brief retourne 1 si les coordonnees en parametre sont dans les chemins
 * 
 * @param x 
 * @param y 
 * @param pathfind 
 * @return int 
 */
int appartient(int x,int y, chemin_t pathfind[NB_ENTREE+1]);

/**
 * @brief remplace toute case n'etant ni base ni chemin ni entree par des 0
 * 
 * @param tab 
 * @param pathfind 
 * @param mat 
 */
void re_initialise(int tab[ABS][ORD],chemin_t pathfind[NB_ENTREE+1],int mat[NB_ENTREE][2]);

/**
 * @brief fonction d'ecriture d'un chemin dans le tableau
 * 
 * @param a 
 * @param b 
 * @param tab 
 * @param x 
 * @param y 
 */
void chemin(int a, int b, int tab[ABS][ORD], int x, int y);

/**
 * @brief ecriture de tout les chemin dans le tableau d'affichage des coordonnee de tout les chemins
 * 
 * @param a 
 * @param b 
 * @param pathfind 
 * @param x 
 * @param y 
 */
void pathfinding(int a, int b, chemin_t * pathfind, int x, int y);

/**
 * @brief ecriture du chemin entre le point central et la base dans le tableua d'affichage de coordonnee
 * 
 * @param a 
 * @param b 
 * @param pathfind 
 * @param x 
 * @param y 
 * @param i 
 * @return int 
 */
int pathfinding_base(int a, int b, chemin_t * pathfind, int x, int y,int i);

/**
 * @brief fonction de creation de chemin du point de rencontre des chemins jusqu'a la base
 * 
 * @param x 
 * @param y 
 * @param tab 
 * @param a 
 * @param b 
 * @param pathfind 
 */
void chemin_base(int x,int y,int tab[ABS][ORD],int a,int b,chemin_t * pathfind);

/**
 * @brief fonction de creation
 * 
 * @param a 
 * @param b 
 * @param mat 
 * @param tab 
 * @param pathfind 
 */
void croisee(int a, int b, int mat[NB_ENTREE][2], int tab[ABS][ORD],chemin_t pathfind[NB_ENTREE+1]);

/**
 * @brief calcul des point important de chemin
 * 
 * @param path 
 * @param repath 
 */
void repathing(chemin_t path[NB_ENTREE+1],chemin_t repath[NB_ENTREE+1]);

/**
 * @brief rassemble tout les point en un tab
 * 
 * @param import 
 * @param suite 
 */
void rassemble(chemin_t import[NB_ENTREE+1],chemin_t * suite);

/**
 * @brief fonction principale qui rassemble toute celle au dessus et les appelle dans le bon ordre
 * 
 * @param renderer 
 * @param tab 
 * @return chemin_t 
 */
chemin_t creation_map(SDL_Renderer *renderer,int tab[ABS][ORD]);