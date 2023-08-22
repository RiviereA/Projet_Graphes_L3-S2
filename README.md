# Projet de Graphes (L3 semestre 2)

Le but du projet était d’implanter l’algorithme de Bron-Kerbosch pour afficher toutes les cliques maximum d’un graphe non orienté, puis de l’appliquer sur des graphes généré aléatoirement. 

## Génération de graphe aléatoire

Il fut décidé de commencer par programmer la génération de graphe aléatoire afin de pouvoir s’en servir pour tester les méthodes ***FloydWarshall*** et ***BronKerbosch***.

La fonction ***Generegraphe*** prend en paramètre la probabilité (comprise entre 0 et 100 inclus) qu’il y ai ou non une arrête entre deux sommets. 

Cette méthode remplie deux matrices d’adjacence :
- **adj** (de taille **n** * **n**) pour la méthode ***Bronkerbosh*** avec des 1 en cas d’arêtes et 0 sinon
- **W** (de taille **n** * **n**) identique à **adj** à ceci près que la valeur **n** remplace les 0 étant donné que l’algorithme de Floyd-Warshall fonctionne par comparaisons de valeurs infinies. La distance maximale entre 2 points étant de **n**-1, la valeur **n** a été choisie pour représenter l’infini.

## Puissance éxacte d’un graphe

La méthode ***FloydWarshall*** permet de remplir la matrice **W** avec les plus cours chemins entre chaque pair de sommets.

Une fois la matrice de plus courts chemins réalisée, il ne reste plus qu’à afficher les distances égales à la puissance exacte souhaitée via l’appelle de notre fonction ***PuissanceExacte*** où le paramètre **d** est un entier indiquant la valeur de la puissance exacte souhaité, cette fonction remplie la matrice de puissance exacte **Pexacte** de la manière suivante :
* 1 si la plus courte distance est égal au paramètre **d**
* 0 dans le cas contraire

## Algo de Bron-Kerbosh

La méthode ***BronKerbosch*** réalisée permet d’afficher la liste de toutes les cliques maximales, en outre elle remplie une liste stockant les cliques maximales rencontrées afin de déterminer la ou les cliques maximum ainsi que leur taille.
Les variables passées en paramètres de cette méthode sont des listes de sommets utilisé lors de l’exécution récursive de la manière suivante :
    • **R** contient les sommets faisant déjà partie de la clique.
    • **P** contient tous les sommets voisins du sommet en cours de traitement.
    • **X** contient les sommets qui ont déjà été utilisé dans une précédente clique.

Cette méthode se sert également des fonctions :
    • ***Intersect*** pour réaliser les opérations d’intersection entre les différentes listes.
    • ***Suppr*** pour supprimer l’un des sommets de la liste passé en paramètre.
    • ***GetV*** pour récupérer l’ensemble des sommets voisins de celui passé en paramètre.