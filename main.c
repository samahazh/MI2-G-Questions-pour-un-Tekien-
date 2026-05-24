#include <stdio.h>   
#include <stdlib.h>  
#include "qcm_structure.h" 
#include "enseignant.h"    // Permet de faire le lien avec les fonctions de l'enseignant.
#include "etudiant.h"      // Permet de faire le lien avec les fonctions de l'étudiant.

/*
 * Code principal de l'application "Questions pour un Tekien".
 * Affiche le menu principal et redirige vers le mode choisi.
 */
int main() {
    int choix;
    char saisie[50];

    // Boucle do...while : le menu s'affiche au moins une fois, et s'affiche tant que l'utilisateur ne tape pas 3.
    do {
        printf(COULEUR_BLEU "\n==========================================\n" COULEUR_DEFAUT);
        printf(COULEUR_BLEU "          QUESTIONS POUR UN TEKIEN\n" COULEUR_DEFAUT); 
        printf(COULEUR_BLEU "==========================================\n" COULEUR_DEFAUT);
        
        printf(COULEUR_ROUGE " 1 - Mode Enseignant (Creer un QCM)\n" COULEUR_DEFAUT);
        printf(COULEUR_VERT  " 2 - Mode Etudiant (Passer un QCM)\n" COULEUR_DEFAUT);
        printf(COULEUR_ROSE  " 3 - Quitter l'application\n" COULEUR_DEFAUT);
        
        printf("------------------------------------------\n");
        printf("Veuillez entrer votre choix (1 a 3) : ");

        // Récupération de la saisie :
        if (fgets(saisie, sizeof(saisie), stdin) != NULL) {
            choix = atoi(saisie);
        } else {
            choix = 0;
        }

        switch (choix) {
            case 1:
                lancerModeEnseignant(); 
                break;

            case 2:
                lancerModeEtudiant(); 
                break;

            case 3:
                printf("\nAu revoir ! Merci d'avoir utilise l'application.\n\n");
                break;

            default:
                // Si l'utilisateur tape 4, 0 ou des lettres (atoi renvoie 0), on affiche une erreur
                printf(COULEUR_ROUGE "  -> Erreur : saisie invalide ! Veuillez entrer un chiffre entre 1 et 3.\n"COULEUR_DEFAUT);
                break;
        }

    } while (choix != 3); // La boucle s'arrête que si choix vaut 3

    return 0;
}