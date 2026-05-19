#include <stdio.h>    // Bibliothèque pour utiliser printf et fgets (affichage et saisie)
#include <stdlib.h>   // Bibliothèque pour utiliser atoi (convertir du texte en chiffre)
#include "qcm_structure.h" // Contient nos structures
#include "teachers.h"      // Permet de faire le lien avec les fonctions du prof
#include "student.h"       // Permet de faire le lien avec les fonctions de l'étudiant

/* ================= COULEURS ================= */
#define COLOR_RESET   "\033[0m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_PINK   "\033[1;35m"
/* ================================================= */

int main() {
    int choix;        // Stocke le choix final de l'utilisateur (1, 2 ou 3)
    char saisie[50];  // Récupère ce que l'utilisateur tape au clavier

    // On utilise une boucle "do... while" : le menu s'affiche au moins une fois, et s'affiche tant que l'utilisateur ne tape pas 3.
    do {
        // --- AFFICHAGE DU MENU PRINCIPAL ---
        printf(COLOR_BLUE "\n==========================================\n" COLOR_RESET);
        printf(COLOR_BLUE "          QUESTIONS POUR UN TEKIEN\n" COLOR_RESET); 
        printf(COLOR_BLUE "==========================================\n" COLOR_RESET);
        
        printf(COLOR_RED   " 1 - Mode Enseignant (Creer un QCM)\n" COLOR_RESET);
        printf(COLOR_GREEN " 2 - Mode Etudiant (Passer un QCM)\n" COLOR_RESET);
        printf(COLOR_PINK" 3 - Quitter l'application\n" COLOR_RESET);
        
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
                launchTeacherMode(); // On appelle la fonction du fichier teachers.c
                break; // On sort du switch

            case 2:
                printf("\n[Lancement du Mode Etudiant]\n");
                launchStudentMode(); // On appelle la fonction du fichier student.c
                break;

            case 3:
                // Le programme sort de la boucle après ça
                printf("\nAu revoir ! Merci d'avoir utilise l'application.\n\n");
                break;

            default:
                // Si l'utilisateur tape 4, 0 ou des lettres (atoi renvoie 0), on affiche une erreur
                printf(COLOR_RED "\n--- Erreur : Saisie invalide ! ---\n");
                printf("--- Veuillez entrer un chiffre entre 1 et 3. ---\n\n" COLOR_RESET);
                break;
        }

    } while (choix != 3); // La boucle s'arrête que si choix vaut 3

    return 0;
}
