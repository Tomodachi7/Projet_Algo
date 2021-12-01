#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parametres.h"

int main()
{
    int choix;
    Game *partie;

    choix=0;

    while(choix!=4){
        choix=Menu();

        switch(choix)
        {
        case 1:
            initGame(&partie);
            printf("podd\n");
            Jeu(partie);
            break;
        case 2:
            chargement_fichier();
            break;
        case 3:
            //fonction pour supprimer une sauvegarde
            break;
        case 4:
            break;
        default:
            printf("Choisissez correctement\n");
            break;
        }
    }



    return 0;
}
