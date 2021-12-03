#include "parametres.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



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

int Menu()
{
    int choix;

    printf("//////////////////////////////////////////\n");
    printf("//////////////bash adventure//////////////\n");
    printf("//////////////////////////////////////////\n");
    sleep(1);

    printf("by \n DYLAS William \n SURVILLE BARLAND Enrick \n TARET Ludovic \n ");
    sleep(2);

    system("cls");

    printf("bienvenue\n\n");
    printf("--Menu--\n");
    printf("1-Jouer\n");
    printf("2-Charger une sauvegarde\n");
    printf("3-Supprimer une sauvegarde\n");
    printf("4-Quitter\n");

    scanf("%d",&choix);

    system("cls");

    return choix;
}

void initGame(Game **partie)
{
    Joueur *p;
    int i,j;

    j=1;
    i=(DIMY-1)/2;

    Univers *Cosmos1;
    Univers *Cosmos2;
    Univers *Cosmos3;

    *partie=(Game*)malloc_p(sizeof(Game));

    p=(*partie)->player;
    initJoueur(&p);



    Cosmos1=(Univers*)malloc_p(sizeof(Univers));
    Cosmos2=(Univers*)malloc_p(sizeof(Univers));
    Cosmos3=(Univers*)malloc_p(sizeof(Univers));


    (*partie)->Galaxy1=Cosmos1;
    (*partie)->Galaxy2=Cosmos2;
    (*partie)->Galaxy3=Cosmos3;


    Cosmos1->level=1;
    Cosmos2->level=2;
    Cosmos3->level=3;



    (*partie)->time=0;

    p->position[0]=i;
    p->position[1]=j;


    initCarte(Cosmos1->carte);



    ///Trou de vers
    Cosmos1->suivante=Cosmos2;
    Cosmos2->suivante=Cosmos3;
    Cosmos3->suivante=NULL;



    affichage(Cosmos1->carte,p);

}

void initCarte(int carte[DIMY][DIMX])
{
    srand(time(NULL));

    int i,j,x,y;


    for(i=0;i<DIMY;i++){
        for(j=0;j<DIMX;j++){
            carte[i][j]=3;
        }
    }


    ///Murs Horizontales
    for(i=0;i<DIMX;i++){
        carte[0][i]=1;
        carte[DIMY-1][i]=1;
    }


    ///Murs verticales
    for(i=1;i<DIMY-1;i++){
        carte[i][DIMX-1]=2;
        carte[i][0]=2;
    }


    ///placement de la porte
    carte[(DIMY-1)/2][DIMX-1]=0;


    ///Obstacle aléatoire
    for(i=0;i<20;i++){
        x=rand() % (DIMX-2 - 3 + 1) + 3;
        y=rand() % (DIMY-2 - 3 + 1) + 3;
        carte[x][y]=4;
    }

    ///drop objet
    carte[19][7]=6;
    carte[17][21]=7;
    carte[1][27]=9;
    carte[15][40]=8;



}

void affichage(int carte[DIMY][DIMX],Joueur *p)
{
    int i,j,x,y;

    x=p->position[0];
    y=p->position[1];

    system("cls");

    for(i=0;i<DIMY;i++){
        for(j=0;j<DIMX;j++){


            if((i==x)&&(j==y)) printf("%c",42);

            else{

                if(carte[i][j]==1) printf("%c",45);

                if(carte[i][j]==2) printf("%c",124);

                if(carte[i][j]==3) printf("%c",32);

                if(carte[i][j]==0) printf("%c",40);

                if(carte[i][j]==4) printf("%c",35);

                if(carte[i][j]==5) printf("%c",77);

                if(carte[i][j]==6) printf("%c",105);

                if(carte[i][j]==7) printf("%c",104);

                if(carte[i][j]==8) printf("%c",112);

                if(carte[i][j]==9) printf("%c",119);
            }

        }
        printf("\n");
    }
}

void DistributeurCapa(Joueur **p,int val)
{
  if(val==1){
    (*p)->LVL=1;
    (*p)->PV=300;
    (*p)->PM=0;
    (*p)->DEF=20;
    (*p)->XP=0;
    (*p)->ATK=40;
  }
  if(val==2){
    (*p)->LVL=1;
    (*p)->PV=200;
    (*p)->PM=100;
    (*p)->DEF=10;
    (*p)->XP=0;
    (*p)->ATK=10;
  }
  if(val==3){
    (*p)->LVL=1;
    (*p)->PV=400;
    (*p)->PM=0;
    (*p)->DEF=40;
    (*p)->XP=0;
    (*p)->ATK=30;
  }
  if(val==4){
    (*p)->LVL=1;
    (*p)->PV=500;
    (*p)->PM=0;
    (*p)->DEF=60;
    (*p)->XP=0;
    (*p)->ATK=20;
  }
}

