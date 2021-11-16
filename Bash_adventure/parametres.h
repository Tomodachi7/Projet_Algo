#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED

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
    char **carte1;
    char **carte2;
    char **carte3;
    int i;

    *partie=(Game*)malloc_p(sizeof(Game));

    p=(*partie)->player;
    //initJoueur(&p); fonction à définir

    (*partie)->time=300;

    (*partie)->position={0,100};

    carte1=(*partie)->MAP1;
    carte1=(char**)malloc_p(201*sizeof(char*));

    carte2=(*partie)->MAP2;
    cart2=(char**)malloc_p(201*sizeof(char*));

    carte3=(*partie)->MAP3;
    cart3=(char**)malloc_p(201*sizeof(char*));

    for(i=0;i<201;i++){
        carte1[i]=(char*)malloc_p(201*sizeof(char));
        carte2[i]=(char*)malloc_p(201*sizeof(char));
        carte3[i]=(char*)malloc_p(201*sizeof(char));
    }

}

#endif // PARAMETRES_H_INCLUDED
