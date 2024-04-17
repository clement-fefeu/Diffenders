#include "../lib/base_struct.h"
#include "../lib/fonc.h"

char * nomHero[8] = {"Skarn","Pof","Roy","Erjar","Ranov","Xoras","Avban","Vzura"};
int degatHero[8] = {100,100,150,300,250,400,800,50};
int typeHero[8] = {3,3,3,3,3,3,3,3};
char * nomTypeHero[8] = {"Direct Hit","Direct Hit","Direct Hit","Direct Hit","Direct Hit","Direct Hit","Direct Hit","Direct Hit"};

ennemie_t * initialise_enemie(){     //fonction qui créér un ennemie.
    ennemie_t * enemieTemp = malloc(sizeof(ennemie_t));

    int pv;

    pv = 100;
    enemieTemp->nom = "Alien Soldier";
    enemieTemp->pv = pv;

    return enemieTemp;
}

void afficheEnem(ennemie_t * ennemie){
    printf(" Nom -> %s | Point de vie -> %d \n",ennemie->nom,ennemie->pv);
}

int detruireEnem(ennemie_t **  ennemie){ //Fonctions de destruction des ennemie créer.
    free((*ennemie));
    (*ennemie) = NULL;
    return 1;
}

hero_t * initialise_hero(int nb){
    hero_t * heroTemp = malloc(sizeof(hero_t));
    int degat;

    heroTemp->nom = nomHero[nb];
    heroTemp->degat = degatHero[nb];
    heroTemp->typehero.idenType = typeHero[nb];
    heroTemp->typehero.nom = nomTypeHero[nb];
    heroTemp->prix= 250;
    
    return heroTemp;
}

void afficheHero(hero_t * hero){
    printf("Nom -> %s | Dégat -> %d | Type -> %s \n",hero->nom,hero->degat,hero->typehero.nom);
}

int detruireHero(hero_t **  hero){ //Fonctions de destruction des ennemie créer.
    free((*hero));
    (*hero) = NULL;
    return 1;
}

listEnemie_t * vagueEnemie(int vague){
    int enemieVague = N;
    int totalEnemie = enemieVague * vague;
    listEnemie_t * vagueTemp = malloc(sizeof(listEnemie_t));
    vagueTemp->enemies = malloc(sizeof(ennemie_t)*(totalEnemie));
    ennemie_t * temp = NULL;
    
    
    vagueTemp->nbVague = vague;

    for(int i = 0; i < totalEnemie ; i++){
    temp = initialise_enemie();
    vagueTemp->enemies[i] = temp;
    vagueTemp->enemies[i]->pv += (((vagueTemp->enemies[i]->pv)/2)*vague); 
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

player_t * initialise_joueur(){
    player_t * joueur = malloc(sizeof(player_t));

    int tab[TailleMap][TailleMap];

    joueur->argent = 1000;
    
    joueur->base = malloc(sizeof(base_t));
}