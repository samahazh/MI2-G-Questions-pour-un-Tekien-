#include <stdio.h>    // Bibliothèque pour utiliser printf et fgets (affichage et saisie)
#include <stdlib.h>   // Bibliothèque pour utiliser atoi (convertir du texte en chiffre)
#include <string.h>   // Bibliothèque pour manipuler les chaines de caracteres (ex: strcmp, strcspn)
#include "qcm_structure.h" // Contient nos structures
#include "teachers.h"      

/* ================= COULEURS ================= */
#define COLOR_RESET  "\033[0m"
#define COLOR_BLUE   "\033[1;34m"
#define COLOR_RED    "\033[1;31m"
#define COLOR_GREEN  "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m" 
/* ===================================================== */

void launchTeacherMode() {
    char motDePasseSaisi[50]; // Tableau pour stocker le mot de passe tapé par l'utilisateur
    const char vraiMotDePasse[] = "prof123"; // Le mot de passe secret 
    char bufferSaisie[MAX_TEXT]; // Zone temporaire pour lire les saisies texte

    // --- AFFICHAGE DU MENU ENSEIGNANT ---
    printf(COLOR_RED "\n==========================================\n" COLOR_RESET);
    printf(COLOR_RED "             MODE ENSEIGNANT\n" COLOR_RESET);
    printf(COLOR_RED "==========================================\n" COLOR_RESET);
    printf("Mot de passe requis : ");
    
    // --- VÉRIFICATION DU MOT DE PASSE ---
    fgets(motDePasseSaisi, sizeof(motDePasseSaisi), stdin); // On lit ce que l'utilisateur tape
    // Comme fgets garde la touche \n à la fin, on l'enlève en la remplaçant par \0 
    motDePasseSaisi[strcspn(motDePasseSaisi, "\n")] = 0;

    // strcmp compare deux textes. S'ils sont identiques, elle renvoie 0.
    // Si c'est différent de 0, c'est que le mot de passe est faux.
    if (strcmp(motDePasseSaisi, vraiMotDePasse) != 0) {
        printf(COLOR_RED "\nMot de passe incorrect ! Acces refuse.\n" COLOR_RESET);
        return; // On stoppe la fonction et on retourne au menu principal
    }

    // Si on arrive ici, c'est que le mot de passe est bon
    printf(COLOR_GREEN "\nConnexion reussie ! Bienvenue dans l'espace de creation.\n" COLOR_RESET);

    // --- PRÉPARATION DU QCM ---
    QCM nouveauQCM; // On crée une variable "nouveauQCM" 
    char nomFichier[100]; // Pour stocker le nom du fichier

    printf(COLOR_RED "\n------------------------------------------\n" COLOR_RESET);
    printf(COLOR_RED "           CONFIGURATION DU QCM\n" COLOR_RESET);
    printf(COLOR_RED "------------------------------------------\n" COLOR_RESET);
    
    printf("Nom du fichier a creer (ex: quizz.bin) : ");
    fgets(nomFichier, sizeof(nomFichier), stdin);
    nomFichier[strcspn(nomFichier, "\n")] = 0; // On retire toujours le '\n' ajouté par fgets

    // Configuration
    printf("Nombre de questions : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.num_questions = atoi(bufferSaisie); // atoi transforme le texte saisi en vrai nombre 

    printf("Activer les points negatifs ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.rules.negative_points = atoi(bufferSaisie); // On enregistre ce choix dans les règles 

    printf("Activer les reponses multiples ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.rules.multiple_answers = atoi(bufferSaisie);

    printf("Activer le mode sequentiel ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.rules.sequential_mode = atoi(bufferSaisie);

    // --- CRÉATION DES QUESTIONS ---
    // Cette boucle tourne autant de fois qu'il y a de questions choisies
    for (int i = 0; i < nouveauQCM.num_questions; i++) {
        printf(COLOR_RED "\nQuestion %d :\n" COLOR_RESET, i + 1);
        printf("  Enonce : ");
        fgets(nouveauQCM.questions[i].statement, MAX_TEXT, stdin);
        nouveauQCM.questions[i].statement[strcspn(nouveauQCM.questions[i].statement, "\n")] = 0;

        // Cette boucle sert à demander les propositions (MAX_OPTIONS fois) pour chaque question
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("  Proposition %d : ", j + 1);
            fgets(nouveauQCM.questions[i].options[j], MAX_TEXT, stdin);
            nouveauQCM.questions[i].options[j][strcspn(nouveauQCM.questions[i].options[j], "\n")] = 0;
            
            printf("  Est-elle vraie ? (1=Oui, 0=Non) : ");
            fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
            // On enregistre si cette proposition est la bonne réponse (1) ou non (0)
            nouveauQCM.questions[i].correct_answers[j] = atoi(bufferSaisie);
        }
    }

    // --- SAUVEGARDE DANS LE FICHIER ---
    // "wb" Write Binary : on ouvre le fichier pour y écrire des données binaires
    FILE *f = fopen(nomFichier, "wb");
    if (f != NULL) { // Si le fichier s'est bien ouvert
        // On prend TOUTE la variable nouveauQCM, et on copie sa taille dans le fichier
        fwrite(&nouveauQCM, sizeof(QCM), 1, f);
        fclose(f); // On ferme le fichier
        printf(COLOR_GREEN "\nLe QCM a ete sauvegarde avec succes dans '%s' !\n\n" COLOR_RESET, nomFichier);
    } else { 
        // Si l'ordinateur refuse de créer le fichier 
        printf(COLOR_RED "Erreur lors de la creation du fichier.\n" COLOR_RESET);
    }
}