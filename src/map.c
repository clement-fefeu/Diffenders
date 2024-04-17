#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WIDTH 1600
#define HEIGHT 900
#define ABS 30
#define ORD 15
#define NB_ENTREE 1
#define NB_TOUR 10



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



/*retourne vrai si les deux entités sont rentrer en contact*/
int contact(coord_t proj,coord_t target){
  return ((proj.x==target.x)&&(proj.y==target.y));
}

/*fonction appellé pour que la tour tir toute les intervals micro secondes*/
Uint32 call(Uint32 interval,void * param){
  if((*(int*)param)==0){
    *(int*)param=1;
  }
  return interval;
}

/*fonction de test pour creer une tour si il y en a moins de 10toute les intervals micro secondes*/
Uint32 call2(Uint32 interval,void * param){
  if((*(int*)param)<10){
    (*(int*)param)++;
  }
  return interval;
}

/*affichage de la map dans le terminal
void affiche_map(int tab[ABS][ORD]) {
  for (int i = 0; i < ORD; i++) {
    for (int j = 0; j < ABS; j++) {
      switch (tab[j][i]) {
      case 0:
        printf(" H ");
        break;
      case 1:
        printf("BAS");
        break;
      case 2:
        printf("ENT");
        break;
      case 3:
        printf("ROU");
        break;
      default:
        printf("111");
        break;
      }
    }
    printf("\n");
  }
}*/

/*affichage de la map grace a la sdl et calcul de projectiles*/
void affiche_map_2(int tab[ABS][ORD],SDL_Renderer *renderer,SDL_Window *window) {
  SDL_Rect position;
  

  SDL_Surface * base =NULL;
  SDL_Texture * texture2= NULL;
  base = IMG_Load("../img/base.png");


  SDL_Surface * blanc =NULL;
  SDL_Texture * texture3= NULL;
  blanc = IMG_Load("../img/chemin.png");

  texture2=SDL_CreateTextureFromSurface(renderer,base);
  texture3=SDL_CreateTextureFromSurface(renderer,blanc);

  int larg,haut;
  SDL_GetWindowSize(window,&larg,&haut);
  

  for(int t =2;t>0;t--){
    position.x=0;
    position.y=0;
    for(int j=0;j<ORD;j++){
      for(int i=0;i<ABS;i++){
        switch(tab[i][j]){
          case 1:
            position.h=(haut-200)/ORD;
            position.w=larg/ABS;
            SDL_RenderCopy(renderer,texture2,NULL,&position);
            SDL_QueryTexture(texture2,NULL,NULL,&(position.w),&(position.h));
            break;;
          case 3:
            position.h=(haut-200)/ORD;
            position.w=larg/ABS;
            SDL_RenderCopy(renderer,texture3,NULL,&position);
            SDL_QueryTexture(texture3,NULL,NULL,&(position.w),&(position.h));
            break;;
        
        }
        position.x=position.x+larg/ABS;
      }
      //affichage ligne par ligne 
      position.y=position.y+(haut-200)/ORD;
      position.x=0;
    }
  }
  SDL_DestroyTexture(texture2);
  SDL_DestroyTexture(texture3);
  SDL_FreeSurface(blanc);
}

/*initialisation de matrice de map a 0*/
void initialise(int tab[ABS][ORD]) {
  int j, i;
  for (j = 0; j < ORD; j++) {
    for (i = 0; i < ABS; i++) {
      tab[i][j] = 0;
    }
  }
}

/*initialise la matrice de chemin a -1*/
void init_chemin(chemin_t pathfind[NB_ENTREE+1]){
  for(int i=0;i<(NB_ENTREE+1);i++){
    for(int j=0;j<((ORD)+(ABS));j++){
      pathfind[i].chemin[j].x=-1;
      pathfind[i].chemin[j].y=-1;
    }
  }
}

void init_chemin2(chemin_t * pathfind){
  for(int j=0;j<((ORD)+(ABS));j++){
    pathfind->chemin[j].x=-1;
    pathfind->chemin[j].y=-1;
  }
}

