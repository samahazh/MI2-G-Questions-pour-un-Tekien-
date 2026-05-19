# Questions-pour-un-Tekien 
📚 Projet QCM – Gestionnaire de Quiz en C 

👥 Équipe 

Projet réalisé dans le cadre du module Informatique – PréING1 2025-2026 à CY Tech. 

Membres du groupe : 

Brahimi Sarah  

Azhani Samah 

Rasamuraly Atcchaya 

  

Ce projet consiste à développer une application de gestion de QCM en langage C destinée aux enseignants et aux étudiants. 

  

L’objectif principal est de proposer une plateforme simple permettant : 

-De créer et enregistrer des questionnaires à choix multiples ; 

-Gérer différentes configurations de QCM ; 

-De faire passer des évaluations aux étudiants ; 

-De corriger automatiquement les réponses ; 

-De calculer une note finale sur 20. 

L’application fonctionne dans le terminal à travers différents menus interactifs. 

 Le projet met également en pratique plusieurs notions importantes de programmation en C comme la gestion de fichiers, les structures de données, la modularité du code et les interactions utilisateur. 

🎯 Fonctionnalités principales 

👨‍🏫 Mode Enseignant 

Le mode enseignant est protégé par un mot de passe. 

Il permet de : 

créer un nouveau QCM ; 
ajouter des questions et des réponses ; 
définir les bonnes réponses ; 
sauvegarder les QCM dans des fichiers ; 
configurer les paramètres du QCM 
Paramètres disponibles 
✅ Réponses multiples possibles 
❌ Points négatifs en cas de mauvaise réponse 
⏭️ Mode séquentiel (obligation de répondre avant de continuer) 
 

👨‍🎓 Mode Étudiant 

Le mode étudiant permet de : 

Consulter la liste des QCM disponibles ; 
Choisir un questionnaire ; 
Répondre aux questions ; 
Obtenir une correction automatique ; 
Recevoir une note finale sur 20. 
Selon les paramètres du QCM, l’étudiant peut : 

Sélectionner une ou plusieurs réponses ; 
Passer une question ; 
Être obligé de répondre avant de continuer. 
 
Fichier utilisée : 

 

 

💾 Sauvegarde des QCM 

Les QCM sont enregistrés dans des fichiers texte afin de pouvoir être réutilisés plus tard. 

Chaque fichier porte le nom du QCM. 

Exemple : 

Science.bin 

Cultures.bin 

Test.bin  

 

🛡️ Gestion des erreurs 

Le programme a été conçu pour être stable et éviter les crashs. 

Les principales sécurités mises en place : 

vérification des saisies utilisateur ; 
gestion des fichiers inexistants ; 
contrôle des limites mémoire ; 
prévention des boucles infinies ; 
validation des réponses. 
 

🧠 Concepts utilisés 

Ce projet nous a permis de travailler plusieurs notions importantes du langage C : 

structures (struct) ; 
tableaux ; 
pointeurs ; 
fichiers texte ; 
modularité (.c / .h) ; 
menus interactifs ; 
gestion mémoire ; 
conditions et boucles. 
🔗 Dépôt Git 

 

📌 Exemple d’utilisation: mettre des photos  

 

 

