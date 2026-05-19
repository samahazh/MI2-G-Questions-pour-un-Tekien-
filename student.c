#include <stdio.h>    // Bibliothèque pour utiliser printf et fgets (affichage et saisie)
#include <stdlib.h>   // Bibliothèque pour utiliser atoi (convertir du texte en chiffre)
#include <string.h>   // Bibliothèque pour manipuler les chaines de caracteres (strcspn)
#include "qcm_structure.h" // Contient nos structures
#include "student.h"

/* ================= COULEURS  ================= */
#define COLOR_RESET  "\033[0m"
#define TEXT_BOLD    "\033[1m"
#define COLOR_BLUE   "\033[1;34m"
#define COLOR_RED    "\033[1;31m"
#define COLOR_GREEN  "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m" 
#define COLOR_PINK   "\033[1;35m" 
/* ===================================================== */

void launchStudentMode() {
    QCM monQuiz; // Stock de toutes les données lues depuis le fichier
    char bufferSaisie[MAX_TEXT]; // Zone mémoire temporaire pour sécuriser les saisies

    // --- AFFICHAGE DU MENU ETUDIANT ---
    printf(COLOR_GREEN "\n==========================================\n" COLOR_RESET);
    printf(COLOR_GREEN "              MODE ETUDIANT\n" COLOR_RESET);
    printf(COLOR_GREEN "==========================================\n" COLOR_RESET);
    
    printf("Entrez le nom du fichier QCM a ouvrir (ex: quizz.bin) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin); // Lecture du nom du fichier
    
    // fgets ajoute un retour a la ligne ('\n') a la fin. 
    // strcspn sert a trouver ce '\n' et a le remplacer par 0 pour avoir un nom de fichier propre.
    bufferSaisie[strcspn(bufferSaisie, "\n")] = 0; 

    // --- OUVERTURE ET LECTURE DU FICHIER ---
    // "rb" Read Binary : on lit le fichier en mode binaire
    FILE *f = fopen(bufferSaisie, "rb");
    if (f == NULL) { // Si le fichier n'existe pas
        printf(COLOR_RED "\nImpossible de trouver le fichier '%s'\n" COLOR_RESET, bufferSaisie);
        return; // On arrete tout et on retourne au menu principal
    }

    // On met tout le contenu du fichier dans la variable monQuiz
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f); // Fermer le fichier après l'avoir lu

    float scoreFinal = 0; // Le compteur de points de l'eleve

    // --- BOUCLE PRINCIPALE : DEFILEMENT DES QUESTIONS ---
    for (int i = 0; i < monQuiz.num_questions; i++) {
        
        // Ce tableau sert de "brouillon" pour retenir les cases que l'élève a cochées (1 = coche, 0 = vide)
        int choixEleveTableau[MAX_OPTIONS] = {0}; 
        int aReponduQuelqueChose = 0; // Un "drapeau" pour savoir si l'élève a passé la question

        printf(TEXT_BOLD "\n------------------------------------------\n" COLOR_RESET);
        printf(TEXT_BOLD "Question %d : %s\n" COLOR_RESET, i + 1, monQuiz.questions[i].statement);

        // Si le prof à autorisé les réponses multiples lors de la création
        if (monQuiz.rules.multiple_answers == 1) {
            printf(COLOR_PINK "(Plusieurs reponses possibles)\n" COLOR_RESET);
        }
        
        // Affichage des propositions (1 à MAX_OPTIONS)
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.questions[i].options[j]);
        }

        /* ===== GESTION DES QUESTIONS A CHOIX MULTIPLES ===== */
        if (monQuiz.rules.multiple_answers == 1) {
            int nbChoix = -1;
            
            // Boucle do...while pour redemander tant que la saisie est invalide
            do {
                if (monQuiz.rules.sequential_mode == 1) {
                    printf("\nCombien de reponses ? (1 a %d) : ", MAX_OPTIONS);
                } else {
                    printf("\nCombien de reponses voulez - vous donner ? (1 a %d, ou 0 pour passer) : ", MAX_OPTIONS);
                }

                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);

                // Si c'est pas la touche Entree, pas le chiffre '0' et que atoi n'arrive pas a lire un chiffre (renvoie 0) -> c'est une lettre
                if (bufferSaisie[0] != '\n' && bufferSaisie[0] != '0' && atoi(bufferSaisie) == 0) {
                    printf(COLOR_RED "Erreur : Vous avez tape des lettres. Veuillez entrer un chiffre.\n" COLOR_RESET);
                    nbChoix = -1;
                } else {
                    // Si l'eleve tape juste "Entree" ou "0"
                    if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.rules.sequential_mode == 0) {
                        nbChoix = 0; // Il a le droit de passer
                    } else if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.rules.sequential_mode == 1) {
                        printf(COLOR_RED "Mode sequentiel ! Vous devez repondre.\n" COLOR_RESET);
                        nbChoix = -1; // Il doit recommencer
                    } else {
                        // On verifie qu'elle ne depasse pas le nombre d'options
                        nbChoix = atoi(bufferSaisie);
                        if (nbChoix < 1 || nbChoix > MAX_OPTIONS) {
                            printf(COLOR_RED "Erreur : Choisissez un chiffre entre 1 et %d.\n" COLOR_RESET, MAX_OPTIONS);
                        }
                    }
                }

                // L'eleve a volontairement saute la question
                if (nbChoix == 0 && monQuiz.rules.sequential_mode == 0) {
                    printf(COLOR_RED "Question passee.\n" COLOR_RESET);
                    break;
                }
            } while (nbChoix < 1 || nbChoix > MAX_OPTIONS);

            // Pour chaque reponse qu'il veut donner, on lui demande son choix
            for (int k = 0; k < nbChoix; k++) {
                int rep = -1;
                do {
                    printf("  Donnez votre choix n%d : ", k + 1);
                    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
                    
                    // Sécurité pour les lettres
                    if (bufferSaisie[0] != '\n' && bufferSaisie[0] != '0' && atoi(bufferSaisie) == 0) {
                        printf(COLOR_RED "Erreur : Vous avez tape des lettres. Veuillez entrer un chiffre.\n" COLOR_RESET);
                        rep = -1;
                    } else {
                        rep = atoi(bufferSaisie);
                        if (rep < 1 || rep > MAX_OPTIONS) {
                            printf(COLOR_RED "Erreur : Choisissez un chiffre valide entre 1 et %d.\n" COLOR_RESET, MAX_OPTIONS);
                        }
                    }
                } while (rep < 1 || rep > MAX_OPTIONS);

                // On "coche" la case correspondante dans le brouillon de l'eleve
                if (rep >= 1 && rep <= MAX_OPTIONS) {
                    choixEleveTableau[rep - 1] = 1;
                    aReponduQuelqueChose = 1;
                }
            }
        }
        
        /* ===== GESTION DES QUESTIONS A CHOIX UNIQUE ===== */
        else {
            int choixEleve = -1;
            do {
                if (monQuiz.rules.sequential_mode == 1) {
                    printf("\nVotre reponse (1 a %d) : ", MAX_OPTIONS);
                } else {
                    printf("\nVotre reponse (1 a %d, ou 0 pour passer) : ", MAX_OPTIONS);
                }

                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);

                if (bufferSaisie[0] != '\n' && bufferSaisie[0] != '0' && atoi(bufferSaisie) == 0) {
                    printf(COLOR_RED "Erreur : Vous avez tape des lettres. Veuillez entrer un chiffre.\n" COLOR_RESET);
                    choixEleve = -1;
                } else {
                    if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.rules.sequential_mode == 0) {
                        choixEleve = 0;
                    } else if ((bufferSaisie[0] == '\n' || atoi(bufferSaisie) == 0) && monQuiz.rules.sequential_mode == 1) {
                        printf(COLOR_RED "Mode sequentiel ! Vous devez obligatoirement repondre.\n" COLOR_RESET);
                        choixEleve = -1;
                    } else {
                        choixEleve = atoi(bufferSaisie);
                        if (choixEleve < 1 || choixEleve > MAX_OPTIONS) {
                            printf(COLOR_RED "Erreur : Choisissez un chiffre valide entre 1 et %d.\n" COLOR_RESET, MAX_OPTIONS);
                        }
                    }
                }

                if (choixEleve == 0 && monQuiz.rules.sequential_mode == 0) {
                    printf(COLOR_RED "Question passee.\n" COLOR_RESET);
                    break;
                }
            } while (choixEleve < 1 || choixEleve > MAX_OPTIONS);

            if (choixEleve >= 1 && choixEleve <= MAX_OPTIONS) {
                choixEleveTableau[choixEleve - 1] = 1;
                aReponduQuelqueChose = 1;
            }
        }

        // --- VERIFICATION ET SCORE ---
        int correct = 1; // On part du principe qu'il a bon
        for (int j = 0; j < MAX_OPTIONS; j++) {
            // on compare chaque case de son brouillon avec les vraies reponses, s'il y a une difference, c'est faux
            if (choixEleveTableau[j] != monQuiz.questions[i].correct_answers[j]) {
                correct = 0;
                break; // Inutile de verifier le reste, on arrete la boucle
            }
        }

        // Attribution ou retrait des points
        if (aReponduQuelqueChose == 0) {
            printf(COLOR_RED "Aucune reponse donnee. Aucun point n'est accorde.\n" COLOR_RESET);
            if (monQuiz.rules.negative_points == 1) { // Si les points negatifs sont actifs
                scoreFinal -= 0.5;
                printf(COLOR_RED "(Point retire : -0.5)\n" COLOR_RESET);
            }
        } else if (correct == 1) {
            printf(COLOR_GREEN "Bravo ! C'est juste.\n" COLOR_RESET);
            scoreFinal += 1;
        } else {
            printf(COLOR_RED "Dommage, c'est faux.\n" COLOR_RESET);
            if (monQuiz.rules.negative_points == 1) {
                scoreFinal -= 0.5;
                printf(COLOR_RED "(Point retire : -0.5)\n" COLOR_RESET);
            }
        }
    }

    // --- RECAPITULATIF ---
    printf(COLOR_GREEN "\n==========================================\n" COLOR_RESET);
    printf(COLOR_GREEN "      RECAPITULATIF DES BONNES REPONSES\n" COLOR_RESET);
    printf(COLOR_GREEN "==========================================\n" COLOR_RESET);

    // On re-parcourt toutes les questions pour afficher la correction
    for (int i = 0; i < monQuiz.num_questions; i++) {
        printf(TEXT_BOLD "Q%d : %s\n" COLOR_RESET, i + 1, monQuiz.questions[i].statement);
        printf("   => La bonne reponse etait : ");
        
        for (int j = 0; j < MAX_OPTIONS; j++) {
            if (monQuiz.questions[i].correct_answers[j] == 1) { // On cherche les propositions vraies
                printf(COLOR_GREEN "[%s] " COLOR_RESET, monQuiz.questions[i].options[j]);
            }
        }
        printf("\n");
    }

    // --- CALCUL ET AFFICHAGE DE LA NOTE FINALE ---
    float noteSur20 = 0;
    if (monQuiz.num_questions > 0) {
        // Ramener le score sur 20
        noteSur20 = (scoreFinal / monQuiz.num_questions) * 20;
    }
    
    // Un etudiant ne peut pas avoir une note inferieure a 0
    if (noteSur20 < 0) noteSur20 = 0;

    printf(COLOR_GREEN "\n------------------------------------------\n" COLOR_RESET);
    printf(COLOR_GREEN "              RESULTAT FINAL\n" COLOR_RESET);
    printf(COLOR_GREEN "------------------------------------------\n" COLOR_RESET);
    
    printf("Votre note : %.2f / 20\n", noteSur20);
    
    printf(COLOR_GREEN "==========================================\n\n" COLOR_RESET);

} 
