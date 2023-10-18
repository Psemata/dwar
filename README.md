Dwar
====

Dwar est un projet réalisé en Qt durant le cours de P2.

Installation
------------

Lancer l'installeur DwarInstaller.exe et suivre les étapes

Comment jouer
-------------

Voici comment jouer à Dwar et quelles sont les règles.
En arrivant sur le menu principal, vous avez 3 choix :
1. Jouer
2. Lire les règles
3. Quitter
En cliquant sur jouer, un dialogue apparaît et vous pouvez choisir des configurations :
En cochant la case : "Sélection de l'armée pour l'IA", on peut alors choisir un mode de difficulté :
1. Facile => L'IA possède une armée de taille faible
2. Intermédiaire => L'IA possède une armée de taille moyenne
3. Difficile => L'IA possède une armée de taille grande
En décochant la case : "Sélection de l'armée pour l'IA" on ne peut plus choisir un mode de difficulté mais on peut choisir l'armée ennemie !
Une fois la configuration faite, vous pourrez choisir votre armée dans le menu de sélection.
Dès que votre armada est au complet, il suffit de valider pour arriver sur le plateau de jeu.
Ici plusieurs opérations se déroulent dans un certain ordre :
1. Déplacez vos unités sur la carte, puis passez votre tour
2. Déplacez les unités ennemies
3. Commencer le combat
4. Le contrôle des unités se fait en deux temps
	1. Il faut d'abord déplacer toutes ses unités - puis passer en mode attaque
	2. Puis, une fois en mode attaque, on peut attaquer les unités ennemies qui sont dans la portée d'attaque
5. Une fois toutes les unités d'une armée détruites, c'est la fin de la partie

Wiki
----

Le wiki est disponible sur [github]([https://gitlab-etu.ing.he-arc.ch/isc/2021/p2qt/Dwar/-/wikis/home](https://github.com/Psemata/dwar/wiki)).

Authors
-------

* Bruno Costa, [@Psemata](https://github.com/Psemata).
* Diogo Lopes Da Silva, [@Ultrasic](https://github.com/Ultrasic).
* Valentino Izzo, [@Tino3210](https://github.com/Tino3210).
