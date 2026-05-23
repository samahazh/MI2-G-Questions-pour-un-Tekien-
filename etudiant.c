#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include "qcm_structure.h" 
#include "etudiant.h"      // Permet de faire le lien avec les fonctions de l'étudiant

// Couleurs :
#define COULEUR_DEFAUT "\033[0m"
#define TEXTE_GRAS     "\033[1m"
#define COULEUR_BLEU   "\033[1;34m"
#define COULEUR_ROUGE  "\033[1;31m"
#define COULEUR_VERT   "\033[1;32m"
#define COULEUR_ROSE   "\033[1;35m" 

/*
 * Gère la saisie de l'étudiant pour une question a choix multiples.
 * Remplit le tableau choixEleveTableau et retourne 1 s'il a répondu, 0 s'il a passée.
 */
int gererChoixMultiples(QCM *monQuiz, int choixEleveTableau[]) {
    char saisie[MAX_TEXTE];
    int nbChoix = -1;
    int aRepondu = 0;
    
    do {
        if (monQuiz->regles.mode_sequentiel == 1) {
            printf("\nCombien de reponses ? (1 a %d) : ", MAX_CHOIX);
        } else {
            printf("\nCombien de reponses voulez-vous donner ? (1 a %d, ou 0 pour passer) : ", MAX_CHOIX);
        }

        fgets(saisie, sizeof(saisie), stdin);

        if (saisie[0] != '\n' && saisie[0] != '0' && atoi(saisie) == 0) {
            printf(COULEUR_ROUGE "  -> Erreur : veuillez entrer un chiffre.\n" COULEUR_DEFAUT);
            nbChoix = -1;
        } else {
            if ((saisie[0] == '\n' || atoi(saisie) == 0) && monQuiz->regles.mode_sequentiel == 0) {
                nbChoix = 0; 
            } else if ((saisie[0] == '\n' || atoi(saisie) == 0) && monQuiz->regles.mode_sequentiel == 1) {
                printf(COULEUR_ROUGE "Mode sequentiel ! Vous devez repondre.\n" COULEUR_DEFAUT);
                nbChoix = -1; 
            } else {
                nbChoix = atoi(saisie);
                if (nbChoix < 1 || nbChoix > MAX_CHOIX) {
                    printf(COULEUR_ROUGE "  -> Erreur : choisissez un chiffre entre 1 et %d.\n" COULEUR_DEFAUT, MAX_CHOIX);
                }
            }
        }

        if (nbChoix == 0 && monQuiz->regles.mode_sequentiel == 0) {
            printf(COULEUR_ROUGE "Question passee.\n" COULEUR_DEFAUT);
            return 0; 
        }
    } while (nbChoix < 1 || nbChoix > MAX_CHOIX);

    for (int k = 0; k < nbChoix; k++) {
        int rep = -1;
        do {
            printf("  Donnez votre choix n%d : ", k + 1);
            fgets(saisie, sizeof(saisie), stdin);
            
            if (saisie[0] != '\n' && saisie[0] != '0' && atoi(saisie) == 0) {
                printf(COULEUR_ROUGE "  -> Erreur : veuillez entrer un chiffre.\n" COULEUR_DEFAUT);
                rep = -1;
            } else {
                rep = atoi(saisie);
                if (rep < 1 || rep > MAX_CHOIX) {
                    printf(COULEUR_ROUGE "  -> Erreur : choisissez un chiffre entre 1 et %d.\n" COULEUR_DEFAUT, MAX_CHOIX);
                }
            }
        } while (rep < 1 || rep > MAX_CHOIX);

        choixEleveTableau[rep - 1] = 1;
        aRepondu = 1;
    }
    return aRepondu;
}

/*
 * Gère la saisie de l'étudiant pour une question a choix unique.
 * Remplit le tableau choixEleveTableau et retourne 1 s'il a repondu, 0 s'il a passée.
 */
int gererChoixUnique(QCM *monQuiz, int choixEleveTableau[]) {
    char saisie[MAX_TEXTE];
    int choixEleve = -1;

    do {
        if (monQuiz->regles.mode_sequentiel == 1) {
            printf("\nVotre reponse (1 a %d) : ", MAX_CHOIX);
        } else {
            printf("\nVotre reponse (1 a %d, ou 0 pour passer) : ", MAX_CHOIX);
        }

        fgets(saisie, sizeof(saisie), stdin);

        if (saisie[0] != '\n' && saisie[0] != '0' && atoi(saisie) == 0) {
            printf(COULEUR_ROUGE "  -> Erreur : veuillez entrer un chiffre.\n" COULEUR_DEFAUT);
            choixEleve = -1;
        } else {
            if ((saisie[0] == '\n' || atoi(saisie) == 0) && monQuiz->regles.mode_sequentiel == 0) {
                choixEleve = 0;
            } else if ((saisie[0] == '\n' || atoi(saisie) == 0) && monQuiz->regles.mode_sequentiel == 1) {
                printf(COULEUR_ROUGE "Mode sequentiel ! Vous devez repondre.\n" COULEUR_DEFAUT);
                choixEleve = -1;
            } else {
                choixEleve = atoi(saisie);
                if (choixEleve < 1 || choixEleve > MAX_CHOIX) {
                    printf(COULEUR_ROUGE "  -> Erreur : choisissez un chiffre entre 1 et %d.\n" COULEUR_DEFAUT, MAX_CHOIX);
                }
            }
        }

        if (choixEleve == 0 && monQuiz->regles.mode_sequentiel == 0) {
            printf(COULEUR_ROUGE "Question passee.\n" COULEUR_DEFAUT);
            return 0; // Il n'a rien repondu
        }
    } while (choixEleve < 1 || choixEleve > MAX_CHOIX);

    choixEleveTableau[choixEleve - 1] = 1;
    return 1;
}

