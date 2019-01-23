*ETAPE DE CREATION DU JEU ET DIFFICULTÉS RENCONTRÉS:

ETAPE 1:

-Termios:J'ai créer une configuration *nouveau* que j'ai mis en mode non canonique (!ICANON)
et j'ai configurer le terminal avec cette nouvelle configuraion.

-Affichage:J'ai creer deux tableaux un pour la carte principale et l'autre pour la carte bonus ,j'ai lu la      longueur e la largeur sur la carte a lire et read dans ce buffer avec une taille=longueur*largeur que j'affiche sur le terminal dans une boucle while.
j'affiche ensuite a la positionJ1 et positionJ2 les joueur A et H.

-Affichage de la carte bonus dans la carte principale: Avec une boucle for allant de 0 a taille je lis tout ce qui est bonus ou explosion et je l'affiche dans le buffer de la carte principale.
lorsqu'un joueur avance sur un bonus cela l'efface dans la carte bonus ce qui a pour effet de le supprimer dans la carte principale.

ETAPE 2:

Ajout de poll: Configuration de poll avec surveillance de l'entrée standard pour reconnaitre les touches de deplacement et de bombes.

Gestion des collisions:le joueur ne peut avancer que sur les espaces,les bonus et les explosions ce qui evite de sortir de la map.

Gestion des bonus et informations sur les joueurs: avec sprintf j'ai copiés les informations iniales des joueurs et je les affiches dans la boucle while,a chaque fois que la partie est relancée je copie dedans les information qui sont dans les struct joueur1 et joueur2 initialiss dans jeu().

-Ajout de la vitesse,la vitesse du joueur augmente de 1 lorsqu'il prend des *.

*probleme n°1:le joueur sort de la map prés du mur et traverse les bonus ,j'ai du gerer ces cas avec une boucle qui va lire la vitesse du joueur dans J1.vitesse et en fonction du nombre de cases a avancer je regarde si i y'a un bonus ou non et si la case suivante est un 0 ou un joueur.

ETAPE 3:

-Ajout des bombes:lorsqu'un joueur appuie sur la touche e ou ! une bombe X est posée sur la carte.

*probleme n°2: sans fork() ce fut trés difficile d'attendre de maniere non bloquante avant de faire explosé la bombe,j'ai d'abord utilisé des alarmes avec les signaux ,puis j'ai compris qu'on ne peux utilisé qu'une seule alarme par processus ce va m'amener a time(); 

*probleme n°3:lors de la configuration de poll j'avais mis le timeout a -1 or le read du buffer qui lit les touches est bloquant...vu que l'attente est infinie mon time() doit attendre que j'appuie sur une touche pour etre pris en compte ,je suis donc rester bloqué quelques jours sans comprendre d'ou venait le probleme,aprés quelques recherche j'ai mis le timeout a 1 ce qui permet de prendre en compte time() toutes les 1 seconde.

-Ajout de la puissance +:la puissance va augmenter chaque cotés de l'explosion de # ,je verrifie d'abord si ce n'ets pas un mur ou un bonus puis j'affiche l'explosion.

-Ajout du nombre de bombes posées au meme moment:c'est l'etape la plus difficile avec l'impossibilité d'utilisé des processus,j'ai donc reutilisé time() pour chaque cas :1,2, ou 3 bombes afin d'attendre qu'une bombe explose sachant qu'il y'en a une avant ou non.

-Ajout des nombre de bombes @: ajoute +1 bombe que le joueur peut posé sans attendre l'explosion.

Quand un joueur est touché une alarme appel un header qui diminue ses pv ,il y'a  alarmes une pour le J1 une pour le J2 et une derniere dans le cas ou ils sont touchés au meme moment.

lorsqu'un jouer se retrouve avec 0 pv le jeu remet la configuration d'orgine de termios et quitte.

-Ajout d'un menue qui permet de choisir entre 3 modes de jeu,je n'ai pas reussi a faire le chargement du niveau suivant lors de la fin d'une partie.

ETAPE 4:

-J'ai essayer de faire la partie reseau mais mon manque de comprehension du sujet ne m'a pas permis de le faire.






