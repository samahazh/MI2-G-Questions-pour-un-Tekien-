#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  
#include "qcm_structure.h"
#include "enseignant.h" // Permet de faire le lien avec les fonctions de l'enseignant.

/*
 * Force l'utilisateur à entrer un nom de fichier se terminant par ".bin".
 * Boucle tant que la saisie est invalide.
 * Paramètres : le tableau où la fonction va stocker le nom tapé.
 */
void demanderNomFichier(char nomFichier[]) {
    int valide = 0;
    do {
        fgets(nomFichier, 100, stdin);
        nomFichier[strcspn(nomFichier, "\n")] = 0;  // Supprime le saut de ligne '\n' ajouté automatiquement par fgets.
        
        int taille = strlen(nomFichier);
       
        // On vérifie que le nom est assez long et on compare les 4 derniers caractères avec ".bin".
        if (taille >= 5 && strcmp(&nomFichier[taille - 4], ".bin") == 0) {
            valide = 1;
        } else {
            printf(COULEUR_ROUGE "  -> Erreur : le nom du fichier doit se terminer par '.bin' (ex: quizz.bin) : " COULEUR_DEFAUT);
        }
    } while (valide == 0);
}

/*
 * Force l'utilisateur à taper uniquement 0 ou 1.
 * Boucle tant que la saisie est invalide.
 * Renvoie : le choix sécurisé.
 */
int demanderOuiNon() {
    char saisie[MAX_TEXTE];
    int choix = -1;
    do {
        fgets(saisie, sizeof(saisie), stdin);
        if (saisie[0] != '\n' && saisie[0] != '0' && atoi(saisie) == 0) {
            printf(COULEUR_ROUGE "  -> Erreur : veuillez taper 0 ou 1 : " COULEUR_DEFAUT);
        } else {
            choix = atoi(saisie);
            if (choix != 0 && choix != 1) {
                printf(COULEUR_ROUGE "  -> Erreur : veuillez taper 0 ou 1 : " COULEUR_DEFAUT);
            }
        }
    } while (choix != 0 && choix != 1);
    return choix;
}

/*
 * Force l'utilisateur à taper un nombre strictement supérieur à 0.
 * Sécurise le nombre de questions pour le QCM.
 * Boucle tant que la saisie est invalide.
 * Renvoie : le nombre de question sécurisé.
 */
int demanderNombrePositif() {
    char saisie[MAX_TEXTE];
    int nombre = 0;
    do {
        fgets(saisie, sizeof(saisie), stdin);

        if (saisie[0] != '\n' && saisie[0] != '0' && atoi(saisie) == 0) {
            printf(COULEUR_ROUGE "  -> Erreur : veuillez taper un nombre valide : " COULEUR_DEFAUT);
        } else {
            nombre = atoi(saisie);
            if (nombre <= 0) {
                printf(COULEUR_ROUGE "  -> Erreur : il faut au moins 1 question : " COULEUR_DEFAUT);
            }
            else if (nombre > MAX_QUESTIONS) {
                printf(COULEUR_ROUGE "  -> Erreur : le maximum est de %d questions : " COULEUR_DEFAUT, MAX_QUESTIONS);
            }
        }
    } while (nombre <= 0 || nombre > MAX_QUESTIONS);
    return nombre;
}

/*
 * Demande le mot de passe à l'enseignant et le vérifie.
 * Renvoie : 1 si le mot de passe est vrai, 0 si le mot de passe est faux.
 */
int verifierMotDePasse() {
    char motDePasseSaisi[50];
    char vraiMotDePasse[] = "prof123";
    
    printf(COULEUR_ROUGE "\n==========================================\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "                 MODE ENSEIGNANT\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "==========================================\n" COULEUR_DEFAUT);
    printf("Mot de passe requis : ");
    
    fgets(motDePasseSaisi, sizeof(motDePasseSaisi), stdin);
    motDePasseSaisi[strcspn(motDePasseSaisi, "\n")] = 0; 

    if (strcmp(motDePasseSaisi, vraiMotDePasse) != 0) {
        printf(COULEUR_ROUGE "\nMot de passe incorrect ! Acces refuse.\n" COULEUR_DEFAUT);
        return 0;
    }

    printf(COULEUR_VERT "\nConnexion reussie ! Bienvenue dans l'espace de creation.\n" COULEUR_DEFAUT);
    return 1;
}

