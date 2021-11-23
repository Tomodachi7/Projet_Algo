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

void Menu(){
  printf("//////////////////////////////////////////\n");
  printf("//////////////bash adventure//////////////\n");
  printf("//////////////////////////////////////////\n");
  sleep(1);
  printf("by \n DYLAS William \n SURVILLE BARLAND Enrick \n TARET Ludovic \n ");
  sleep(3);
  system("cls");
  printf("bienvenue\n\n");
}

typedef struct Joueur Joueur;
struct Joueur{
char pseudo[20];
char classe[20];
int prec;
int PV;
int DEF;
int PM;
int LVL;
int XP;
int ATK;
int VIT;
int position[2];
};

typedef struct Game Game;
struct Game{
Joueur *player;
int **map1[DIMY];
int **map2[DIMY];
int **map3[DIMY];
int time;

};

typedef struct Monstre Monstre;
struct Monstre{
int represention;
int prec;
char nom[20];
int PV;
int PM;
int XP;
int ATK;
int VIT;
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

    (*partie)->time=0;

    j=0;
    i=(DIMY-1)/2;

    p->position[0]=i;
    p->position[1]=j;

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
    srand(time(NULL));

    int i,j,x,y;

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


    for(i=0;i<10;i++){
        x=rand() % (DIMX-2 - 2 + 1) + 2;
        y=rand() % (DIMY-2 - 2 + 1) + 2;
        carte[x][y]=35;
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

void DistributeurCapa(Joueur **p,int val)
{
  if(val==1){
    (*p)->LVL=1;
    (*p)->PV=100;
    (*p)->PM=0;
    (*p)->DEF=20;
    (*p)->XP=0;
    (*p)->ATK=40;
  }
  if(val==2){
    (*p)->LVL=1;
    (*p)->PV=100;
    (*p)->PM=6;
    (*p)->DEF=10;
    (*p)->XP=0;
    (*p)->ATK=10;
  }
  if(val==3){
    (*p)->LVL=150;
    (*p)->PV=5;
    (*p)->PM=0;
    (*p)->DEF=40;
    (*p)->XP=0;
    (*p)->ATK=30;
  }
  if(val==4){
    (*p)->LVL=1;
    (*p)->PV=200;
    (*p)->PM=0;
    (*p)->DEF=55;
    (*p)->XP=0;
    (*p)->ATK=20;
  }
}

void initJoueur(Joueur **p){
    *p=(Joueur*)malloc_p(sizeof(Joueur));

    int choix;

    fgets((*p)->pseudo,20,stdin);
    printf("Saisir votre pseudo de joueur\n");
    fgets((*p)->pseudo,20,stdin);

    printf("Choisissez votre classe parmi celles-ci\n");
    printf("1.Archer\n");
    printf("2.Mage\n");
    printf("3.Chevalier\n");
    printf("4.Vanguard\n");

    scanf("%d",&choix);

    if(choix==1){
        strcpy((*p)->classe,"Archer");
    }
    if(choix==2){
      strcpy((*p)->classe,"Caster");
    }
    if(choix==3){
      strcpy((*p)->classe,"Knight");
    }
    if(choix==4){
      strcpy((*p)->classe,"Vanguard");
    }

    DistributeurCapa(p,choix);
}

void init_monstre(Monstre **self,int nv_map)
{
    srand(time(NULL));

    int x,i,j,PV,XP,ATK;

    char t[3]={'zombie' , 'slime', 'dragon'};

    *self=malloc_p(sizeof(Monstre));

    x=rand()%3;
    i=rand()%(DIMX-1)+1;
    j=rand()%(DIMY-1)+1;

    if(nv_map==1){
        PV=0;
        ATK=1;
        XP=50;
    }

    if(nv_map==2){
        PV=40;
        ATK=2;
        XP=33;
    }

    if(nv_map==3){
        PV=80;
        ATK=3;
        XP=25;
    }

    if (strcmp(t[x],'zombie'))
    {
        (*self)->represention=35;
        (*self)->PV=100+PV;
        (*self)->XP=XP;
        (*self)->ATK=7*ATK;
    }
    if (strcmp(t[x],'slime'))
    {
        (*self)->represention=35;
        (*self)->PV=50;
        (*self)->XP=XP;
        (*self)->ATK=1*ATK;
    }
    if (strcmp(t[x],'zombie'))
    {
        (*self)->represention=35;
        (*self)->PV=200+PV;
        (*self)->XP=XP;
        (*self)->ATK=10*ATK;
    }

    (*self)->position[0]=i;
    (*self)->position[1]=j;
}

void deplament_monstre(int **carte,Monstre *monstre)
{
    srand( time( NULL ) );

    int i,x,y,prec;

    x=monstre->position[0];
    y=monstre->position[1];

    i=rand()%4;

    if(i==0){
            if((x+1<DIMX-1) && (carte[x+1][y]!=35)){
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x+1][y];
                carte[x+1][y]=monstre->represention;
            }
        }
    if(i==1)
        {
            if((y+1<DIMY-1) && (carte[x][y+1]!=35))
            {
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x][y+1];
                carte[x][y+1]=monstre->represention;
            }
        }
    if(i==2)
        {
            if((x-1>0) && (carte[x-1][y]!=35))
            {
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x-1][y];
                carte[x-1][y]=monstre->represention;
            }
        }
    if((i==3) && (carte[x][y-1]!=35))
        {
            if(y-1>0)
            {
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x][y-1];
                carte[x][y-1]=monstre->represention;
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

void DeplacementJoueur(Joueur *p,int **carte)
{
    int touche,prec,x,y;

    scanf("%d",&touche);

    x=p->position[0];
    y=p->position[1];

    if((touche==122) && (carte[x][y+1]!=35) && (y+1<DIMY-1)){
        carte[x][y]=p->prec;
        p->prec=carte[x][y+1];
        carte[x][y+1]=42;
    }
    if((touche==115) && (carte[x][y-1]!=35) && (y-1>0)){
        carte[x][y]=p->prec;
        p->prec=carte[x][y-1];
        carte[x][y-1]=42;
    }
    if((touche==113) && (carte[x-1][y]!=35) && (x-1>0)){
        carte[x][y]=p->prec;
        p->prec=carte[x-1][y];
        carte[x-1][y]=42;
    }
    if((touche==100) && (carte[x+1][y]!=35) && (x+1<DIMX-1)){
        carte[x][y]=p->prec;
        p->prec=carte[x+1][y];
        carte[x+1][y]=42;
    }
}
void Jeu(Game *p)
{
  int continuer;
  Joueur *player;
  player=p->player;
  continuer=1;

  while(continuer==1){
    DeplacementJoueur(player,p->map1);

  }

}

///chargement sauvegarde supression
//void chargement_fichier(){
//}
void sauvegarde_fichier(Game *partie)
{
    FILE *fichier;
    // Ouverture du fichier en écriture grâce à "w"
    fichier = fopen("save.txt ","a");
    // Verifier que le fichier a bien été ouvert
    if (fichier != NULL)
    {
        // Ecriture
        //fprintf(fichier,"%d\n",a);
        //fprintf(fichier,"%lf\n",b);
        // Fermeture du fichier
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de sauvegarder");
    }
}

#endif // PARAMETRES_H_INCLUDED
