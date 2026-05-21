#include <stdio.h>    // Bibliothèque pour utiliser printf et fgets (affichage et saisie)
#include <stdlib.h>   // Bibliothèque pour utiliser atoi (convertir du texte en chiffre)
#include <string.h>   // Bibliothèque pour manipuler les chaines de caracteres (ex: strcmp, strcspn)
#include "qcm_structure.h" // Contient nos structures 
#include "enseignant.h"    // Permet de faire le lien avec les fonctions du prof

/* ================= COULEURS ================= */
#define COULEUR_DEFAUT "\033[0m"
#define COULEUR_BLEU   "\033[1;34m"
#define COULEUR_ROUGE  "\033[1;31m"
#define COULEUR_VERT   "\033[1;32m"
#define COULEUR_JAUNE  "\033[1;33m" 
/* ===================================================== */

void lancerModeEnseignant() {
    char motDePasseSaisi[50]; // Tableau pour stocker le mot de passe tapé par l'utilisateur
    const char vraiMotDePasse[] = "prof123"; // Le mot de passe secret 
    char bufferSaisie[MAX_TEXTE]; // Zone temporaire pour lire les saisies texte

    // --- AFFICHAGE DU MENU ENSEIGNANT ---
    printf(COULEUR_ROUGE "\n==========================================\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "             MODE ENSEIGNANT\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "==========================================\n" COULEUR_DEFAUT);
    printf("Mot de passe requis : ");
    
    // --- VÉRIFICATION DU MOT DE PASSE ---
    fgets(motDePasseSaisi, sizeof(motDePasseSaisi), stdin); // On lit ce que l'utilisateur tape
    // Comme fgets garde la touche \n à la fin, on l'enlève en la remplaçant par \0 
    motDePasseSaisi[strcspn(motDePasseSaisi, "\n")] = 0;

    // strcmp compare deux textes. S'ils sont identiques, elle renvoie 0.
    // Si c'est différent de 0, c'est que le mot de passe est faux.
    if (strcmp(motDePasseSaisi, vraiMotDePasse) != 0) {
        printf(COULEUR_ROUGE "\nMot de passe incorrect ! Acces refuse.\n" COULEUR_DEFAUT);
        return; // On stoppe la fonction et on retourne au menu principal
    }

    // Si on arrive ici, c'est que le mot de passe est bon
    printf(COULEUR_VERT "\nConnexion reussie ! Bienvenue dans l'espace de creation.\n" COULEUR_DEFAUT);

    // --- PRÉPARATION DU QCM ---
    QCM nouveauQCM; // On crée une variable "nouveauQCM" 
    char nomFichier[100]; // Pour stocker le nom du fichier

    printf(COULEUR_ROUGE "\n------------------------------------------\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "           CONFIGURATION DU QCM\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "------------------------------------------\n" COULEUR_DEFAUT);
    
    printf("Nom du fichier a creer (ex: quizz.bin) : ");
    fgets(nomFichier, sizeof(nomFichier), stdin);
    nomFichier[strcspn(nomFichier, "\n")] = 0; // On retire toujours le '\n' ajouté par fgets

    // Configuration
    printf("Nombre de questions : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.nb_questions = atoi(bufferSaisie); // atoi transforme le texte saisi en vrai nombre 

    printf("Activer les points negatifs ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.regles.points_negatifs = atoi(bufferSaisie); // On enregistre ce choix dans les règles 

    printf("Activer les reponses multiples ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.regles.reponses_multiples = atoi(bufferSaisie);

    printf("Activer le mode sequentiel ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.regles.mode_sequentiel = atoi(bufferSaisie);

    // --- CRÉATION DES QUESTIONS ---
    // Cette boucle tourne autant de fois qu'il y a de questions choisies
    for (int i = 0; i < nouveauQCM.nb_questions; i++) {
        printf(COULEUR_ROUGE "\nQuestion %d :\n" COULEUR_DEFAUT, i + 1);
        printf("  Enonce : ");
        fgets(nouveauQCM.questions[i].enonce, MAX_TEXTE, stdin);
        nouveauQCM.questions[i].enonce[strcspn(nouveauQCM.questions[i].enonce, "\n")] = 0;

        // Cette boucle sert à demander les propositions (MAX_CHOIX fois) pour chaque question
        for (int j = 0; j < MAX_CHOIX; j++) {
            printf("  Proposition %d : ", j + 1);
            fgets(nouveauQCM.questions[i].propositions[j], MAX_TEXTE, stdin);
            nouveauQCM.questions[i].propositions[j][strcspn(nouveauQCM.questions[i].propositions[j], "\n")] = 0;
            
            printf("  Est-elle vraie ? (1=Oui, 0=Non) : ");
            fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
            // On enregistre si cette proposition est la bonne réponse (1) ou non (0)
            nouveauQCM.questions[i].bonnes_reponses[j] = atoi(bufferSaisie);
        }
    }

    // --- SAUVEGARDE DANS LE FICHIER ---
    // "wb" Write Binary : on ouvre le fichier pour y écrire des données binaires
    FILE *f = fopen(nomFichier, "wb");
    if (f != NULL) { // Si le fichier s'est bien ouvert
        // On prend TOUTE la variable nouveauQCM, et on copie sa taille dans le fichier
        fwrite(&nouveauQCM, sizeof(QCM), 1, f);
        fclose(f); // On ferme le fichier
        printf(COULEUR_VERT "\nLe QCM a ete sauvegarde avec succes dans '%s' !\n\n" COULEUR_DEFAUT, nomFichier);
    } else { 
        // Si l'ordinateur refuse de créer le fichier 
        printf(COULEUR_ROUGE "Erreur lors de la creation du fichier.\n" COULEUR_DEFAUT);
    }
}
