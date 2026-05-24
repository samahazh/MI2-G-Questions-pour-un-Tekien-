# Questions pour un Tekien - Projet QCM

## Compilation et Exécution :

Le projet utilise un fichier `Makefile` pour faciliter la compilation : 

**1. Compiler le programme :**
Ouvrez le terminal dans le dossier du projet et tapez :
`make re`

**2. Lancer l'application :**
Une fois la compilation terminée, exécutez le programme avec :
`./programme_qcm`

**3. Nettoyer le dossier :**
Pour supprimer l'exécutable généré :
`make clean`

---

## Présentation du projet :

<img width="316" height="137" alt="Capture d’écran 2026-05-22 à 03 54 02" src="https://github.com/user-attachments/assets/8c0ce183-aff6-41e9-9b76-f50c9cfe495c" />

Ce projet consiste à développer une application de gestion de QCM en langage C, fonctionnant dans le terminal à travers différents menus. Elle est faite pour les enseignants (pour la création des QCM) et les étudiants (pour passer l'évaluation).

**L’objectif principal est de proposer une application permettant de :**
* Créer et enregistrer des QCM
* Gérer les options de chaque QCM.
* Faire passer des évaluations aux étudiants.
* Corriger automatiquement les réponses et calculer une note sur 20.

Ce projet met en pratique des notions de la programmation en C : la gestion de fichiers, les structures, les saisies clavier et les tableaux.

---

## Fonctionnalités principales :

### Mode Enseignant

<img width="438" height="218" alt="Capture d’écran 2026-05-22 à 10 47 10" src="https://github.com/user-attachments/assets/aa88e69d-3c1f-48c6-ac0d-cfe83a0c747b" />

Le mode enseignant est l'espace de création des QCM, protégé par un mot de passe (`prof123`).

**Il permet de :**
* Créer un nouveau QCM.
* Ajouter des questions et des propositions de réponses.
* Définir les bonnes réponses.
* Sauvegarder les QCM dans des fichiers binaires.
* Configurer les paramètres spécifiques de chaque QCM.

**Paramètres de QCM disponibles :**
* Réponses multiples.
* Points négatifs en cas de mauvaise réponse.
* Mode séquentiel (obligation de répondre pour passer à la suite).

### Mode Étudiant

<img width="528" height="254" alt="Capture d’écran 2026-05-22 à 03 57 56" src="https://github.com/user-attachments/assets/be5fd5ed-8e23-4901-8f1a-c84e6ffb3984" />

Le mode étudiant est l'espace d'évaluation.

**Il permet de :**
* Ouvrir un questionnaire existant.
* Répondre aux questions.
* Obtenir une correction automatique.
* Recevoir une note finale sur 20.

**Selon les paramètres définis par l'enseignant, l’étudiant peut :**
* Sélectionner une ou plusieurs réponses.
* Passer une question (si le mode séquentiel est désactivé).

---

## Informations sur le projet :

* Architecture : Le code est divisé en modules pour une meilleure lisibilité.
* Sauvegarde : Les QCM sont enregistrés dans des fichiers binaires (.bin).
* Sécurité : Le programme intègre des sécurités pour empêcher les erreurs lors de l'utilisation (saisie utilisateur, ouverture des fichiers).

---

## Références couleurs :

| Couleur  |  Utilisation principale              |
|----------|--------------------------------------|
| Bleu 🔵  | Titres et menus principaux           |
| Rouge 🔴 | Mode Enseignant et Messages d'erreur |
| Vert 🟢  | Mode Étudiant et Bonne réponse       |
| Rose 🟣  | Quitter et indications spécifiques   |
| Gras ⚫️  | Énoncés des questions                |
| Défaut ⚪️| Réinitialisation (fin de couleur)    |

---

Projet réalisé par Azhani Samah, Brahimi Sarah, Rasamuraly Atcchaya (Équipe MI2 - G) dans le cadre de la matière "Informatique - Préing1 - 2025/2026"
