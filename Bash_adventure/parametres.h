#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED
#define DIMX 62
#define DIMY 31

void* malloc_p(size_t s)
{
  void *p;
  if(!(p = malloc(s))) {exit(EXIT_FAILURE);}

  return p;
}

typedef struct Monstre Monstre;
struct Monstre{
char nom[20];
int PV;
int PM;
int XP;
int Force;
int VITESSE;
};

typedef struct Joueur Joueur;
struct Joueur{
char pseudo[20];
char classe[20];
int PV;
int PM;
int XP;
int Force;
int VIT;
};

/*
typedef struct Classe Classe;
struct Classe{
int Archer[4];
int Mage[4];
int Chevalier[4];
int Vanguard[4];
}
*/


typedef struct Game Game;
struct Game{
Joueur *player;
int **map1[DIMY];
int **map2[DIMY];
int **map3[DIMY];
int time;
int position[2];
};


void initGame(Game **partie)
{
    Joueur *p;
    char player=42;
    int i,j;

    *partie=(Game*)malloc_p(sizeof(Game));

    p=(*partie)->player;
    initJoueur(&p);

    (*partie)->time=300;

    j=0;
    i=(DIMY-1)/2;

    (*partie)->position[0]=i;
    (*partie)->position[1]=j;

    Creation_map((*partie)->map1);
    Creation_map((*partie)->map2);
    Creation_map((*partie)->map3);

    ///initialisation de la carte
    initCarte((*partie)->map1);

    ///placement du joueur
    (*partie)->map1[i][j]=player;

    affichage((*partie)->map1);
}

void Creation_map(int **carte)
{
    int i;

    for(i=0;i<DIMY;i++){
        carte[i]=(int*)malloc_p(DIMX*sizeof(int));
    }

}

void initCarte(int **carte)
{
    int i,j;

    for(i=0;i<DIMY;i++){
        for(j=0;j<DIMX;j++){
            carte[i][j]=0;
        }
    }


    ///Murs Horizontales
    for(i=0;i<DIMX;i++){
        carte[0][i]=45;
        carte[DIMY-1][i]=45;
    }
    ///Murs verticales
    for(i=1;i<DIMY-1;i++){
        carte[i][DIMX-1]=124;
        carte[i][0]=124;
    }
}

void affichage(int **carte)
{
    int i,j;

    for(i=0;i<DIMY;i++){
        for(j=0;j<DIMX;j++){
            printf("%c",carte[i][j]);
        }
        printf("\n");
    }
}

DistributeurCapa(Joueur **p,int val){
  if(val==1){
    (*p)->PV=10;
    (*p)->PM=0;
    (*p)->XP=0;
    (*p)->Force=3;
  }
  if(val==2){
    (*p)->PV=6;
    (*p)->PM=6;
    (*p)->XP=0;
    (*p)->Force=2;
  }
  if(val==3){
    (*p)->PV=5;
    (*p)->PM=0;
    (*p)->XP=0;
    (*p)->Force=3;
  }
  if(val==4){
    (*p)->PV=15;
    (*p)->PM=0;
    (*p)->XP=0;
    (*p)->Force=8;
  }
}

void initJoueur(Joueur **p){
    *p=(Joueur*)malloc_p(sizeof(Joueur));
    int choix=0;
    printf("Saisir votre pseudo de joueur\n");
    fgets((*p)->pseudo,20,stdin);
    printf("Choisissez votre classe parmi celles-ci\n");
    printf("1.Archer\n");
    printf("2.Mage\n");
    printf("3.Chevalier\n");
    printf("4.Vanguard\n");
    scanf("%d",&choix);
    ///on voudrait affecter une chaîne de caractères à une autre mais on se trompe à chaque fois sur la syntaxe
    /*if(choix==1){
        (*p)->classe={'A','r','c','h','e','r'};
    }
    if(choix==2){
      strcpy((*p)->classue,{'M','a','g','e'});
    }
    if(choix==3){
      strcpy((*p)->classe,{'C','h','e','v','a','l','i','e','r'});
    }
    if(choix==4){
      strcpy((*p)->classe,{'V','a','n','g','u','a','r','d'});
    }*/
    DistributeurCapa(p,choix);
}

void init_monstre(Monstre **self)
{
    srand(time(NULL));
    int x;
    char t[3]={'zombie' , 'slime', 'dragon'};
    *self=malloc_p(sizeof(Monstre));
    x=rand()%3;
    if (strcmp(t[x],'zombie'))
    {
        (*self)->PV=100;
        (*self)->PM=0;
        (*self)->Force=5;
    }
    else if (strcmp(t[x],'slime'))
    {
        (*self)->PV=50;
        (*self)->PM=10;
        (*self)->Force=1;
    }
    else if (strcmp(t[x],'zombie'))
    {
        (*self)->PV=200;
        (*self)->PM=100;
        (*self)->Force=10;
    }
}


#endif // PARAMETRES_H_INCLUDED
