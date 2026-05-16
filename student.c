#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "student.h"

/* ================= COULEURS ANSI ================= */

#define RESET   "\033[0m"

#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define BLEU    "\033[34m"
#define ROSE    "\033[35m"
#define CYAN    "\033[36m"

#define GRAS    "\033[1m"

/* ================================================= */

void launchStudentMode() {
    QCM monQuiz;
    char bufferSaisie[MAX_TEXT]; 

    printf(BLEU GRAS "\n==========================================\n" RESET);
    printf(BLEU GRAS "              MODE ETUDIANT\n" RESET);
    printf(BLEU GRAS "==========================================\n" RESET);
    
    printf("Entrez le nom du fichier QCM a ouvrir (ex: quizz.bin) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    bufferSaisie[strcspn(bufferSaisie, "\n")] = 0; 

    FILE *f = fopen(bufferSaisie, "rb");
    if (f == NULL) {
        printf(ROUGE "\n[ERREUR] Impossible de trouver le fichier '%s'\n" RESET, bufferSaisie);
        printf("Appuyez sur Entree pour revenir au menu");
        fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
        return;
    }

    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f);

    float scoreFinal = 0;

    for (int i = 0; i < monQuiz.num_questions; i++) {

        int choixEleveTableau[MAX_OPTIONS] = {0}; 
        int aReponduQuelqueChose = 0;

        printf(BLEU "\n------------------------------------------\n" RESET);
        printf(BLEU "Question %d : %s\n" RESET,
               i + 1,
               monQuiz.questions[i].statement);

        if (monQuiz.rules.multiple_answers == 1) {
            printf(ROSE "(ATTENTION : Plusieurs reponses possibles)\n" RESET);
        }

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("  %d) %s\n",
                   j + 1,
                   monQuiz.questions[i].options[j]);
        }

        /* ===== QUESTION A CHOIX MULTIPLES ===== */

        if (monQuiz.rules.multiple_answers == 1) {

            int nbChoix = -1;

            do {

                if (monQuiz.rules.sequential_mode == 1) {
                    printf("\nCombien de reponses ? (1 a %d) : ",
                           MAX_OPTIONS);
                } else {
                    printf("\nCombien de reponses ? (1 a %d, ou 0 pour passer) : ",
                           MAX_OPTIONS);
                }

                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);

                if ((bufferSaisie[0] == '\n'
                    || atoi(bufferSaisie) == 0)
                    && monQuiz.rules.sequential_mode == 0) {

                    nbChoix = 0;

                } else {

                    nbChoix = atoi(bufferSaisie);
                }

                if (nbChoix == 0
                    && monQuiz.rules.sequential_mode == 0) {

                    printf(JAUNE "[INFO] Question passee.\n" RESET);
                    break;
                }

            } while (nbChoix < 1 || nbChoix > MAX_OPTIONS);

            for (int k = 0; k < nbChoix; k++) {

                int rep = 0;

                do {

                    printf("  Donnez votre choix n%d : ", k + 1);

                    fgets(bufferSaisie,
                          sizeof(bufferSaisie),
                          stdin);

                    rep = atoi(bufferSaisie);

                } while (rep < 1 || rep > MAX_OPTIONS);

                choixEleveTableau[rep - 1] = 1;
                aReponduQuelqueChose = 1;
            }
        }

        /* ===== QUESTION A CHOIX UNIQUE ===== */

        else {

            int choixEleve = -1;

            do {

                if (monQuiz.rules.sequential_mode == 1) {

                    printf("\nVotre reponse (1 a %d) : ",
                           MAX_OPTIONS);

                } else {

                    printf("\nVotre reponse (1 a %d, ou 0 pour passer) : ",
                           MAX_OPTIONS);
                }

                fgets(bufferSaisie,
                      sizeof(bufferSaisie),
                      stdin);

                if ((bufferSaisie[0] == '\n'
                    || atoi(bufferSaisie) == 0)
                    && monQuiz.rules.sequential_mode == 0) {

                    choixEleve = 0;

                } else {

                    choixEleve = atoi(bufferSaisie);
                }

                if (choixEleve == 0
                    && monQuiz.rules.sequential_mode == 0) {

                    printf(JAUNE "Question passee.\n" RESET);
                    break;

                } else if (choixEleve < 1
                           || choixEleve > MAX_OPTIONS) {

                    printf(ROUGE "Erreur : Choisissez un chiffre valide.\n" RESET);
                }

            } while (choixEleve < 1
                     || choixEleve > MAX_OPTIONS);

            if (choixEleve >= 1
                && choixEleve <= MAX_OPTIONS) {

                choixEleveTableau[choixEleve - 1] = 1;
                aReponduQuelqueChose = 1;
            }
        }

        /* ===== VERIFICATION ===== */

        int correct = 1;

        for (int j = 0; j < MAX_OPTIONS; j++) {

            if (choixEleveTableau[j]
                != monQuiz.questions[i].correct_answers[j]) {

                correct = 0;
                break;
            }
        }

        if (aReponduQuelqueChose == 0) {

            printf(JAUNE "Aucune reponse donnee. C'est considere comme faux.\n" RESET);

        }

        else if (correct == 1) {

            printf(VERT "Bravo ! C'est juste.\n" RESET);
            scoreFinal += 1;

        }

        else {

            printf(ROUGE "Dommage, c'est faux.\n" RESET);

            if (monQuiz.rules.negative_points == 1) {

                scoreFinal -= 0.5;
                printf(ROUGE "(Point retire : -0.5)\n" RESET);
            }
        }
    }

    /* ===== RECAP ===== */

    printf(BLEU GRAS "\n==========================================\n" RESET);
    printf(BLEU GRAS "      RECAPITULATIF DES BONNES REPONSES\n" RESET);
    printf(BLEU GRAS "==========================================\n" RESET);

    for (int i = 0; i < monQuiz.num_questions; i++) {

        printf(BLEU "Q%d : %s\n" RESET,
               i + 1,
               monQuiz.questions[i].statement);

        printf(VERT "   => La bonne reponse etait : " RESET);

        for (int j = 0; j < MAX_OPTIONS; j++) {

            if (monQuiz.questions[i].correct_answers[j] == 1) {

                printf(VERT "[%s] " RESET,
                       monQuiz.questions[i].options[j]);
            }
        }

        printf("\n");
    }

    /* ===== NOTE ===== */

    float noteSur20 = 0;

    if (monQuiz.num_questions > 0) {

        noteSur20 =
        (scoreFinal / monQuiz.num_questions) * 20;
    }

    if (noteSur20 < 0)
        noteSur20 = 0;

    printf(BLEU GRAS "\n------------------------------------------\n" RESET);
    printf(BLEU GRAS "              RESULTAT FINAL\n" RESET);
    printf(BLEU GRAS "------------------------------------------\n" RESET);

    printf(CYAN GRAS "Votre note : %.2f / 20\n" RESET,
           noteSur20);

    printf(BLEU GRAS "==========================================\n\n" RESET);

    printf("Appuyez sur Entree pour revenir au menu");

    fgets(bufferSaisie,
          sizeof(bufferSaisie),
          stdin);
}
<<<<<<< HEAD
}
=======
}
>>>>>>> bb211f7200a805430c57fcd4d6e4babc10eca7c1
