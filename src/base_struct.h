#include <stdlib.h>
#include <stdio.h>

typedef struct enemie_s enemie_t;
typedef struct hero_s hero_t;
typedef struct typeEnemie_s typeEnemie_t;
typedef struct vague_s vague_t;
typedef struct listEnemie_s listEnemie_t;
typedef struct typeHero_s typeHero_t;
typedef struct totalHero_s totalHero_t;
typedef struct base_s base_t;
typedef struct joueur_s joueur_t;


struct typeEnemie_s{
    char * nom;
    int idenType;
};

struct typeHero_s{
    char * nom;
    int idenType;
};

struct enemie_s{
    char * nom;
    int pv;
    typeEnemie_t typeenemie;

};

struct hero_s{
    char * nom;
    int degat;
    typeHero_t typehero;


};

struct listEnemie_s{
    int nbVague;
    enemie_t ** enemies;
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

struct joueur_t{
    int pointVie;
    int argent;
    //inventaire
    //capacité Ultime
    base_t * base;

};


enemie_t * initialise_enemie();
int detruireEnem(enemie_t **  enemie);
listEnemie_t * vagueEnemie(int vague);

hero_t * initialise_hero();
void afficheHero(hero_t * hero);
int detruireHero(hero_t **  hero);

listEnemie_t * vagueEnemie(int vague);
void afficherListeEnem(listEnemie_t * liste,int vague);
int detruireListe(listEnemie_t ** liste,int vague);

totalHero_t * equipeHero(int nbHero);
void afficherAllHero(totalHero_t * allHero , int nbHero);
int detruireAllHero(totalHero_t ** allHero,int nbHero);

int jeu();