#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../lib/base_struct.h"

char * nomHero[8] = {"Skarn","Pof","Roy","Erjar","Ranov","Xoras","Avban","Vzura"};
int degatHero[8] = {100,0,50,35,250,120,75,5};
int typeHero[8] = {3,1,2,4,3,4,2,1};
char * nomTypeHero[8] = {"Direct Hit","Support","AOE","DOT","Direct Hit","DOT","AOE","Support"};

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

hero_t * initialise_hero(int nb){
    hero_t * heroTemp = malloc(sizeof(hero_t));
    int degat;

    heroTemp->nom = nomHero[nb];
    heroTemp->degat = degatHero[nb];
    heroTemp->typehero.idenType = typeHero[nb];
    heroTemp->typehero.nom = nomTypeHero[nb];
    
    return heroTemp;
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

totalHero_t * equipeHero(int nbHero, int nb){
    hero_t * temp = NULL;
    totalHero_t * equipeTemp = malloc(sizeof(totalHero_t));
    equipeTemp->hero = malloc(sizeof(hero_t)*nbHero);

    for(int i = 0; i < nbHero ; i++){
        temp = initialise_hero(nb);
        equipeTemp->hero[i] = temp;
    }
    return equipeTemp;
}

void afficherAllHero(totalHero_t * allHero , int nbHero){
    for(int i = 0 ; i<nbHero ; i++){ //oui
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


int genereMapBeta(int tab[TailleMap][TailleMap]){
    int i;
    int j;
    for(i = 0 ; i< TailleMap ; i++){
        for(j = 0 ; j < TailleMap ; j++){
            tab[i][j] = 0;
        }
    }
    return 1;
}

int genereMapVisuBeta(int tab[TailleMap][TailleMap],char tabVisu[TailleMap][TailleMap]){
    int i = 0;
    for(i ; i<TailleMap ; i++){
        for(int j = 0 ; j  < TailleMap; j++){
            if(tab[i][j] == 1){
                tabVisu[i][j] = 'B';
            }
            else{
                tabVisu[i][j] = '_';
            }
    }
}
return 1;
}


void afficherMap(char tab[TailleMap][TailleMap]){
    for(int i = 0; i < TailleMap ; i++){ 
        for(int j = 0 ; j < TailleMap ; j++){
            printf("%c | ",tab[i][j]);
        }
        printf("\n");
    }
}

base_t * genererBase(int tab[TailleMap][TailleMap]){
    int x;
    int y;

    base_t * baseTemp = malloc(sizeof(base_t));

    do{
    x = rand() % 30;
    printf("Le X = %d \n",x);
    if(x >= 20){
        y = rand() % 31;
    }
    }while(x<20);
    tab[y][x] = 1;
    baseTemp->pv = 1000;
    baseTemp->coordX = x;
    baseTemp->coordY = y;

    return baseTemp;
}

int detruireBase(base_t ** base){
    free(*base);
    (*base)=NULL;
}

int degatBase(base_t * base){
    int degat;
    printf("Indiquez les dégat que vous voullez infligé à la base :");
    scanf("%d",&degat);

    base->pv -= degat;

    return 1;
}

int actualiseBase(base_t * base){
    if(base->pv <= 0){
        printf("Vous avez perdu ! \n");
        return 0;
    }
    else{
        printf("Il vous reste %d pv \n",base->pv);
    }
    return 1;   
}

/*int jeu(){
    int vague = 4;
    int nbHero = 8;
    listEnemie_t * vagueEnem = NULL;
    totalHero_t * teamHero = NULL;
    hero_t * hero = NULL;
    base_t * base = NULL;
    int tab[TailleMap][TailleMap];
    char tabVisuelle[TailleMap][TailleMap];
    vagueEnem = vagueEnemie(vague);

    afficherListeEnem(vagueEnem,vague);

    detruireListe(&vagueEnem,vague);

    teamHero = equipeHero(nbHero);

    afficherAllHero(teamHero,nbHero);

    detruireAllHero(&teamHero,nbHero);

    genereMapBeta(tab);

    base = genererBase(tab);

    genereMapVisuBeta(tab,tabVisuelle);

    printf("\n");

    afficherMap(tabVisuelle);

    for(int i = 0 ; i < 4 ; i++){

        degatBase(base);

    if(actualiseBase(base) == 0){
        detruireBase(&base);
        return 0;
    }
    }
    return 1;
}

int main(){     //Programme principal
    srand( time( NULL ) );

    jeu();

}
*/