/*affichage dans le terminal des coordonnées des chemins vers la base
void affiche_chemin(chemin_t pathfind[NB_ENTREE+1]){
  for(int i=0;i<(NB_ENTREE+1);i++){
    for(int j=0;pathfind[i].chemin[j].x!=-1;j++){
      printf("|%d : %d",pathfind[i].chemin[j].x,pathfind[i].chemin[j].y);
    }
    printf("\n");
  }
}*/

void affiche_chemin2(chemin_t pathfind){
  for(int j=0;pathfind.chemin[j].x!=-1;j++){
    printf("|(%d : %d)|",(pathfind.chemin[j].x),(pathfind.chemin[j].y));
  }
  printf("\n");
}


/*pose la base aléatoirement sur la carte*/
void genere_base(int *a, int *b, int tab[ABS][ORD]) {
  int x = (rand() % (ABS - 2)) + 1;
  int y = (rand() % (ORD - 2)) + 1;
  tab[x][y] = 1;
  (*a) = x;
  (*b) = y;
}

/*verifie qu'une case est vide*/
int vide(int a, int b, int tab[ABS][ORD]) { 
  return tab[a][b] == 0;
}

/*verifie si une case du bord donnée en parametre n'est pas a coté d'une autre*/
int adjacent(int a, int b, int tab[ABS][ORD]) {
  if (a == 0) {
    if (b == 0) {
      return 0;
    }
    if (b == (ORD - 1)) {
      return 0;
    }
    return (vide(a, b - 1, tab) && vide(a, b + 1, tab));
  }
  if (a == (ABS - 1)) {
    if (b == 0) {
      return 0;
    }
    if (b == (ORD - 1)) {
      return 0;
    }
    return (vide(a, b - 1, tab) && vide(a, b + 1, tab));
  }
  return (vide(a - 1, b, tab) && vide(a + 1, b, tab));
}

/*verifie que la case du bord n'est pas en face ou diagonal d'une case non-vide */
int devant(int a, int b, int tab[ABS][ORD]) {
  if (a == 0) {
    if (b == 0) {
      return 0;
    }
    if (b == (ORD - 1)) {
      return 0;
    }
    return (vide(a + 1, b, tab) && vide(a + 1, b - 1, tab) &&
            vide(a + 1, b + 1, tab));
  }
  if (a == (ABS - 1)) {
    if (b == 0) {
      return 0;
    }
    if (b == (ORD - 1)) {
      return 0;
    }
    return (vide(a - 1, b - 1, tab) && vide(a - 1, b - 1, tab) &&
            vide(a - 1, b + 1, tab));
  }
  if (b == 0) {
    return (vide(a - 1, b + 1, tab) && vide(a + 1, b + 1, tab) &&
            vide(a, b + 1, tab));
  }
  if (b == (ORD - 1)) {
    return (vide(a - 1, b - 1, tab) && vide(a + 1, b - 1, tab) &&
            vide(a, b - 1, tab));
  }
  return 0;
}

/*retourne le resultat du calcul de fonction pour savoir si l'entree est acceptable*/
int test_bord(int a, int b, int tab[ABS][ORD]) {
  return adjacent(a, b, tab) && devant(a, b, tab) && (tab[a][b] == 0);
}

