#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED
#define DIM 101

void* malloc_p(size_t s)
{
  void *p;
  if(!(p = malloc(s))) {exit(EXIT_FAILURE);}

  return p;
}

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
char **MAP1;
char **MAP2;
char **MAP3;
int time;
int position[2];
};

typedef struct Monstre Monstre;
struct Monstre{
char nom[20];
int PV;
int PM;
int XP;
int Force;
int VIT;
};

void initGame(Game **partie)
{
    Joueur *p;
    char player='§';
    char **carte1;
    char **carte2;
    char **carte3;
    int i,j;

    *partie=(Game*)malloc_p(sizeof(Game));

    p=(*partie)->player;
    initJoueur(&p);

    (*partie)->time=300;

    (*partie)->position[0]=0;
    (*partie)->position[1]=(DIM-1)/2;

    carte1=(*partie)->MAP1;
    carte1=(char**)malloc_p(DIM*sizeof(char*));

    carte2=(*partie)->MAP2;
    carte2=(char**)malloc_p(DIM*sizeof(char*));

    carte3=(*partie)->MAP3;
    carte3=(char**)malloc_p(DIM*sizeof(char*));

    for(i=0;i<201;i++){
        carte1[i]=(char*)malloc_p(DIM*sizeof(char));
        carte2[i]=(char*)malloc_p(DIM*sizeof(char));
        carte3[i]=(char*)malloc_p(DIM*sizeof(char));
    }

    for(i=0;i<DIM;i++){
        carte1[0][i]='-';
        carte1[DIM-1][i]='-';
        carte2[0][i]='-';
        carte2[DIM-1][i]='-';
        carte3[0][i]='-';
        carte3[DIM-1][i]='-';
    }
    for(i=0;i<DIM;i++){
        carte1[i][DIM-1]='|';
        carte1[i][0]='|';
        carte2[i][DIM-1]='|';
        carte2[i][0]='|';
        carte3[i][DIM-1]='|';
        carte3[i][0]='|';
    }
    carte1[(*partie)->position[0]][(*partie)->position[1]]=player;

    affichage(carte1);
}

void affichage(char **carte)
{
    int i,j;

    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
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
    /*if(choix==1){
        (*p)->classe={'A','r','c','h','e','r'};
    }
    if(choix==2){
      strcpy((*p)->classe,{'M','a','g','e'});
    }
    if(choix==3){
      strcpy((*p)->classe,{'C','h','e','v','a','l','i','e','r'});
    }
    if(choix==4){
      strcpy((*p)->classe,{'V','a','n','g','u','a','r','d'});
    }*/
    DistributeurCapa(p,choix);
}

#endif // PARAMETRES_H_INCLUDED
