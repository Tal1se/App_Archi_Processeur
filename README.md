# Projet de Microprocesseur - Chronomètre

Ce fichier README contient des informations détaillées sur un projet de chronomètre développé pour un microprocesseur. Ce chronomètre dispose de boutons pour démarrer, arrêter, sauvegarder et réinitialiser le compteur de temps.

## Fonctionnalités

Le chronomètre offre les fonctionnalités suivantes :

- **Démarrer le chronomètre** : Appuyez sur le bouton **Start** pour commencer à compter le temps écoulé. Si le chronomètre est en pause, le bouton **Start** devient **Restart** pour recommencer le comptage.
- **Arrêter le chronomètre** : En appuyant sur le bouton **Stop**, le chronomètre s'arrête, enregistrant le temps écoulé. Si le chronomètre est déjà en pause, le bouton **Stop** devient **Reset** pour remettre le compteur à zéro.
- **Sauvegarder la valeur du chronomètre** : Le bouton **Save** permet de sauvegarder la valeur actuelle du chronomètre en mémoire (`val mem`) et d'incrémenter un compteur de sauvegarde (`nb save`).
- **Réinitialiser le compteur de sauvegarde** : Le bouton **Reset** permet de remettre à zéro le compteur de sauvegarde (`nb save`).

## Affichage

- **Valeur du chronomètre** : La valeur actuelle du chronomètre est affichée en temps réel.
- **Valeurs sauvegardées** : La dernière valeur sauvegardée et le nombre de sauvegardes sont affichés.
- **Redémarrage** : Lors d'un redémarrage, le chronomètre reprend à zéro sans conserver la valeur précédente mais garde en mémoire le nombre de save et sa dernière valeur.

## Configuration logicielle

Pour développer et programmer ce projet de chronomètre, vous aurez besoin des outils suivants :

- **Langage de programmation** : C
- **Environnement de développement intégré (IDE)** : Keil μVision5
- **Lancement du projet** : Dans le dossier "Projet", ouvrez le fichier "projet" avec l'extension uVision5 pour démarrer le développement.

Une fois le projet ouvert, des instructions supplémentaires seront affichées par le microprocesseur pour guider le développement et le débogage.

## Auteur

Syrine HAQUIN 

ENSSAT / 2023 - 2024

