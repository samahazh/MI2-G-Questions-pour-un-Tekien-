#include <stdio.h>    // Bibliothèque pour utiliser printf et fgets (affichage et saisie)
#include <stdlib.h>   // Bibliothèque pour utiliser atoi (convertir du texte en chiffre)
#include <string.h>   // Bibliothèque pour manipuler les chaines de caracteres (strcspn)
#include "qcm_structure.h" // Contient nos structures
#include "etudiant.h"      // Permet de faire le lien avec les fonctions de l'étudiant

/* ================= COULEURS  ================= */
#define COULEUR_DEFAUT "\033[0m"
#define TEXTE_GRAS     "\033[1m"
#define COULEUR_BLEU   "\033[1;34m"
#define COULEUR_ROUGE  "\033[1;31m"
#define COULEUR_VERT   "\033[1;32m"
#define COULEUR_JAUNE  "\033[1;33m" 
#define COULEUR_ROSE   "\033[1;35m" 
/* ===================================================== */

void lancerModeEtudiant() {
    QCM monQuiz; // Stock de toutes les données lues depuis le fichier
    char bufferSaisie[MAX_TEXTE]; // Zone mémoire temporaire pour sécuriser les saisies

    // --- AFFICHAGE DU MENU ETUDIANT ---
    printf(COULEUR_VERT "\n==========================================\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "              MODE ETUDIANT\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "==========================================\n" COULEUR_DEFAUT);
    
    printf("Entrez le nom du fichier QCM a ouvrir (ex: quizz.bin) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin); // Lecture du nom du fichier
    
    // fgets ajoute un retour a la ligne ('\n') a la fin. 
    // strcspn sert a trouver ce '\n' et a le remplacer par 0 pour avoir un nom de fichier propre.
    bufferSaisie[strcspn(bufferSaisie, "\n")] = 0; 

    // --- OUVERTURE ET LECTURE DU FICHIER ---
    // "rb" Read Binary : on lit le fichier en mode binaire
    FILE *f = fopen(bufferSaisie, "rb");
    if (f == NULL) { // Si le fichier n'existe pas
        printf(COULEUR_ROUGE "\nImpossible de trouver le fichier '%s'\n" COULEUR_DEFAUT, bufferSaisie);
        return; // On arrete tout et on retourne au menu principal
    }

    // On met tout le contenu du fichier dans la variable monQuiz
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f); // Fermer le fichier après l'avoir lu

    float scoreFinal = 0; // Le compteur de points de l'eleve

    // --- BOUCLE PRINCIPALE : DEFILEMENT DES QUESTIONS ---
    for (int i = 0; i < monQuiz.nb_questions; i++) {
        
        // Ce tableau sert de "brouillon" pour retenir les cases que l'élève a cochées (1 = coche, 0 = vide)
        int choixEleveTableau[MAX_CHOIX] = {0}; 
        int aReponduQuelqueChose = 0; // Un "drapeau" pour savoir si l'élève a passé la question

        printf(TEXTE_GRAS "\n------------------------------------------\n" COULEUR_DEFAUT);
        printf(TEXTE_GRAS "Question %d : %s\n" COULEUR_DEFAUT, i + 1, monQuiz.questions[i].enonce);

        // Si le prof à autorisé les réponses multiples lors de la création
        if (monQuiz.regles.reponses_multiples == 1) {
            printf(COULEUR_ROSE "(Plusieurs reponses possibles)\n" COULEUR_DEFAUT);
        }
        
        // Affichage des propositions (1 à MAX_CHOIX)
        for (int j = 0; j < MAX_CHOIX; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.questions[i].propositions[j]);
        }

        /* ===== GESTION DES QUESTIONS A CHOIX MULTIPLES ===== */
        if (monQuiz.regles.reponses_multiples == 1) {
            int nbChoix = -1;
            
            // Boucle do...while pour redemander tant que la saisie est invalide
            do {
                if (monQuiz.regles.mode_sequentiel == 1) {
                    printf("\nCombien de reponses ? (1 a %d) : ", MAX_CHOIX);
                } else {
                    printf("\nCombien de reponses voulez-vous donner ? (1 a %d, ou 0 pour passer) : ", MAX_CHOIX);
                }

                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);

                // Si c'est pas la touche Entree, pas le chiffre '0' et que atoi n'arrive pas a lire un chiffre (renvoie 0) -> c'est une lettre
                if (bufferSaisie[0] != '\n' && bufferSaisie[0] != '0' && atoi(bufferSaisie) == 0) {
                    printf(COULEUR_ROUGE "Erreur : Vous avez tape des lettres. Veuillez entrer un chiffre.\n" COULEUR_DEFAUT);
                    nbChoix = -1;
                } else {
                    // Si l'eleve tape juste "Entree" ou "0"
                    if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.regles.mode_sequentiel == 0) {
                        nbChoix = 0; // Il a le droit de passer
                    } else if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.regles.mode_sequentiel == 1) {
                        printf(COULEUR_ROUGE "Mode sequentiel ! Vous devez repondre.\n" COULEUR_DEFAUT);
                        nbChoix = -1; // Il doit recommencer
                    } else {
                        // On verifie qu'elle ne depasse pas le nombre d'options
                        nbChoix = atoi(bufferSaisie);
                        if (nbChoix < 1 || nbChoix > MAX_CHOIX) {
                            printf(COULEUR_ROUGE "Erreur : Choisissez un chiffre entre 1 et %d.\n" COULEUR_DEFAUT, MAX_CHOIX);
                        }
                    }
                }

                // L'eleve a volontairement saute la question
                if (nbChoix == 0 && monQuiz.regles.mode_sequentiel == 0) {
                    printf(COULEUR_ROUGE "Question passee.\n" COULEUR_DEFAUT);
                    break;
                }
            } while (nbChoix < 1 || nbChoix > MAX_CHOIX);

            // Pour chaque reponse qu'il veut donner, on lui demande son choix
            for (int k = 0; k < nbChoix; k++) {
                int rep = -1;
                do {
                    printf("  Donnez votre choix n%d : ", k + 1);
                    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
                    
                    // Sécurité pour les lettres
                    if (bufferSaisie[0] != '\n' && bufferSaisie[0] != '0' && atoi(bufferSaisie) == 0) {
                        printf(COULEUR_ROUGE "Erreur : Vous avez tape des lettres. Veuillez entrer un chiffre.\n" COULEUR_DEFAUT);
                        rep = -1;
                    } else {
                        rep = atoi(bufferSaisie);
                        if (rep < 1 || rep > MAX_CHOIX) {
                            printf(COULEUR_ROUGE "Erreur : Choisissez un chiffre valide entre 1 et %d.\n" COULEUR_DEFAUT, MAX_CHOIX);
                        }
                    }
                } while (rep < 1 || rep > MAX_CHOIX);

                // On "coche" la case correspondante dans le brouillon de l'eleve
                if (rep >= 1 && rep <= MAX_CHOIX) {
                    choixEleveTableau[rep - 1] = 1;
                    aReponduQuelqueChose = 1;
                }
            }
        }
        
        /* ===== GESTION DES QUESTIONS A CHOIX UNIQUE ===== */
        else {
            int choixEleve = -1;
            do {
                if (monQuiz.regles.mode_sequentiel == 1) {
                    printf("\nVotre reponse (1 a %d) : ", MAX_CHOIX);
                } else {
                    printf("\nVotre reponse (1 a %d, ou 0 pour passer) : ", MAX_CHOIX);
                }

                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);

                if (bufferSaisie[0] != '\n' && bufferSaisie[0] != '0' && atoi(bufferSaisie) == 0) {
                    printf(COULEUR_ROUGE "Erreur : Vous avez tape des lettres. Veuillez entrer un chiffre.\n" COULEUR_DEFAUT);
                    choixEleve = -1;
                } else {
                    if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.regles.mode_sequentiel == 0) {
                        choixEleve = 0;
                    } else if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.regles.mode_sequentiel == 1) {
                        printf(COULEUR_ROUGE "Mode sequentiel ! Vous devez obligatoirement repondre.\n" COULEUR_DEFAUT);
                        choixEleve = -1;
                    } else {
                        choixEleve = atoi(bufferSaisie);
                        if (choixEleve < 1 || choixEleve > MAX_CHOIX) {
                            printf(COULEUR_ROUGE "Erreur : Choisissez un chiffre valide entre 1 et %d.\n" COULEUR_DEFAUT, MAX_CHOIX);
                        }
                    }
                }

                if (choixEleve == 0 && monQuiz.regles.mode_sequentiel == 0) {
                    printf(COULEUR_ROUGE "Question passee.\n" COULEUR_DEFAUT);
                    break;
                }
            } while (choixEleve < 1 || choixEleve > MAX_CHOIX);

            if (choixEleve >= 1 && choixEleve <= MAX_CHOIX) {
                choixEleveTableau[choixEleve - 1] = 1;
                aReponduQuelqueChose = 1;
            }
        }

        // --- VERIFICATION ET SCORE ---
        int correct = 1; // On part du principe qu'il a bon
        for (int j = 0; j < MAX_CHOIX; j++) {
            // on compare chaque case de son brouillon avec les vraies reponses, s'il y a une difference, c'est faux
            if (choixEleveTableau[j] != monQuiz.questions[i].bonnes_reponses[j]) {
                correct = 0;
                break; // Inutile de verifier le reste, on arrete la boucle
            }
        }

        // Attribution ou retrait des points
        if (aReponduQuelqueChose == 0) {
            printf(COULEUR_ROUGE "Aucune reponse donnee. Aucun point n'est accorde.\n" COULEUR_DEFAUT);
            if (monQuiz.regles.points_negatifs == 1) { // Si les points negatifs sont actifs
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

    // --- RECAPITULATIF ---
    printf(COULEUR_VERT "\n==========================================\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "      RECAPITULATIF DES BONNES REPONSES\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "==========================================\n" COULEUR_DEFAUT);

    // On re-parcourt toutes les questions pour afficher la correction
    for (int i = 0; i < monQuiz.nb_questions; i++) {
        printf(TEXTE_GRAS "Q%d : %s\n" COULEUR_DEFAUT, i + 1, monQuiz.questions[i].enonce);
        printf("   => La bonne reponse etait : ");
        
        for (int j = 0; j < MAX_CHOIX; j++) {
            if (monQuiz.questions[i].bonnes_reponses[j] == 1) { // On cherche les propositions vraies
                printf(COULEUR_VERT "[%s] " COULEUR_DEFAUT, monQuiz.questions[i].propositions[j]);
            }
        }
        printf("\n");
    }

    // --- CALCUL ET AFFICHAGE DE LA NOTE FINALE ---
    float noteSur20 = 0;
    if (monQuiz.nb_questions > 0) {
        // Ramener le score sur 20
        noteSur20 = (scoreFinal / monQuiz.nb_questions) * 20;
    }
    
    // Un etudiant ne peut pas avoir une note inferieure a 0
    if (noteSur20 < 0) noteSur20 = 0;

    printf(COULEUR_VERT "\n------------------------------------------\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "              RESULTAT FINAL\n" COULEUR_DEFAUT);
    printf(COULEUR_VERT "------------------------------------------\n" COULEUR_DEFAUT);
    
    printf("Votre note : %.2f / 20\n", noteSur20);
    
    printf(COULEUR_VERT "==========================================\n\n" COULEUR_DEFAUT);
}
