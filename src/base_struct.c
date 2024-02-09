#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "base_struct.h"

#define N 6

enemie_t * initialise_enemie(){     //fonction qui créér un enemie.
    enemie_t * enemieTemp = malloc(sizeof(enemie_t));

    enemieTemp->typeenemie.idenType = rand() % 3 + 1;
    int pv;

    if(enemieTemp->typeenemie.idenType == 1){
    pv = 50;
    enemieTemp->nom = "Alien Scout";
    enemieTemp->pv = pv;
    enemieTemp->typeenemie.nom = "Rapide";
    }
    else if(enemieTemp->typeenemie.idenType == 2){
    pv = 100;
    enemieTemp->nom = "Alien Soldier";
    enemieTemp->pv = pv;
    enemieTemp->typeenemie.nom = "Soldat";
    }
    else if(enemieTemp->typeenemie.idenType == 3){
    pv = 200;
    enemieTemp->nom = "Alien Tank";
    enemieTemp->pv = pv;
    enemieTemp->typeenemie.nom = "Tank";
    }

    return enemieTemp;
}

void afficheEnem(enemie_t * enemie){
    printf(" Nom -> %s | Point de vie -> %d | Type -> %s \n",enemie->nom,enemie->pv,enemie->typeenemie.nom);
}

int detruireEnem(enemie_t **  enemie){ //Fonctions de destruction des enemie créer.
    free((*enemie));
    (*enemie) = NULL;
    return 1;
}

hero_t * initialise_hero(){
    hero_t * heroTemp = malloc(sizeof(hero_t));

    heroTemp->typehero.idenType = rand() % 4+1;
    int degat;

    if(heroTemp->typehero.idenType == 1){
    degat = 0;
    heroTemp->nom = "Hero Support";
    heroTemp->degat = degat;
    heroTemp->typehero.nom = "Support";
    }
    else if(heroTemp->typehero.idenType == 2){
    degat = rand() % 100+20;
    heroTemp->nom = "Hero de Zone";
    heroTemp->degat = degat;
    heroTemp->typehero.nom = "AOE (Area Of Effect)";
    }
    else if(heroTemp->typehero.idenType == 3){
    degat  = rand() % 200+60;
    heroTemp->nom = "Hero attaquant direct";
    heroTemp->degat = degat;
    heroTemp->typehero.nom = "DH (Direct Hit)";
    }
    else if(heroTemp->typehero.idenType == 4){
    degat  = rand() % 140+40;
    heroTemp->nom = "Hero attaquant sur la durée";
    heroTemp->degat = degat;
    heroTemp->typehero.nom = "DOT (Damage Over Time)";
    }
}

void afficheHero(hero_t * hero){
    printf("Nom -> %s | Dégat -> %d | Type -> %s \n",hero->nom,hero->degat,hero->typehero.nom);
}

int detruireHero(hero_t **  hero){ //Fonctions de destruction des enemie créer.
    free((*hero));
    (*hero) = NULL;
    return 1;
}

listEnemie_t * vagueEnemie(int vague){
    int enemieVague = N;
    int totalEnemie = enemieVague * vague;
    listEnemie_t * vagueTemp = malloc(sizeof(listEnemie_t));
    vagueTemp->enemies = malloc(sizeof(enemie_t)*(totalEnemie));
    enemie_t * temp = NULL;
    
    
    vagueTemp->nbVague = vague;

    for(int i = 0; i < totalEnemie ; i++){
    temp = initialise_enemie();
    vagueTemp->enemies[i] = temp;
    }


    return vagueTemp;
} 

void afficherListeEnem(listEnemie_t * liste,int vague){
    int totaleVague = N * vague;
    for(int i = 0; i< totaleVague; i++){
        printf("%d : ",i);
        afficheEnem(liste->enemies[i]);
    }
}  

int detruireListe(listEnemie_t ** liste,int vague){
    int totaleVague = N * vague;
    for(int i = 0; i < totaleVague ; i++){
        detruireEnem(&(*liste)->enemies[i]); 
        (*liste)->enemies[i] = NULL;
    }
    free((*liste)->enemies);
    (*liste)->enemies = NULL;
    free((*liste));
    (*liste)=NULL;
    return 1;
}

totalHero_t * equipeHero(int nbHero){
    hero_t * temp = NULL;
    totalHero_t * equipeTemp = malloc(sizeof(totalHero_t));
    equipeTemp->hero = malloc(sizeof(hero_t)*nbHero);

    for(int i = 0; i < nbHero ; i++){
        temp = initialise_hero();
        equipeTemp->hero[i] = temp;
    }
    return equipeTemp;
}

void afficherAllHero(totalHero_t * allHero , int nbHero){
    for(int i = 0 ; i<nbHero ; i++){
        afficheHero(allHero->hero[i]);
    }
}

int detruireAllHero(totalHero_t ** allHero,int nbHero){
    for(int i = 0; i < nbHero ; i++){
        detruireHero(&(*allHero)->hero[i]);
        (*allHero)->hero[i] = NULL;
    }
    free((*allHero)->hero);
    (*allHero)->hero = NULL;
    free(*allHero);
    (*allHero)=NULL;
}



int jeu(){
    int vague = 4;
    int nbHero = 8;
    listEnemie_t * vagueEnem = NULL;
    totalHero_t * teamHero = NULL;
    hero_t * hero = NULL;
    vagueEnem = vagueEnemie(vague);

    afficherListeEnem(vagueEnem,vague);

    detruireListe(&vagueEnem,vague);

    teamHero = equipeHero(nbHero);

    afficherAllHero(teamHero,nbHero);

    detruireAllHero(&teamHero,nbHero);



}

int main(){     //Programme principal
    srand( time( NULL ) );

    jeu();

}