/*
 * Affiche la correction detaillee et la note finale de l'étudiant.
 */
void afficherCorrection(QCM monQuiz, float scoreFinal) {
    printf(COULEUR_VERT "\n==========================================\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "      RECAPITULATIF DES BONNES REPONSES\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "==========================================\n" COULEUR_DEFAUT);

    for (int i = 0; i < monQuiz.nb_questions; i++) {
        printf(TEXTE_GRAS "Q%d : %s\n" COULEUR_DEFAUT, i + 1, monQuiz.questions[i].enonce);
        printf("   => La bonne reponse etait : ");
        
        for (int j = 0; j < MAX_CHOIX; j++) {
            if (monQuiz.questions[i].bonnes_reponses[j] == 1) { 
                printf(COULEUR_VERT "[%s] " COULEUR_DEFAUT, monQuiz.questions[i].propositions[j]);
            }
        }
        printf("\n");
    }

    float noteSur20 = 0;
    if (monQuiz.nb_questions > 0) {
        noteSur20 = (scoreFinal / monQuiz.nb_questions) * 20;
    }
    if (noteSur20 < 0) noteSur20 = 0;

    printf(COULEUR_VERT "\n------------------------------------------\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "              RESULTAT FINAL\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "------------------------------------------\n" COULEUR_DEFAUT);
    printf("Votre note : %.2f / 20\n", noteSur20);
    printf(COULEUR_VERT "==========================================\n\n" COULEUR_DEFAUT);
}

/*
 * Fonction principale du mode Etudiant.
 * Ouvre le fichier, gère le déroulement du QCM et calcule le score.
 */
void lancerModeEtudiant() {
    QCM monQuiz; 
    char saisie[MAX_TEXTE]; 

    printf(COULEUR_VERT "\n==========================================\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "              MODE ETUDIANT\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "==========================================\n" COULEUR_DEFAUT);
    
    printf("Entrez le nom du fichier QCM a ouvrir (ex: quizz.bin) : ");
    fgets(saisie, sizeof(saisie), stdin); 
    saisie[strcspn(saisie, "\n")] = 0; 

    FILE *f = fopen(saisie, "rb");
    if (f != NULL) { 
        fread(&monQuiz, sizeof(QCM), 1, f);
        fclose(f); 
    } else { 
        printf(COULEUR_ROUGE "\nImpossible de trouver le fichier '%s'\n" COULEUR_DEFAUT, saisie);
        return; 
    }

    printf(COULEUR_BLEU "\n=======================================================\n" COULEUR_DEFAUT);
    printf(COULEUR_BLEU "  Bienvenue dans le QCM : %s\n" COULEUR_DEFAUT, monQuiz.nom);
    printf(COULEUR_BLEU "=======================================================\n" COULEUR_DEFAUT);

    float scoreFinal = 0; 

    for (int i = 0; i < monQuiz.nb_questions; i++) {
        int choixEleveTableau[MAX_CHOIX] = {0}; 
        int aReponduQuelqueChose = 0; 

        printf(TEXTE_GRAS "\n------------------------------------------\n" COULEUR_DEFAUT);
        printf(TEXTE_GRAS "Question %d : %s\n" COULEUR_DEFAUT, i + 1, monQuiz.questions[i].enonce);

        if (monQuiz.regles.reponses_multiples == 1) {
            printf(COULEUR_ROSE "(Plusieurs reponses possibles)\n" COULEUR_DEFAUT);
        }
        
        for (int j = 0; j < MAX_CHOIX; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.questions[i].propositions[j]);
        }

        if (monQuiz.regles.reponses_multiples == 1) {
            aReponduQuelqueChose = gererChoixMultiples(&monQuiz, choixEleveTableau);
        } else {
            aReponduQuelqueChose = gererChoixUnique(&monQuiz, choixEleveTableau);
        }

        int correct = 1; 
        for (int j = 0; j < MAX_CHOIX; j++) {
            if (choixEleveTableau[j] != monQuiz.questions[i].bonnes_reponses[j]) {
                correct = 0;
                break; 
            }
        }

        if (aReponduQuelqueChose == 0) {
            printf(COULEUR_ROUGE "Aucune reponse donnee.\n" COULEUR_DEFAUT);
            if (monQuiz.regles.points_negatifs == 1) { 
                scoreFinal -= 0.5;
                printf(COULEUR_ROUGE "(Point retire : -0.5)\n" COULEUR_DEFAUT);
            }
        } else if (correct == 1) {
            printf(COULEUR_VERT "Bravo ! C'est juste.\n" COULEUR_DEFAUT);
            scoreFinal += 1;
        } else {
            printf(COULEUR_ROUGE "Dommage, c'est faux.\n" COULEUR_DEFAUT);
            if (monQuiz.regles.points_negatifs == 1) {
                scoreFinal -= 0.5;
                printf(COULEUR_ROUGE "(Point retire : -0.5)\n" COULEUR_DEFAUT);
            }
        }
    }

    afficherCorrection(monQuiz, scoreFinal);
}