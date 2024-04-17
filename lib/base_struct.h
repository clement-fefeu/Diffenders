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
typedef struct vague_s vague_t;
typedef struct listEnemie_s listEnemie_t;
typedef struct typeHero_s typeHero_t;
typedef struct totalHero_s totalHero_t;
typedef struct base_s base_t;
typedef struct caseHero_s caseHero_t;
typedef struct tabCase_s tabCase_t;
typedef struct player_s player_t;


struct typeEnemie_s{
    char * nom;
    int idenType;
};

struct typeHero_s{
    char * nom;
    int idenType;
};

struct ennemie_s{
    char * nom;
    int pv;
<<<<<<< HEAD
    int sensX;
    int sensY;
=======
>>>>>>> bb4533840c98cd13ecf720c373290069aab3b84f
    SDL_Rect imgDestRectEnnemie;
    SDL_Texture *texture;


};

struct hero_s{
    char * nom;
    int degat;
    int prix;
    typeHero_t typehero;


};

struct listEnemie_s{
    int nbVague;
    ennemie_t ** enemies;
};

struct totalHero_s{
    hero_t ** hero;
};

struct vague_s{
    int numero;
    listEnemie_t listEnem;
};

struct base_s{
    int pv;
    int coordX;
    int coordY;
};

struct caseHero_s{
    int coordX;
    int coordY;
    hero_t * Hero;
};

struct tabCase_s{
    caseHero_t * tab[MAXHERO];
};

struct player_s{
    int argent;
    base_t * base;
};

ennemie_t * initialise_enemie();         //Fonction pour la structure enemie_t
int detruireEnem(ennemie_t **  ennemie);
listEnemie_t * vagueEnemie(int vague);

hero_t * initialise_hero(int nb);             //Fonctions pour la structure hero_t
void afficheHero(hero_t * hero);
int detruireHero(hero_t **  hero);

listEnemie_t * vagueEnemie(int vague);              //Fonction pour gérer la liste d'ennemie (le nb par vague)
void afficherListeEnem(listEnemie_t * liste,int vague);
int detruireListe(listEnemie_t ** liste,int vague);

totalHero_t * equipeHero(int nbHero, int nb);               //Fonction pour le total de héro sur le plateau
void afficherAllHero(totalHero_t * allHero , int nbHero);   
int detruireAllHero(totalHero_t ** allHero,int nbHero);

int genereMapBeta(int tab[TailleMap][TailleMap]);       //Fonction génération de la map
int genereMapVisuBeta(int tab[TailleMap][TailleMap],char tabVisu[TailleMap][TailleMap]);
void afficherMap(char tab[TailleMap][TailleMap]);

base_t * genererBase(int tab[TailleMap][TailleMap]);       //Generation de la base
int detruireBase(base_t ** base);
int degatBase(base_t * base);
int actualiseBase(base_t * base);

player_t * initialise_joueur();