# Projet_FAIN
WENDLING Quentin
## Fonctionnement : 

* Lancement du programme :</br>
  La compilation du code ce fais avec la commande <pre><code>make</code></pre>
  Une fois le code compilé le programme se lance avec la commande : <pre><code>./plot [width][height] </code></pre> 
--------
* Choix du mode :
  Le programme offre différents mode d'intéraction.</br> 
  Le choix du mode se fais avec les commandes : </br>
  * 'a' mode append 
  * 'v' mode vertex
  * 'e' mode edge
-------
* Mode append :</br>
  Permet les intéractions de base avec le polygone :
  * click gauche : Création d'un nouveau sommets lié avec le dernier sommet créé
  ![ajout sommets](/append_click.png)
  * 'c' : Fermeture/ouverture du polygone
  ![fermeture polygone](/append_c.png)
  * 'f' : Remplissage du polygone  
  ![fill polygone](/append_fill.png)
-----------
* Mode Vertex :</br>
  Permet les intéractions avec les sommets : 
  * 'page suivante' : selection du point suivant
  * 'page précédente' : selection du point précédent
  ![select vertex](/vertex.png)
  * touche haut,bas,droite,gauche : déplacement du point courant
  ![move vertex](/vertex_move.png)
  * 'suppr' : supprésion du point courant
  ![suppr vertex](/vertex_suppr.png)
-----------
* Mode Edge :</br>
  Permet les intéractions avec les aretes :
  * 'page suivante' : selection de l'arete suivante
  * 'page précédente' : selection de l'arete précédente
  ![select edge](/edge.png)
  * click du milieu : coupe l'arete courante en ajoutant un sommet entre les extrémités
  ![cropping edge](/edge_crop.png)
