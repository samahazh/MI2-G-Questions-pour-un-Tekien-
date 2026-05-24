#ifndef QCM_H
#define QCM_H

#define MAX_QUESTIONS 50
#define MAX_CHOIX 4    
#define MAX_TEXTE 256

// Couleurs :
#define COULEUR_DEFAUT "\033[0m"
#define TEXTE_GRAS     "\033[1m"
#define COULEUR_BLEU   "\033[1;34m"
#define COULEUR_ROUGE  "\033[1;31m"
#define COULEUR_VERT   "\033[1;32m"
#define COULEUR_ROSE   "\033[1;35m"

// Structure pour les paramètres d'un QCM
typedef struct {
    int points_negatifs;   
    int reponses_multiples; 
    int mode_sequentiel;    
} Parametres;     

// Structure pour une question
typedef struct {
    char enonce[MAX_TEXTE];                       
    char propositions[MAX_CHOIX][MAX_TEXTE];    
    int bonnes_reponses[MAX_CHOIX];   
} Question;

// Structure pour tout le QCM
typedef struct {
    char nom[MAX_TEXTE];            
    Parametres regles;               
    Question questions[MAX_QUESTIONS]; 
    int nb_questions;                
} QCM;

#endif
