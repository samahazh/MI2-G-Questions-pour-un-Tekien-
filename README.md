# 🧠 Questions-pour-un-Tekien 
**Projet QCM 

## 👥 Équipe & Contexte

Projet réalisé dans le cadre du module **Informatique – PréING1 2025-2026** à **CY Tech**. 

**Membres du groupe :
* Brahimi Sarah
* Azhani Samah
* Rasamuraly Atcchaya

---

## 📝 Présentation du projet

Ce projet consiste à développer une application de gestion de QCM en langage C, fonctionnant dans le terminal à travers différents menus interactifs. Elle est destinée à la fois aux enseignants (pour la création) et aux étudiants (pour l'évaluation).

**L’objectif principal est de proposer une plateforme simple permettant de :
* Créer et enregistrer des questionnaires à choix multiples.
* Gérer différentes configurations et règles de QCM.
* Faire passer des évaluations aux étudiants.
* Corriger automatiquement les réponses.
* Calculer une note finale sur 20.

Ce projet met en pratique des notions fondamentales de la programmation en C : gestion de fichiers, structures de données, modularité du code et interactions utilisateur.

---

## 🎯 Fonctionnalités principales

### 👨‍🏫 Mode Enseignant
Le mode enseignant est l'espace d'administration, protégé par un mot de passe.
Il permet de :
* Créer un nouveau QCM.
* Ajouter des questions et des réponses.
* Définir les bonnes réponses.
* Sauvegarder les QCM dans des fichiers binaires.
* Configurer les paramètres spécifiques de chaque QCM.

**Paramètres de QCM disponibles :**
* ✅ Réponses multiples possibles.
* ❌ Points négatifs en cas de mauvaise réponse.
* ⏭️ Mode séquentiel (obligation de répondre avant de continuer).

### 👨‍🎓 Mode Étudiant
Le mode étudiant est l'espace de test.
Il permet de :
* Consulter la liste des QCM disponibles.
* Choisir un questionnaire.
* Répondre aux questions interactives.
* Obtenir une correction automatique immédiate.
* Recevoir une note finale sur 20.

**Selon les paramètres définis par l'enseignant, l’étudiant peut :**
* Sélectionner une ou plusieurs réponses.
* Passer une question (si le mode séquentiel est désactivé).

---

## 🚀 Installation et Exécution

Le projet utilise un `Makefile` pour faciliter la compilation.

1. **Ouvrir le terminal** dans le dossier du projet.
2. **Compiler le programme** en tapant simplement :
   
   make
---

## 🚀 Installation et Exécution

Le projet utilise un `Makefile` pour faciliter la compilation.

1. **Ouvrir le terminal** dans le dossier du projet.
2. **Compiler le programme** en tapant simplement :
   make

Lancer l'application :
./programme_qcm

Nettoyer les fichiers de compilation:
make clean

📁 Architecture du projet
Le code est modulaire pour une meilleure lisibilité et maintenance :
-main.c : Point d'entrée principal du programme.
-teachers.c / teachers.h : Fonctions relatives au mode Enseignant (création, gestion).
-student.c / student.h : Fonctions relatives au mode Étudiant (passage de test, notation).
-qcm.h / utile.h : Définition des structures de données et fonctions utilitaires.
-Makefile : Fichier de configuration pour la compilation automatisée.

💾 Sauvegarde des QCM
Les QCM sont enregistrés dans des fichiers .bin afin d'être persistants et réutilisés plus tard. Chaque fichier porte le nom du QCM créé.
Exemples : Sciences.bin, Culture_Generale.bin, test.bin.

🛡️ Gestion des erreurs & Sécurité
Le programme a été conçu pour être stable et éviter les crashs. Les principales sécurités mises en place sont :
-Vérification stricte des saisies utilisateur.
-Gestion des fichiers inexistants.
-Contrôle des limites mémoire.
-Validation des réponses et gestion des erreurs de format.

🧠 Concepts techniques appliqués
Ce projet nous a permis de consolider les notions suivantes :
-Structures (struct) : Pour modéliser les questions et les QCM.
-Tableaux & Pointeurs : Pour la manipulation des données en mémoire.
-Fichiers : Lecture et écriture de fichiers binaires/texte.
-Modularité : Séparation du code en fichiers .c et .h.
-Interface : Création de menus interactifs dans le terminal.

🎨 Références couleurs (Affichage terminal)

Les couleurs sont utilisées dans les `printf` pour améliorer la lisibilité en terminal.

| Couleur   | Code ANSI                | Aperçu                         |
|-----------|--------------------------|--------------------------------|
| 🔴 Rouge  | `\033[91m`               | `RED`                          |
| 🔵 Bleu   | `\033[94m`               | `BLUE`                         |
| 🏴 Magenta| `\033[35m`               | `MAGENTA`                      |
| 🟢 Vert   | `\033[92m`               | `GREEN`                        |
| ♻️ Reset  | `\033[0m`                | Réinitialisation des couleurs `RESET` |
| 🌊 Cyan   | `\033[96m`               | `CYAN`                         |
| 🟠 Orange | `\033[38;5;214m`         | `ORANGE`                       |

🔗 Liens & Démonstration
Dépôt Git : https://github.com/samahazh/MI2-G-Questions-pour-un-Tekien-.git
📌 Aperçu de l'application :
"mettre des photo du menu et de chaque fichier"

 
