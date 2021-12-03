#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define DIMX 62
#define DIMY 31
#define TAILLE_SAC 4

typedef struct Joueur Joueur;
struct Joueur{
char pseudo[20];
char classe[20];
int sexe;
int PV;
int DEF;
int PM;
int LVL;
int XP;
int ATK;
int position[2];
int sacado[TAILLE_SAC];
int portefeuille;
};

typedef struct Univers Univers;
struct Univers{
int carte[DIMY][DIMX];
int level;
Univers *suivante;
};

typedef struct Game Game;
struct Game{
Joueur *player;
Univers *Galaxy1;
Univers *Galaxy2;
Univers *Galaxy3;
int time;

};



typedef struct Monstre Monstre;
struct Monstre{
int representation;
char nom[20];
int PV;
int XP;
int ATK;
};

void* malloc_p(size_t s);
int Menu();
void initGame(Game **partie);
void initCarte(int carte[DIMY][DIMX]);
void affichage(int carte[DIMY][DIMX],Joueur *p);
void DistributeurCapa(Joueur **p,int val);
void initJoueur(Joueur **p);
void init_monstre(Monstre **self,int nv_map);
//void deplament_monstre(int **carte,Monstre *monstre);
void Combat(int carte[DIMY][DIMX],Joueur *player,Monstre *ennemi);
void DeplacementJoueur(Joueur *p,int carte[DIMY][DIMX]);
void Jeu(Game *p);
void chargement_fichier();
void sauvegarde_fichier(Game *partie,Univers *cosmos);
int Test_Key(int *tab);
void recolte(int carte[DIMY][DIMX],Joueur *player);
int Test_sac(int sac[]);

#endif // PARAMETRES_H_INCLUDED