void initJoueur(Joueur **p){
    *p=(Joueur*)malloc_p(sizeof(Joueur));

    int choix,sexe,i;

    printf("Choisissez votre genre: 1.Male alpha 2.Femme\n");
    scanf("%d",&sexe);

    for(i=0;i<TAILLE_SAC;i++){
        (*p)->sacado[i]=0;
    }

    (*p)->sexe=sexe;
    (*p)->portefeuille=100;

    ///Le début des emmerdes
    purgeSTDIN();
    printf("Saisir votre pseudo de joueur\n");
    fgets((*p)->pseudo,20,stdin);

    printf("Choisissez votre classe parmi celles-ci\n");
    printf("1.Archer\n");
    printf("2.Caster\n");
    printf("3.Knight\n");
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

    int x,PV,XP,ATK;

    x=rand()%3;

    char *t[]={"zombie" , "slime", "dragon"};

    *self=malloc_p(sizeof(Monstre));

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

    if (strcmp(t[x],"zombie"))
    {
        (*self)->representation=35;
        (*self)->PV=100+PV;
        (*self)->XP=XP;
        (*self)->ATK=7*ATK;
        strcpy((*self)->nom,t[x]);
    }
    if (strcmp(t[x],"slime"))
    {
        (*self)->representation=35;
        (*self)->PV=50;
        (*self)->XP=XP;
        (*self)->ATK=1*ATK;
        strcpy((*self)->nom,t[x]);
    }
    if (strcmp(t[x],"dragon"))
    {
        (*self)->representation=35;
        (*self)->PV=200+PV;
        (*self)->XP=XP;
        (*self)->ATK=10*ATK;
        strcpy((*self)->nom,t[x]);
    }
}

/*void deplament_monstre(int **carte,Monstre *monstre)
{
    srand( time( NULL ) );

    int i,x,y;

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
}*/

void Combat(int carte[DIMY][DIMX],Joueur *player,Monstre *ennemi)
{
    int choix=0;
    int tours=0;

    system("cls");

    printf("Vous etes en combat, il est l'heure de montrer ce que vous savez faire !\n\n");

    sleep(2);

    while( ((player->PV > 0) && (ennemi->PV > 0)) || (choix!=4) ){

        printf("%s : %d PV\n",player->pseudo,player->PV);
        printf("XP : %d\n",player->XP);
        printf("\n");
        printf("%s : %d PV\n",ennemi->nom,ennemi->PV);

        printf("Faites votre choix:\n");
        printf("1.Attaquer\n");
        printf("2.Defense\n");
        printf("3.Inventaire\n");
        printf("4.Fuir\n\n");

        scanf("%d",&choix);

        switch(choix)
        {
            case 1:
                if(strcmp(player->classe,"Archer")==0){
                    if(tours%4==0) ennemi->PV=ennemi->PV - 2*player->ATK;
                    else ennemi->PV=ennemi->PV - player->ATK;

                }

                if(strcmp(player->classe,"Caster")==0){
                        if(tours>0) ennemi->PV=ennemi->PV - tours*player->ATK;
                        else ennemi->PV=ennemi->PV - player->ATK;
                }

                if(strcmp(player->classe,"Knight")==0) ennemi->PV=ennemi->PV - player->ATK;

                if(strcmp(player->classe,"Vanguard")==0) ennemi->PV=ennemi->PV - player->ATK;

                break;
            case 2:
                printf("Vous avez decide de vous defendre\n");
                player->PV=player->PV+(ennemi->ATK/player->DEF);
                break;
            case 3:
                printf("Ouverture inventaire");
                break;
            case 4:
                printf("Vous etes un gros lache, vous n'avez pas l ame d un guerrier... honte a vous !\n");
                break;

        }

        if(tours%3==0 && strcmp(player->classe,"Chevalier")==0) printf("Vous avez bloque une attaque");
        else player->PV=player->PV - ennemi->ATK;

        tours+=1;

    }

    if(player->PV<=0){
        printf("L aventure s'arrete malheureusement ici pour vous petit, j avais pourtant prevu de grands dessein pour vous jeune ame egaree... ");
    }

    if(ennemi->PV<=0){
        printf("Bien joue, Jeune aventurier !");
        carte[(DIMY-1)/2][(DIMX-1)/2]=0;
        player->XP=player->XP+ennemi->XP;

    }
}


