#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED

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
Joueur player;
char **MAP;
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

#endif // PARAMETRES_H_INCLUDED
