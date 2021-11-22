#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parametres.h"

int main()
{
    int choix;
    Game *partie;
    printf("bash adventure\n\n bienvenue\n\n");

    printf("--menu--\n");
    printf("1-jouer\n");
    printf("2charger une sauvegarde\n");
    printf("3-supprimer une sauvegarde\n");
    printf("4-quitter\n");
    scanf("%d",&choix);
    system("cls");
    switch(choix)
    {
    case 1:
        initGame(&partie);
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