void DeplacementJoueur(Joueur *p,int carte[DIMY][DIMX])
{
    int x,y;
    char touche;

    purgeSTDIN();
    touche=getc(stdin);

    x=p->position[0];
    y=p->position[1];

    if((touche==100) && (carte[x][y+1]!=4) && (x+1<DIMX-1)){//122
            p->position[1]=y+1;

    }
    if((touche==113) && (carte[x][y-1]!=4) && (y-1>0)){//115
        p->position[1]=y-1;
    }
    if((touche==122) && (carte[x-1][y]!=4) && (x+1>0)){//113
        p->position[0]=x-1;
    }
    if((touche==115) && (carte[x+1][y]!=4) && (y+1<DIMY+1)){//100
        p->position[0]=x+1;
    }

    system("cls");

    affichage(carte,p);

}


void Jeu(Game *p)
{
    int i,fin,tours,ind,choix;
    Joueur *player;
    Monstre *monstre;
    Univers *Cosmos;

    Cosmos=p->Galaxy1;
    player=p->player;
    fin=0;

    while(fin==0){
        if(Cosmos->level==1){
        tours=3;
        }

        if(Cosmos->level==2){
            tours=4;
        }

        if(Cosmos->level==3){
            tours=5;
        }

        for(i=0;i<tours;i++){
            init_monstre(&monstre,Cosmos->level);
            Cosmos->carte[(DIMY-1)/2][(DIMX-1)/2]=5;
            affichage(Cosmos->carte,player);

            while(monstre->PV>0){

                DeplacementJoueur(player,Cosmos->carte);
                if(player->position[0]==19 && player->position[1]==7){
                    recolte(Cosmos->carte,player);
                    affichage(Cosmos->carte,player);}

                if(player->position[0]==17 && player->position[1]==21){
                    recolte(Cosmos->carte,player);
                    affichage(Cosmos->carte,player);}

                if(player->position[0]==1 && player->position[1]==27){
                    recolte(Cosmos->carte,player);
                    affichage(Cosmos->carte,player);}

                if(player->position[0]==15 && player->position[1]==40){
                    recolte(Cosmos->carte,player);
                    affichage(Cosmos->carte,player);}

                if(player->position[0]==(DIMY-1)/2 && player->position[1]==(DIMX-1)/2){
                    Combat(Cosmos->carte,player,monstre);
                }

                if(player->position[0]==(DIMY-1)/2 && player->position[1]==DIMX-1){
                    ind=Test_Key(player->sacado);
                    if(ind==-1){
                        printf("Vous n avez pas la cle, revenez quand vous l aurez malotru !");
                        player->position[1]=player->position[1]-1;
                        affichage(Cosmos->carte,player);
                    }
                    else{
                        printf("Voulez vous passez au niveau suivant ?\n");
                        printf("1.Oui  2.Non\n");
                        scanf("%d",&choix);
                    }

                }

                if(choix==1) break;

            }
        }

        choix=0;

        Cosmos=Cosmos->suivante;
        initCarte(Cosmos->carte);
        sauvegarde_fichier(p,Cosmos);

        if(Cosmos==NULL) fin=1;
    }

    printf("Aah enfin vous voila...\n");
    printf("L'aventure fut rempli de nombreux obstacles mais vous avez su relever le defi.\nSoyez fiere de vous jeune aventurier, mais votre histoire ne s'arrete pas ici petit scarabe !\n");
    printf("Il vous reste encore d'autres mondes a decouvrir, que la force soit avec vous !");

}