/*fonction de calculs des entree des ennemis retourne en parametre les coordonné*/
void calc_bord(int a, int b, int tab[ABS][ORD], int *c, int *d) {
  int x = 0, y = 0;
  do {
    x = 0;
    y = 0;
    if (a < ((ABS - 1) / 2)) {
      x = (rand() % (ABS / 2)) + ((ABS - 1) / 2);
      if (b < ((ORD - 1) / 2)) {
        if (x == ABS - 1) {
          y = (rand() % (ORD / 2)) + ((ORD - 1) / 2);
        } else {
          y = ORD - 1;
        }
      } else {
        if (x == 0) {
          y = 1 + (rand() % ((ORD - 1) / 2));
        } else {
          y = 0;
        }
      }
    } else {
      x = (rand() % ((ABS - 1) / 2));
      if (b < ((ORD - 1) / 2)) {
        if (x == 0) {
          y = (rand() % (ORD / 2)) + ((ORD - 1) / 2);
        } else {
          y = ORD - 1;
        }
      } else {
        if (x == 0) {
          y = 1 + (rand() % ((ORD - 1) / 2));
        } else {
          y = 0;
        }
      }
    }
  } while (!test_bord(x, y, tab));
  *c = x;
  *d = y;
}

/*calcul les bord et met dans la matrice les coordonnees de ceux ci*/
void mat_bord(int a, int b, int tab[ABS][ORD], int mat[NB_ENTREE][2]) {
  int x, y;
  for (int i = 0; i < NB_ENTREE; i++) {
    calc_bord(a, b, tab, &x, &y);
    tab[x][y] = 2;
    mat[i][0] = x;
    mat[i][1] = y;
  }
}

/*retourne 1 si les coordonnees en parametre sont dans les chemins*/
int appartient(int x,int y, chemin_t pathfind[NB_ENTREE+1]){
  for(int i=0;i<NB_ENTREE+1;i++){
    for(int j=0;j<(ABS)+(ORD);j++){
      if(pathfind[i].chemin[j].x==x && pathfind[i].chemin[j].y==y){
        return 1;
      }
    }
  }
  return 0;
}

/*remplace toute case n'etant ni base ni chemin ni entree par des 0*/
void re_initialise(int tab[ABS][ORD],chemin_t pathfind[NB_ENTREE+1],int mat[NB_ENTREE][2]) {
  int j, i;
  for (j = 0; j < ORD; j++) {
    for (i = 0; i < ABS; i++) {
      if(tab[i][j]<0 || tab[i][j]>3){
        tab[i][j]=0;
      }
      if(appartient(i,j,pathfind)==0){
        tab[i][j]=0;
      }
    }
  }
  for(i=0;i<NB_ENTREE;i++){
    tab[mat[i][0]][mat[i][1]]=2;
  }
}

/*fonction d'ecriture d'un chemin dans le tableau*/
void chemin(int a, int b, int tab[ABS][ORD], int x, int y) {
  if (b == 0) {
    for (b++; b < y; b++) {
      tab[a][b] = 3;
    }
  }
  if (b == (ORD - 1)) {
    for (b--; b > y; b--) {
      tab[a][b] = 3;
    }
  }
  if (a == 0) {
    a++;
  }
  if (a == (ABS - 1)) {
    a--;
  }
  for (; a < x; a++) {
    tab[a][b] = 3;
  }
  for (; a > x; a--) {
    tab[a][b] = 3;
  }
  for (; b < y; b++) {
    tab[a][b] = 3;
  }
  for (; b > y; b--) {
    tab[a][b] = 3;
  }
  tab[a][b] = 3;
}

/*ecriture de tout les chemin dans le tableau d'affichage des coordonnee de tout les chemins*/
void pathfinding(int a, int b, chemin_t * pathfind, int x, int y){
  int i=0;
  pathfind->chemin[i].x=a;
  pathfind->chemin[i].y=b;
  i++;
  if (b == 0) {
    for (b++; b < y; b++) {
      pathfind->chemin[i].x=a;
      pathfind->chemin[i].y=b;
      i++;
    }
  }
  if (b == (ORD - 1)) {
    for (b--; b > y; b--) {
      pathfind->chemin[i].x=a;
      pathfind->chemin[i].y=b;
      i++;
    }
  }
  if (a == 0) {
    a++;
  }
  if (a == (ABS - 1)) {
    a--;
  }
  for (; a < x; a++) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  for (; a > x; a--) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  for (; b < y; b++) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  for (; b > y; b--) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  pathfind->chemin[i].x=a;
  pathfind->chemin[i].y=b;
  i++;
}

