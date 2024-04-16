#include "../lib/fonc.h"


typedef struct coord_s{
  int x;
  int y;
} coord_t;

typedef struct chemin_s{
  coord_t chemin[(ABS)+(ORD)];
} chemin_t;



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
}

void affiche_map_2(int tab[ABS][ORD],SDL_Renderer *renderer,SDL_Window *window) {
  SDL_Rect position;
  

  SDL_Surface * loutre =NULL;
  SDL_Texture * texture2= NULL;
  loutre = IMG_Load("../img/loutre.png");

  SDL_Surface * cheese =NULL;
  SDL_Texture * texture3= NULL;
  cheese = IMG_Load("../img/cheese.png");


  SDL_Surface * blanc =NULL;
  SDL_Texture * texture4= NULL;
  blanc = IMG_Load("../img/chemin.png");

  texture2=SDL_CreateTextureFromSurface(renderer,loutre);
  texture3=SDL_CreateTextureFromSurface(renderer,cheese);
  texture4=SDL_CreateTextureFromSurface(renderer,blanc);

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
          case 2:
            position.h=(haut-200)/ORD;
            position.w=larg/ABS;
            SDL_RenderCopy(renderer,texture3,NULL,&position);
            SDL_QueryTexture(texture3,NULL,NULL,&(position.w),&(position.h));
            break;;
          case 3:
            position.h=(haut-200)/ORD;
            position.w=larg/ABS;
            SDL_RenderCopy(renderer,texture4,NULL,&position);
            SDL_QueryTexture(texture4,NULL,NULL,&(position.w),&(position.h));
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
  SDL_DestroyTexture(texture4);
  SDL_FreeSurface(loutre);
  SDL_FreeSurface(cheese);
  SDL_FreeSurface(blanc);
}



void initialise(int tab[ABS][ORD]) {
  int j, i;
  for (j = 0; j < ORD; j++) {
    for (i = 0; i < ABS; i++) {
      tab[i][j] = 0;
    }
  }
}

void init_chemin(chemin_t pathfind[NB_ENTREE+1]){
  for(int i=0;i<(NB_ENTREE+1);i++){
    for(int j=0;j<((ORD)+(ABS));j++){
      pathfind[i].chemin[j].x=0;
      pathfind[i].chemin[j].y=0;
    }
  }
}

void affiche_chemin(chemin_t pathfind[NB_ENTREE+1]){
  for(int i=0;i<(NB_ENTREE+1);i++){
    for(int j=0;pathfind[i].chemin[j].x!=0;j++){
      printf("|%d : %d",pathfind[i].chemin[j].x,pathfind[i].chemin[j].y);
    }
    printf("\n");
  }

}

void genere_base(int *a, int *b, int tab[ABS][ORD]) {
  int x = (rand() % (ABS - 2)) + 1;
  int y = (rand() % (ORD - 2)) + 1;
  tab[x][y] = 1;
  (*a) = x;
  (*b) = y;
}

int vide(int a, int b, int tab[ABS][ORD]) { return tab[a][b] == 0; }

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

int test_bord(int a, int b, int tab[ABS][ORD]) {
  return adjacent(a, b, tab) && devant(a, b, tab) && (tab[a][b] == 0);
}

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

void mat_bord(int a, int b, int tab[ABS][ORD], int mat[NB_ENTREE][2]) {
  int x, y;
  for (int i = 0; i < NB_ENTREE; i++) {
    calc_bord(a, b, tab, &x, &y);
    tab[x][y] = 2;
    mat[i][0] = x;
    mat[i][1] = y;
  }
}

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

void map(int tab[ABS][ORD],chemin_t pathfind[NB_ENTREE+1]) {
  srand(time(NULL));  
  int a;
  int b;
  int mat[NB_ENTREE][2];
  initialise(tab);
  init_chemin(pathfind);
  genere_base(&a, &b, tab);
  mat_bord(a, b, tab, mat);
  croisee(a, b, mat, tab,pathfind);
  re_initialise(tab,pathfind,mat);
  tab[a][b] = 1;
}




void creation_map(SDL_Renderer *renderer,int tab[ABS][ORD]){
  chemin_t pathfind[NB_ENTREE+1];
  map(tab,pathfind); 
  affiche_map(tab);
  affiche_chemin(pathfind);
}