///chargement d'une sauvegarde
void chargement_fichier(Game *partie)
{
    FILE *fichier;
    // Ouverture du fichier en lecture grâce à "r"
    fichier = fopen("save.txt ","r");
    // Verifier que le fichier a bien été ouvert
    if (fichier != NULL)
    {
        //perso
        partie->player->PV=fscanf(fichier,"%d\n",&partie->player->PV);
        partie->player->DEF=fscanf(fichier,"%d\n",&partie->player->DEF);
        partie->player->PM=fscanf(fichier,"%d\n",&partie->player->PM);
        partie->player->LVL=fscanf(fichier,"%d\n",&partie->player->LVL);
        partie->player->XP=fscanf(fichier,"%d\n",&partie->player->XP);
        partie->player->ATK=fscanf(fichier,"%d\n",&partie->player->ATK);
        partie->player->DEF=fscanf(fichier,"%d\n",&partie->player->DEF);
        partie->player->position[2]=fscanf(fichier,"%d\n",&partie->player->position[2]);
        partie->player->pseudo[20]=fscanf(fichier,"%s\n",&partie->player->pseudo[20]);
        partie->player->classe[20]=fscanf(fichier,"%s\n",&partie->player->classe[20]);
        //map
        //monstre

        // Fermeture du fichier
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de sauvegarder");
    }
}
void sauvegarde_fichier(Game *partie,Univers *cosmos)
{
    FILE *fichier;
    // Ouverture du fichier en ajout grâce à "a"
    fichier = fopen("save.txt ","a");
    // Verifier que le fichier a bien été ouvert
    if (fichier != NULL)
    {
        // Ecriture
        //perso
        int i,j;

        fprintf(fichier,"%d\n",partie->player->PV);
        fprintf(fichier,"%d\n",partie->player->DEF);
        fprintf(fichier,"%d\n",partie->player->PM);
        fprintf(fichier,"%d\n",partie->player->LVL);
        fprintf(fichier,"%d\n",partie->player->XP);
        fprintf(fichier,"%d\n",partie->player->ATK);
        fprintf(fichier,"%d\n",partie->player->DEF);
        fprintf(fichier,"%d\n",partie->player->position[0]);
        fprintf(fichier,"%d\n",partie->player->position[1]);
        fprintf(fichier,"%s\n",partie->player->pseudo);
        fprintf(fichier,"%s\n",partie->player->classe);

        //map

        for(i=0;i<DIMY;i++)
        {
            for(j=0;j<DIMX;j++)
            {
               fprintf(fichier,"%d",cosmos->carte[i][j]);
            }
        }


        //monstre



        // Fermeture du fichier
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de sauvegarder");
    }
}
void libere(Game *partie)
{
    free(partie->player);
    free(partie->Galaxy1);
    free(partie->Galaxy2);
    free(partie->Galaxy3);
    free(partie);

}


int Test_Key(int tab[])
{
    int i;

    int VerifKey=-1;

    for(i=0;i<TAILLE_SAC;i++){
      if(tab[i]==45){
        VerifKey=i;
      }
    }

    if(VerifKey!=-1){
      printf("Mon precieuuuuux !!!");
    }
    else{
      printf("Vous resterez coincés encore dans ce donjon");
    }

    return VerifKey;
}

int Test_sac(int sac[])
{
    int i=1;

    while(sac[i]!=0 && i<TAILLE_SAC+1){
        i++;
    }

    if(i>TAILLE_SAC){
        printf("le sac est plein");
        return -1;
    }
    else return i;
}

void recolte(int carte[DIMY][DIMX],Joueur *player)
{
    int x,y,choix,i;
    x=player->position[0];
    y=player->position[1];
    if(carte[x][y]==6)
    {
        printf("voulez vous prendre l'objet ? \n 1:oui 2:non\n");
        scanf("%d",&choix);
        if (choix==1)
        {
            i=Test_sac(player->sacado);
            if(i!=-1)player->sacado[i]=105;
            carte[x][y]=3;
        }
    }
    if(carte[x][y]==7)
    {
        printf("voulez vous prendre l'objet ? \n 1:oui 2:non\n");
        scanf("%d",&choix);
        if (choix==1)
        {
            i=Test_sac(player->sacado);
            if(i!=-1)player->sacado[i]=104;
            carte[x][y]=3;
            system("cls");
        }
    }
    if(carte[x][y]==8)
    {
        printf("voulez vous prendre l'objet ? \n 1:oui 2:non\n");
        scanf("%d",&choix);
        if (choix==1)
        {
            i=Test_sac(player->sacado);
            if(i!=-1)player->sacado[i]=112;
            carte[x][y]=3;
            system("cls");
        }
    }
    if(carte[x][y]==9)
    {
        printf("voulez vous prendre l'objet ? \n 1:oui 2:non\n");
        scanf("%d",&choix);
        if (choix==1)
        {
            i=Test_sac(player->sacado);
            if(i!=-1)player->sacado[i]=119;
            carte[x][y]=3;
            system("cls");
        }
    }
}