/*
 * Enregistre la structure QCM remplie dans un fichier binaire.
 * Paramètres : le QCM à sauvegarder, le nom du fichier.
 */
void sauvegarderQCM(QCM qcm, char nomFichier[]) {
    FILE *f = fopen(nomFichier, "wb");
    if (f != NULL) { 
        fwrite(&qcm, sizeof(QCM), 1, f); // On écrit toute la structure QCM dans le fichier.
        fclose(f);
        printf(COULEUR_VERT "\nLe QCM a ete sauvegarde avec succes dans '%s' !\n\n" COULEUR_DEFAUT, nomFichier);
    } else { 
        printf(COULEUR_ROUGE "  -> Erreur lors de la creation du fichier.\n" COULEUR_DEFAUT);
    }
}

/*
 * Fonction principale du mode enseignant.
 * Elle permet l'authentification, la configuration, la création et la sauvegarde.
 */
void lancerModeEnseignant() {
    // Authentification :
    if (verifierMotDePasse() == 0) {
        return;
    }

    QCM nouveauQCM;
    char nomFichier[100];

    printf(COULEUR_ROUGE "\n-----------------------------------------------\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "               CONFIGURATION DU QCM\n" COULEUR_DEFAUT);
    printf(COULEUR_ROUGE "-----------------------------------------------\n" COULEUR_DEFAUT);
    
    printf("Nom du fichier a creer (ex: quizz.bin) : ");
    demanderNomFichier(nomFichier);

    printf("Quel est le titre de ce QCM ? : ");
    fgets(nouveauQCM.nom, sizeof(nouveauQCM.nom), stdin);
    nouveauQCM.nom[strcspn(nouveauQCM.nom, "\n")] = 0; 

    // Configuration du QCM :
    printf("Nombre de questions : ");
    nouveauQCM.nb_questions = demanderNombrePositif();

    printf("Activer les points negatifs ? (1=Oui, 0=Non) : ");
    nouveauQCM.regles.points_negatifs = demanderOuiNon();

    printf("Activer les reponses multiples ? (1=Oui, 0=Non) : ");
    nouveauQCM.regles.reponses_multiples = demanderOuiNon();

    printf("Activer le mode sequentiel ? (1=Oui, 0=Non) : ");
    nouveauQCM.regles.mode_sequentiel = demanderOuiNon();

    // Saisie des questions :
    for (int i = 0; i < nouveauQCM.nb_questions; i++) {
        printf(COULEUR_ROUGE "\nQuestion %d :\n" COULEUR_DEFAUT, i + 1);
        printf("  Enonce : ");
        fgets(nouveauQCM.questions[i].enonce, MAX_TEXTE, stdin);
        nouveauQCM.questions[i].enonce[strcspn(nouveauQCM.questions[i].enonce, "\n")] = 0;

        int aDejaUneBonneReponse = 0; // Sert de sécurité si le QCM est paramétré en "choix unique".

        for (int j = 0; j < MAX_CHOIX; j++) {
            printf("  Proposition %d : ", j + 1);
            fgets(nouveauQCM.questions[i].propositions[j], MAX_TEXTE, stdin);
            nouveauQCM.questions[i].propositions[j][strcspn(nouveauQCM.questions[i].propositions[j], "\n")] = 0;
            
            int estVraie = -1;
            do {
                printf("  Est-elle vraie ? (1=Oui, 0=Non) : ");
                estVraie = demanderOuiNon();

                if (nouveauQCM.regles.reponses_multiples == 0 && estVraie == 1 && aDejaUneBonneReponse == 1) {
                    printf(COULEUR_ROUGE "  -> Erreur : ce QCM est a choix unique, vous avez deja valide une bonne reponse !\n" COULEUR_DEFAUT);
                    estVraie = -1; 
                }
            } while (estVraie == -1);

            nouveauQCM.questions[i].bonnes_reponses[j] = estVraie;
            
            if (estVraie == 1) {
                aDejaUneBonneReponse = 1; 
            }
        }
    }
    
    // Sauvegarde :
    sauvegarderQCM(nouveauQCM, nomFichier);
}
