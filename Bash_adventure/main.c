#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parametres.h"

int main()
{
    int choix;
    Game *partie;
    //printf("bash adventure\n\n bienvenue\n\n");
    Menu();
    printf("--Menu--\n");
    printf("1-Jouer\n");
    printf("2-Charger une sauvegarde\n");
    printf("3-Supprimer une sauvegarde\n");
    printf("4-Quitter\n");
    scanf("%d",&choix);
    //system("cls");
    switch(choix)
    {
    case 1:
        initGame(&partie);
        Jeu(partie);
        break;
    case 2:
        //fonction charger supp sauvegarde
        break;
    case 3:
        //fonction pour explique comment on joue
        break;
    case 4:
        break;
    default:
        printf("choisi correctement\n");
        break;
    }


    return 0;
}
