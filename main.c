#include <stdio.h>    // Bibliothèque pour utiliser printf et fgets (affichage et saisie)
#include <stdlib.h>   // Bibliothèque pour utiliser atoi (convertir du texte en chiffre)
#include "qcm_structure.h" // Contient nos structures
#include "enseignant.h"    // Permet de faire le lien avec les fonctions du prof
#include "etudiant.h"      // Permet de faire le lien avec les fonctions de l'étudiant

/* ================= COULEURS ================= */
#define COULEUR_DEFAUT "\033[0m"
#define COULEUR_BLEU   "\033[1;34m"
#define COULEUR_ROUGE  "\033[1;31m"
#define COULEUR_VERT   "\033[1;32m"
#define COULEUR_JAUNE  "\033[1;33m"
#define COULEUR_ROSE   "\033[1;35m"
/* ================================================= */

int main() {
    int choix;        // Stocke le choix final de l'utilisateur (1, 2 ou 3)
    char saisie[50];  // Récupère ce que l'utilisateur tape au clavier

    // On utilise une boucle "do... while" : le menu s'affiche au moins une fois, et s'affiche tant que l'utilisateur ne tape pas 3.
    do {
        // --- AFFICHAGE DU MENU PRINCIPAL ---
        printf(COULEUR_BLEU "\n==========================================\n" COULEUR_DEFAUT);
        printf(COULEUR_BLEU "          QUESTIONS POUR UN TEKIEN\n" COULEUR_DEFAUT); 
        printf(COULEUR_BLEU "==========================================\n" COULEUR_DEFAUT);
        
        printf(COULEUR_ROUGE " 1 - Mode Enseignant (Creer un QCM)\n" COULEUR_DEFAUT);
        printf(COULEUR_VERT  " 2 - Mode Etudiant (Passer un QCM)\n" COULEUR_DEFAUT);
        printf(COULEUR_ROSE  " 3 - Quitter l'application\n" COULEUR_DEFAUT);
        
        printf("------------------------------------------\n");
        printf("Veuillez entrer votre choix (1 a 3) : ");

        // --- RECUPERATION DE LA SAISIE ---
        // On recupère le texte tapé avec fgets
        if (fgets(saisie, sizeof(saisie), stdin) != NULL) {
            // atoi transforme le texte en entier
            choix = atoi(saisie);
        } else {
            choix = 0; // Sécurité si erreur de lecture
        }

        // --- REDIRECTION SELON LE CHOIX ---
        switch (choix) {
            case 1:
                printf("\n[Lancement du Mode Enseignant]\n");
                lancerModeEnseignant(); 
                break; // On sort du switch

            case 2:
                printf("\n[Lancement du Mode Etudiant]\n");
                lancerModeEtudiant(); 
                break;

            case 3:
                // Le programme sort de la boucle après ça
                printf("\nAu revoir ! Merci d'avoir utilise l'application.\n\n");
                break;

            default:
                // Si l'utilisateur tape 4, 0 ou des lettres (atoi renvoie 0), on affiche une erreur
                printf(COULEUR_ROUGE "\n--- Erreur : Saisie invalide ! ---\n");
                printf("--- Veuillez entrer un chiffre entre 1 et 3. ---\n\n" COULEUR_DEFAUT);
                break;
        }

    } while (choix != 3); // La boucle s'arrête que si choix vaut 3

    return 0;
}
