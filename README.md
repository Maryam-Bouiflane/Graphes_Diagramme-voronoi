Graphe structuré en grille rectangulaire
===================================================================================================

On considère un graphe non orienté dont les sommets sont plongés dans une grille rectangulaire
et sont dotés d’une altitude. 
Le sommet (i, j) positionné sur la ième ligne et la jième colonne de la grille est muni d’une altitude 
h(i, j). 
Les seuls voisins possibles d’un sommet (i, j) sont les sommets à sa gauche (i, j − 1), à sa droite (i, j + 1), 
au dessus (i − 1, j) et en dessous de lui (i + 1, j) (on les désignera sous l’appellation voisins Ouest, Est, 
Nord et Sud), mais cela n’a pas besoin d’être stocké de manière explicite. Cela signifie qu’on ne va pas 
utiliser une représentation par matrice ou par liste d’adjacence pour stocker le graphe. Les sommets du bord de 
la grille ont bien entendu moins de voisins. 
La valuation d’une arête correspond à la distance Euclidienne entre ses deux extrémités 3D (par exemple la valuation 
de l’arête joignant le sommet (i, j) à son voisin Nord (i − 1, j) est sqrt(1 + sqr(h(i, j) − h(i − 1, j))). 
On désigne par L et C le nombre de lignes et de colonnes de la grille.

On se propose de mettre en œuvre un tel module graphe représentant une Grille, en utilisant
uniquement un tableau 1D de taille L×C contenant des informations de hauteur. Le sommet (i, j)
(0 ≤ i ≤ L − 1, 0 ≤ j ≤ C − 1) est représenté par l’indice global i ∗ C + j de la case du tableau
qui contient la valeur de son altitude h(i, j). 
Il est inutile de créer une structure de donnée arête, puisqu’on connaît la position et l’altitude des voisins d’un 
sommet (i, j).
Parmi les procédures d’initialisation d’une Grille, on en prévoit une pour charger un graphe sauvegardé dans un fichier.

```
Format de stockage d’un graphe dans un fichier :
15 24 // Dimensions du graphe L (largeur) et H (hauteur)
12 34 5 .... //Altitudes des L*H sommets listés ligne par ligne
// (du haut vers le bas et de gauche vers la droite)
```

En plus des opérations classiques d’initialisation, d’affectation et de testament de graphe,
on prévoit des fonctions d’accès à l’indice global d’un sommet en fonction de ses indices de ligne ou
de colonne, d’accès à l’altitude d’un sommet (en fonction de son indice global), d’accès à l’indice
global du voisin Nord (resp. Sud, Est et Ouest) d’un sommet (avec pour précondition que le
voisin existe) ainsi que des procédures de modification de l’altitude d’un sommet et une procédure
d’affichage de la grille de hauteur.


Connaître la librairie la plus proche : diagramme de Voronoï
===================================================================================================

L’algorithme de Dijkstra vu en cours permet de trouver les plus courts chemins entre UN
unique nœud n et tous les nœuds accessibles d’un graphe orienté valué, mais il peut également
être mis en oeuvre sur un graphe non orienté. Cela signifie seulement que toutes les arêtes sont
orientées dans les deux sens.

Nous allons à présent modifier l’algorithme de Dijkstra de telle sorte que l’origine des plus courts
chemins ne sera plus un unique site de départ, mais UN ENSEMBLE de N sites 'ni', 0 ≤ i ≤ N − 1
matérialisant la position de librairies dans notre graphe modélisant le terrain d’un site géographique. 
A la fin de l’exécution de l’algorithme de Dijkstra, pour tous les nœuds de la grille, on obtiendra 
ainsi le chemin le plus court depuis la librairie la plus proche.

En plus des hauteurs fournies en entrée, l’utilisateur pourra récupérer dans un fichier les coordonnées, 
en indices de ligne et de colonne, d’un ensemble de sites choisis parmi les sommets
de la grille. La grille modélise le site géographique et ces coordonnées matérialisent les positions
des librairies. Suivant où vous vous trouvez, vous êtes dans le secteur d’une librairie différente. La
cellule de Voronoï du ième site est l’ensemble des sommets de la grille qui sont plus proches de ce
site que des autres sites (en intégrant bien l’information de hauteur dans les calculs de longueur
de chemin, comme évoqué plus haut pour connaître le coût d’un arc). On enregistrera et 
visualisera pour chaque point de la grille l’indice du site dont il est le plus proche à l’issu de
l’algorithme de plus court chemin (ainsi que la distance). Ainsi l'affichage final permettra de
faire apparaître le diagramme de Voronoï de l’ensemble des sites de librairies.

>On stocke les infos relatives au parcours du graphe (couleur, prédécesseur, longueur de chemin) dans des 
>tableaux de taille L × C, indexés dans le même ordre que les L × C sommets du graphe.

***

Pour que le programme fonctionne correctement il faut compiler en faisant "make" et executer en faisant "./main.out"

Vous pouvez executer plusieurs fois afin d'obtenir des diagrammes de voronoi differents car nous tirons 
nos altitudes et librairies aléatoirement.

Notre grille est de taille fixe, 10*15 (10 lignes et 15 colonnes).
Nous avons décidé d'avoir 5 librairies.