/*ecriture du chemin entre le point central et la base dans le tableua d'affichage de coordonnee*/
int pathfinding_base(int a, int b, chemin_t * pathfind, int x, int y,int i){
  pathfind->chemin[i].x=a;
  pathfind->chemin[i].y=b;
  i++;
  if (b == 0) {
    for (b++; b < y; b++) {
      pathfind->chemin[i].x=a;
      pathfind->chemin[i].y=b;
      i++;
    }
  }
  if (b == (ORD - 1)) {
    for (b--; b > y; b--) {
      pathfind->chemin[i].x=a;
      pathfind->chemin[i].y=b;
      i++;
    }
  }
  if (a == 0) {
    a++;
  }
  if (a == (ABS - 1)) {
    a--;
  }
  for (; a < x; a++) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  for (; a > x; a--) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  for (; b < y; b++) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  for (; b > y; b--) {
    pathfind->chemin[i].x=a;
    pathfind->chemin[i].y=b;
    i++;
  }
  pathfind->chemin[i].x=a;
  pathfind->chemin[i].y=b;
  i++;
  return i;
}

/*fonction de creation de chemin du point de rencontre des chemins jusqu'a la base*/
void chemin_base(int x,int y,int tab[ABS][ORD],int a,int b,chemin_t * pathfind){
  int x_rand,y_rand;
  int min_x,min_y;
  if(a<(ABS/2)){
    if(b<(ORD/2)){
      min_x=(rand()%((x)-(a)+1));
      min_y=rand()%((y-b)+1);
      if(!min_x){
        x_rand=x;
      }else{
        x_rand=x-min_x;
      }if(!min_y){
        y_rand=y;
      }else{
        y_rand=y-min_y;
      }
    }else{
      min_x=(rand()%((x)-(a)+1));
      min_y=rand()%((b-y)+1);
      if(!min_x){
        x_rand=x;
      }else{
        x_rand=x-min_x;
      }if(!min_y){
        y_rand=y;
      }else{
        y_rand=y+min_y;
      }
    }
  }else{
    if(b<(ORD/2)){
      min_x=(rand()%((a)-(x)+1));
      min_y=rand()%((y-b)+1);
      if(!min_x){
        x_rand=x;
      }else{
        x_rand=x+min_x;
      }if(!min_y){
        y_rand=y;
      }else{
        y_rand=y-min_y;
      }
    }else{
      min_x=(rand()%((a)-(x)+1));
      min_y=rand()%((b-y)+1);
      if(!min_x){
        x_rand=x;
      }else{
        x_rand=x+min_x;
      }if(!min_y){
        y_rand=y;
      }else{
        y_rand=y+min_y;
      }
    }
  }
  int i=0;
  chemin(x, y, tab, x_rand, y);
  chemin(x_rand, y, tab, x_rand, y_rand);
  chemin(x_rand, y_rand, tab, a, b);
  i=pathfinding_base(x, y, pathfind, x_rand, y,i);
  i=pathfinding_base(x_rand, y, pathfind, x_rand, y_rand,i);
  i=pathfinding_base(x_rand,y_rand, pathfind, a, b,i);
}

