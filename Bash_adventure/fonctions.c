#include "parametres.h"
#define DIMX 62
#define DIMY 31


void* malloc_p(size_t s)
{
  void *p;
  if(!(p = malloc(s))) {exit(EXIT_FAILURE);}

  return p;
}

void purgeSTDIN(){
char ch;
while ((ch = getchar()) != '\n' && ch != EOF);
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

void initGame(Game **partie)
{
    Joueur *p;
    int i,j;

    Univers *Cosmos;

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

    ///initialisation du COSMOS
    initCarte((*partie)->map1);
    initCarte((*partie)->map2);
    initCarte((*partie)->map3);

    ///Trou de vers
    Cosmos=(*partie)->Galaxy;

    Cosmos->carte=(*partie)->map1;

    Cosmos->suivante=(*partie)->map2;

    Cosmos=Cosmos->suivante;

    Cosmos->suivante=(*partie)->map3;

    Cosmos=Cosmos->suivante;

    Cosmos->suivante=NULL;

    ///placement du joueur
    (*partie)->map1[i][j+1]=42;

    Cosmos=(*partie)->Galaxy;
    affichage(Cosmos->carte);
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
            carte[i][j]=32;
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

    ///placement de la porte
    carte[(DIMY-1)/2][DIMX-1]=40;

    ///Obstacle al�atoire
    for(i=0;i<20;i++){
        x=rand() % (DIMX-2 - 3 + 1) + 3;
        y=rand() % (DIMY-2 - 3 + 1) + 3;
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
        (*self)->representation=35;
        (*self)->PV=100+PV;
        (*self)->XP=XP;
        (*self)->ATK=7*ATK;
    }
    if (strcmp(t[x],'slime'))
    {
        (*self)->representation=35;
        (*self)->PV=50;
        (*self)->XP=XP;
        (*self)->ATK=1*ATK;
    }
    if (strcmp(t[x],'zombie'))
    {
        (*self)->representation=35;
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
                carte[x+1][y]=monstre->representation;
            }
        }
    if(i==1)
        {
            if((y+1<DIMY-1) && (carte[x][y+1]!=35))
            {
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x][y+1];
                carte[x][y+1]=monstre->representation;
            }
        }
    if(i==2)
        {
            if((x-1>0) && (carte[x-1][y]!=35))
            {
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x-1][y];
                carte[x-1][y]=monstre->representation;
            }
        }
    if((i==3) && (carte[x][y-1]!=35))
        {
            if(y-1>0)
            {
                carte[x][y]=monstre->prec;
                monstre->prec=carte[x][y-1];
                carte[x][y-1]=monstre->representation;
            }
        }
}

void Combat(Joueur *player,Monstre *ennemi)
{
    int choix;

    printf("Vous �tes en combat, il est l'heure de montrer ce que vous savez faire !\n\n");


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
                printf("Vous avez decide de vous defendre");
                break;
            case 3:
                printf("Ouverture inventaire");
                break;
            case 4:
                printf("Vous etes un gros lache, vous n'avez pas l ame d un guerrier... honte a vous !\n");
                return 0;
                break;

        }
    }
}


void DeplacementJoueur(Joueur *p,int **carte)
{
    int x,y;
    char touche;

    //purgeSTDIN();
    //getc(touche);

    x=p->position[0];
    y=p->position[1];

    if((touche=='z') && (carte[x][y+1]!=35) && (y+1<DIMY-1)){//122
        carte[x][y]=p->prec;
        p->prec=carte[x][y+1];
        carte[x][y+1]=42;
    }
    if((touche=='s') && (carte[x][y-1]!=35) && (y-1>0)){//115
        carte[x][y]=p->prec;
        p->prec=carte[x][y-1];
        carte[x][y-1]=42;
    }
    if((touche=='q') && (carte[x-1][y]!=35) && (x-1>0)){//113
        carte[x][y]=p->prec;
        p->prec=carte[x-1][y];
        carte[x-1][y]=42;
    }
    if((touche==100) && (carte[x+1][y]!=35) && (x+1<DIMX-1)){//100
        carte[x][y]=p->prec;
        p->prec=carte[x+1][y];
        carte[x+1][y]=42;
    }
    //system("cls");
    affichage(carte);
}
void Jeu(Game *p)
{
    int continuer,i;
    Joueur *player;
    Monstre *monstre;
    Univers *Cosmos;

    Cosmos=p->Galaxy;
    player=p->player;
    continuer=1;

    for(i=0;i<3;i++){

    }

    while(continuer==1){
        DeplacementJoueur(player,Cosmos->carte);
        if(player->prec=monstre->representation){
            Combat(player,monstre);
        }
        if((player->position[0]==(DIMY-1)/2)&&(player->position[1]==DIMX-1)){
            printf("Voulez vous passez au niveau suivant ?\n");
            printf("1.Oui\n2.Non\n");
        }
    }

}

///chargement d'une sauvegarde
void chargement_fichier()
{
    FILE *fichier;
    // Ouverture du fichier en lecture gr�ce � "r"
    fichier = fopen("save.txt ","r");
    // Verifier que le fichier a bien �t� ouvert
    if (fichier != NULL)
    {

        // Fermeture du fichier
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de sauvegarder");
    }
}
void sauvegarde_fichier(Game *partie)
{
    FILE *fichier;
    // Ouverture du fichier en ajout gr�ce � "a"
    fichier = fopen("save.txt ","a");
    // Verifier que le fichier a bien �t� ouvert
    if (fichier != NULL)
    {
        // Ecriture
        //perso
        fprintf(fichier,"%d\n",partie->player->prec);
        fprintf(fichier,"%d\n",partie->player->PV);
        fprintf(fichier,"%d\n",partie->player->DEF);
        fprintf(fichier,"%d\n",partie->player->PM);
        fprintf(fichier,"%d\n",partie->player->LVL);
        fprintf(fichier,"%d\n",partie->player->XP);
        fprintf(fichier,"%d\n",partie->player->ATK);
        fprintf(fichier,"%d\n",partie->player->VIT);
        fprintf(fichier,"%d\n",partie->player->DEF);
        fprintf(fichier,"%d\n",partie->player->position[2]);
        fprintf(fichier,"%s\n",partie->player->pseudo[20]);
        fprintf(fichier,"%s\n",partie->player->classe[20]);
        //map


        // Fermeture du fichier
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de sauvegarder");
    }
}