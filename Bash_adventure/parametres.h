#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIMX 62
#define DIMY 31

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

typedef struct Univers Univers;
struct Univers{
int **carte;
Univers *suivante;
};

typedef struct Game Game;
struct Game{
Joueur *player;
int *map1[DIMY];
int *map2[DIMY];
int *map3[DIMY];
Univers *Galaxy;
int time;

};



typedef struct Monstre Monstre;
struct Monstre{
int representation;
int prec;
char nom[20];
int PV;
int PM;
int XP;
int ATK;
int VIT;
int position[2];
};

void* malloc_p(size_t s);
int Menu();
void initGame(Game **partie);
void Creation_map(int **carte);
void initCarte(int **carte);
void affichage(int **carte);
void DistributeurCapa(Joueur **p,int val);
void initJoueur(Joueur **p);
void init_monstre(Monstre **self,int nv_map);
void deplament_monstre(int **carte,Monstre *monstre);
void Combat(Joueur *player,Monstre *ennemi);
void DeplacementJoueur(Joueur *p,int **carte);
void Jeu(Game *p);
void chargement_fichier();
void sauvegarde_fichier(Game *partie);

#endif // PARAMETRES_H_INCLUDED