/*fonction de creation */
void croisee(int a, int b, int mat[NB_ENTREE][2], int tab[ABS][ORD],chemin_t pathfind[NB_ENTREE+1]) {
  int i = 0;
  int x, y;
  if (a < ((ABS - 1) / 2)) {
    x = ABS - 3;
    for (i = 0; i < NB_ENTREE; i++) {
      if (mat[i][0] < x) {
        x = mat[i][0];
      }
    }
  } else {
    x = 2;
    for (i = 0; i < NB_ENTREE; i++) {
      if (mat[i][0] > x) {
        x = mat[i][0];
      }
    }
  }
  if (b < ((ORD - 1) / 2)) {
    y = ORD - 3;
    for (i = 0; i < NB_ENTREE; i++) {
      if (mat[i][1] < y) {
        y = mat[i][1];
      }
    }
  } else {
    y = 2;
    for (i = 0; i < NB_ENTREE; i++) {
      if (mat[i][1] > y) {
        y = mat[i][1];
      }
    }
  }
  for (i = 0; i < NB_ENTREE; i++) {
    chemin(mat[i][0], mat[i][1], tab, x, y);
    pathfinding(mat[i][0], mat[i][1], &pathfind[i], x, y);
  }
  chemin_base(x,y,tab,a,b,&pathfind[i]);
}
/*calcul des point important de chemin*/
void repathing(chemin_t path[NB_ENTREE+1],chemin_t repath[NB_ENTREE+1]){
  int j=0;
  int m=0;
  int i=0;
  int f=0;
  int q=0;
  for(int n=0;n<(NB_ENTREE+1);n++){
    q=0;
    while(path[n].chemin[q].x!=-1){
      if(path[n].chemin[q].x==path[n].chemin[q+1].x && path[n].chemin[q].y==path[n].chemin[q+1].y){
        f=q+1;
        while(path[n].chemin[f].x!=-1){
          path[n].chemin[f].x=path[n].chemin[f+1].x;
          path[n].chemin[f].y=path[n].chemin[f+1].y;
          f++;
        }
        q--;
      }
      q++;
    }
  }
  for(i=0;i<(NB_ENTREE+1);i++){
    repath[i].chemin[0].x=path[i].chemin[0].x;
    repath[i].chemin[0].y=path[i].chemin[0].y;
    j=1;
    m=1;
    while(path[i].chemin[j+1].x!=-1){
      j++;
      if(!(path[i].chemin[j-1].x==path[i].chemin[j+1].x) && !(path[i].chemin[j-1].y==path[i].chemin[j+1].y) ){
        repath[i].chemin[m].x=path[i].chemin[j].x;
        repath[i].chemin[m].y=path[i].chemin[j].y;
        m++;
      }
    }
    m++;
    j++;
    repath[i].chemin[m].x=path[i].chemin[j].x;
    repath[i].chemin[m].y=path[i].chemin[j].y;
  }
}

/*rassemble tout les point en un tab*/
void rassemble(chemin_t import[NB_ENTREE+1],chemin_t * suite){
  int h=0;
  suite->chemin[h].x=import[0].chemin[0].x;
  suite->chemin[h].y=import[0].chemin[0].y;
  h++;
  for(int i=0;i<(NB_ENTREE+1);i++){
    for(int j=0;import[i].chemin[j].x>-1;j++){
      if(import[i].chemin[j].x==suite->chemin[h-1].x && import[i].chemin[j].y==suite->chemin[h-1].y){
      }else{
        suite->chemin[h].x=import[i].chemin[j].x;
        suite->chemin[h].y=import[i].chemin[j].y;
        h++;
      }

    }
  }



}

/*fonction principale qui rassemble toute celle au dessus et les appelle dans le bon ordre*/
chemin_t map(int tab[ABS][ORD]) {
  srand(time(NULL));  
  chemin_t pathfind[NB_ENTREE+1];
  chemin_t import[NB_ENTREE+1];
  chemin_t suite;
  int a;
  int b;
  int mat[NB_ENTREE][2];
  initialise(tab);
  init_chemin(pathfind);
  init_chemin(import);
  init_chemin2(&suite);
  genere_base(&a, &b, tab);
  mat_bord(a, b, tab, mat);
  croisee(a, b, mat, tab,pathfind);
  re_initialise(tab,pathfind,mat);
  repathing(pathfind,import);
  rassemble(import,&suite);
  tab[a][b] = 1;
  affiche_chemin2(suite);
  return suite;
}

/*main appellant la fonction principale*/
chemin_t creation_map(SDL_Renderer *renderer,int tab[ABS][ORD]){
  chemin_t suite;
  suite=map(tab);
  return suite;
}
