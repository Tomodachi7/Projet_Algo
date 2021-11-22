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
int represention;
char nom[20];
int PV;
int PM;
int XP;
int ATK;
int VIT;
int position[2];
};

typedef struct Joueur Joueur;
struct Joueur{
char pseudo[20];
char classe[20];
int PV;
int DEF;
int PM;
int XP;
int ATK;
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
    (*p)->ATK=3;
  }
  if(val==2){
    (*p)->PV=6;
    (*p)->PM=6;
    (*p)->XP=0;
    (*p)->ATK=2;
  }
  if(val==3){
    (*p)->PV=5;
    (*p)->PM=0;
    (*p)->XP=0;
    (*p)->ATK=3;
  }
  if(val==4){
    (*p)->PV=15;
    (*p)->PM=0;
    (*p)->XP=0;
    (*p)->ATK=8;
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
    int x,i,j;
    char t[3]={'zombie' , 'slime', 'dragon'};

    *self=malloc_p(sizeof(Monstre));

    x=rand()%3;
    i=rand()%(DIMX-1)+1;
    j=rand()%(DIMY-1)+1;

    if (strcmp(t[x],'zombie'))
    {
        (*self)->represention=35;
        (*self)->PV=100;
        (*self)->PM=0;
        (*self)->ATK=5;
    }
    else if (strcmp(t[x],'slime'))
    {
        (*self)->represention=35;
        (*self)->PV=50;
        (*self)->PM=10;
        (*self)->ATK=1;
    }
    else if (strcmp(t[x],'zombie'))
    {
        (*self)->represention=35;
        (*self)->PV=200;
        (*self)->PM=100;
        (*self)->ATK=10;
    }

    (*self)->position[0]=i;
    (*self)->position[1]=j;
}

void deplament_monstre(int **carte,Monstre *monstre)
{
    srand( time( NULL ) );

    int i,x,y;

    x=monstre->position[0];
    y=monstre->position[1];

    i=rand()%4;

    if(i==0){
            if((x+1<DIMX-1) && (carte[x+1][y]==58)){
                carte[x+1][y]=monstre->represention;
                carte[x][y]=0;
                //delay(3); ///rechercher comment delay le temps
            }
        }
    if(i==1)
        {
            if((y+1<DIMY-1) && (carte[x][y+1]==58))
            {
                carte[x][y+1]=monstre->represention;
                carte[x][y]=0;
                //delay(3);
            }
        }
    if(i==2)
        {
            if((x-1>0) && (carte[x-1][y]==58))
            {
                carte[x-1][y]=monstre->represention;
                carte[x][y]=0;
                //delay(3);
            }
        }
    if((i==3) && (carte[x][y-1]==58))
        {
            if(y-1>0)
            {
                carte[x][y-1]=monstre->represention;
                carte[x][y]=0;
                //delay(3);
            }
        }
}

void Combat(Joueur *player,Monstre *ennemi)
{
    int choix;

    printf("Vous êtes en combat, il est l'heure de montrer ce que vous savez faire !\n\n");


    while((player->PV!=0)||(ennemi->PV!=0)){

        printf("Faites votre choix:\n");
        printf("1.Attaquer\n");
        printf("2.Defense\n");
        printf("3.Inventaire\n");
        printf("4.Fuir\n\n");

        scanf("%d",&choix);

        switch(choix)
        {
            case 1:
                printf("Quelle type d'attaque voulez vous utiliser\n");
                printf("Attaque physique\n");
                printf("Attaque magique\n");
                break;
            case 2:
                printf("Vous avez décidé de défendre");
                break;
            case 3:
                printf("Ouverture inventaire");
                break;
            case 4:
                printf("Vous êtes un gros lache, honte a vous !\n");
                return 0;
                break;

        }
    }
}
///Trouver une façon de fliger la map derrière

#endif // PARAMETRES_H_INCLUDED
