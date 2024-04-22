/**
 * @file   base_struct.c
 * @brief  Programme qui contient les fonctions et les structures du jeu
 */

#include "../lib/base_struct.h"
#include "../lib/fonc.h"

/** @brief Noms des héros */
char *nomHero[3] = {"Skarn", "Pof", "Roy"};

/** @brief Dégâts des héros */
int degatHero[3] = {80, 50, 200};

/** @brief Types des héros */
int typeHero[3] = {3, 3, 3};

/** @brief Prix des héros */
int prix[3] = {250, 500, 1000};

/** @brief Temps de recharge des héros */
int cooldown[3] = {1000, 500, 1500};

/** @brief Noms des types de héros */
char *nomTypeHero[3] = {"Direct Hit", "Direct Hit", "Direct Hit"};

ennemie_t *initialise_enemie() {
    ennemie_t *enemieTemp = malloc(sizeof(ennemie_t));
    int pv = 100;
    enemieTemp->nom = "Alien Soldier";
    enemieTemp->pv = pv;
    return enemieTemp;
}

int detruireEnem(ennemie_t **ennemie) {
    free((*ennemie));
    (*ennemie) = NULL;
    return 1;
}

hero_t *initialise_hero(int nb) {
    hero_t *heroTemp = malloc(sizeof(hero_t));
    heroTemp->nom = nomHero[nb];
    heroTemp->degat = degatHero[nb];
    heroTemp->cooldown = cooldown[nb];
    heroTemp->typehero.idenType = typeHero[nb];
    heroTemp->typehero.nom = nomTypeHero[nb];
    heroTemp->etat = 0;
    heroTemp->prix = prix[nb];
    return heroTemp;
}

void afficheHero(hero_t *hero) {
    printf("Nom -> %s | Dégat -> %d | Type -> %s \n", hero->nom, hero->degat, hero->typehero.nom);
}

int detruireHero(hero_t **hero) {
    free((*hero));
    (*hero) = NULL;
    return 1;
}

player_t * initialise_joueur(){
    player_t * joueur = malloc(sizeof(player_t));

    joueur->argent = 500;
    
    return joueur;
}

void detruire_joueur(player_t *joueur){
    
    free(joueur);
    joueur=NULL;

}