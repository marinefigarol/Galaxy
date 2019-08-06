# Galaxy
Galaxy est un jeu de stratégie tour par tour où vous affrontez l'ordinateur pour conquérir la galaxie !

## Informations

Galaxy est un jeu de stratégie créé lors d'un projet dans le cadre de ma première année de master de bioinformatique. Il s'agit d'un jeu en mode texte qui se déroule entre un joueur humain et l'ordinateur. Le but était de programmer le jeu, l'intelligence artificielle a été fournie (fichiers ai.c et ai.h). L'ensemble des spécifications qui vont suivre ont également été fournies.
Les fichiers ai.c, ai.h, la structure des données galaxy.h ainsi que les annexes sont disponibles à l'adresse https://www.lri.fr/~zaharia/C2017.<br>
Ce jeu est entièrement codé en C et a été réalisé en collaboration avec Christelle Viguier.

## Éxécuter galaxy
Vous avez besoin de <code>gcc</code> et <code>make</code> pour pouvoir jouer.

Une fois les fichiers téléchargés, placez-vous dans le dossier et compilez le code source :<br>

<pre>
<code>cd galaxy
make</code>
</pre>

Vous pouvez désormais lancer le jeu en faisant :

<pre>
<code>./main</code>
</pre>

## 1. Spécification du jeu

Deux joueurs s’affrontent afin de conquérir la galaxie. Le jeu continue jusqu’à ce que l’un d’entre eux perde toutes ses colonies.


### 1.1 La galaxie

La galaxie est une matrice de secteurs galactiques de taille 10 sur 10. Chaque secteur est défini par ses coordonnées (x, y) ou 0 ≤ x, y ≤ 9.<br>
Lors de l’initialisation du jeu, tous les secteurs galactiques ont une probabilité de 0.25 de contenir une planète. Toutes les planètes de la galaxie sont colonisables par les deux joueurs. Chaque planète produit un certain nombre de ressources par tour (entre 100 et 1000, par tranche de 100).<br>
Les secteurs ne contenant pas de planète possèdent un bonus en ressources (un entier aléatoire entre 50 et 250, par tranche de 50).
Chaque joueur commence avec sa planète mère, déterminée aléatoirement parmi les planètes de la galaxie au moment de l’initialisation du jeu. Les planètes mères des deux joueurs ont la particularité de produire chacune 500 ressources par tour.

### 1.2 Les flottes

Chaque joueur commence avec un vaisseau situé dans le secteur de sa planète mère, en orbite de celle-là. Le coût d’un vaisseau est de 1000 ressources. Pour simplifier, les vaisseaux sont construits automatiquement sur chaque planète de chaque joueur, lorsqu’elle a rassemblé suffisamment de ressources. Par exemple, les planètes mères produisent 500 ressources par tour, donc elles construisent un vaisseau tous les deux tours. Une planète qui produit 300 ressources par tour a besoin de quatre tours pour produire un vaisseau. Lors du quatrième tour, elle augmente sa flotte d’un vaisseau et reste avec 300 ×4−1000 = 200 ressources.<br>
Pour simplifier encore, les vaisseaux ne sont pas gérés individuellement. En revanche, ils constituent une flotte ayant une certaine puissance. La puissance d’une flotte est déterminée par le nombre de vaisseaux qui la constituent. Donc, comme chaque joueur possède un vaisseau en orbite de sa planète mère en début de jeu, cette notion sera modélisée par une flotte de puissance 1. Lorsqu’un nouveau vaisseau est construit sur la planète mère, la flotte du joueur dans ce secteur aura une puissance 2, et ainsi de suite.<br>
Chaque secteur galactique peut posséder une flotte, même s’il ne contient pas de planète. Ceci permet l’exploration de la galaxie, telle qu’explicitée dans la section suivante.

### 1.3 L'exploration

Au début du jeu, chaque joueur ne connaît que sa planète mère. Afin d’explorer le reste de la galaxie, les joueurs envoient des flottes dans des secteurs inconnus. Pour initier l’exploration, le joueur doit spécifier le secteur de départ, le secteur d’arrivée et la puissance de la flotte qu’il souhaite déplacer. Cette dernière est supérieure ou égale à 1 (il faut que la flotte à déplacer contienne au moins un vaisseau) et inférieure ou égale à la puissance totale de la flotte du secteur de départ.<br>
S’il le souhaite, le joueur peut déplacer l’ensemble de ses flottes au cours d’un tour. Le voyage est quasi-instantané et n’implique pas la notion de distance. Les flottes n’arrivent à destination qu’au tour prochain (lorsque le joueur choisit de passer au tour suivant).
Lorsqu’un joueur explore un secteur contenant une planète n’appartenant pas à son adversaire, la planète est automatiquement colonisée, mais ne commence à apporter des ressources qu’au tour suivant sa colonisation.<br>
Lorsque le secteur exploré ne contient pas de planète et qu’il n’a pas encore été découvert par l’autre joueur, il contient un bonus aléatoire en ressources (entre 50 et 250, par tranche de 50). C’est alors le joueur qui découvre le secteur pour la première fois qui récupère ce bonus au niveau de sa planète mère. Par exemple, la planète mère du joueur possède un total de 500 ressources accumulées au tour T et pendant le même tour le joueur découvre trois secteurs inconnus qui n’ont pas été explorés auparavant par son adversaire. Supposons que chacun de ces secteurs lui apporte 200 ressources supplémentaires. Alors les ressources cumulées sur la planète mère au tour T valent 1100 ressources, ce qui entraîne l’augmentation de la puissance de la flotte en orbite de la planète mère au tour T + 1.
Quand un joueur découvre un secteur, le bonus affecté au secteur est récupéré mais il est aussi mis à zéro. Ceci rendra impossible la récupération d’un bonus sur un même secteur, par le joueur-même ou par son adversaire.<br>
Le jeu continue tant que chacun des deux adversaires possède au moins une planète. Donc lorsqu’un joueur perd sa planète mère dans une bataille, il va falloir lui réaffecter une planète mère parmi les autres planètes possédées afin qu’il puisse récupérer les bonus d’exploration des secteurs inconnus.

### 1.4 Les batailles

Lorsqu’au tour T les deux joueurs possèdent des flottes (en stationnement ou arrivant) sur un même secteur, une bataille aura lieu dans ce secteur.<br>
Le facteur décisif d’une bataille est la puissance des flottes adverses. Le joueur possédant la flotte la plus puissante gagne toujours, en perdant une puissance égale à la puissance de la flotte du vaincu. Si les deux flottes sont égales en puissance, alors il n’y a pas de vainqueur et les deux joueurs perdent leur flottes dans le secteur en question.<br>
Lorsqu’une bataille a lieu dans un secteur (x, y) :<br>
- Si le joueur J n’a pas encore exploré le secteur (x, y) et qu’il a envoyé une flotte vers ce secteur :<br>
  + Si le joueur J perd la bataille ou si la bataille est à égalité, alors le secteur (x, y) reste non exploré pour J. De plus, si J est le joueur humain, alors le secteur (x, y) sera représenté par un symbole indiquant que l’exploration du secteur n’a pas abouti à cause d’une bataille perdue ou à égalité (référez-vous aux annexes 1 et 4).<br>
  * Si le joueur J gagne la bataille, alors le secteur (x, y) est marqué comme exploré par J, qui :<br>
    + récupère le bonus d’exploration si le secteur ne possède pas de planète et si ce bonus n’a pas déjà été récupéré par l’adversaire, ou<br>
    + colonise la planteè si le secteur possède une planète.<br>
- Si l’adversaire du joueur J a envoyé une flotte vers le secteur (x, y) qui contient une planète appartenant au joueur J :<br>
  * Si la bataille est à égalité, alors le joueur J garde la planète.<br>
  * Si le joueur J perd la bataille, alors il perd aussi la planète. Si en plus il s’agissait de sa planète mère, alors il va falloir réaffecter une planète mère au joueur J. Si ceci n’est pas possible, la planète du secteur (x, y) était son unique colonie, et donc le jeu finit avec l’adversaire de J comme gagnant.
    
## 2 Le déroulement du jeu
### 2.1 Initialisation du jeu

Dans un premier temps, on déterminera les secteurs possédant des planètes. Chaque planète se verra affecter une production de ressources par tour. Il va aussi falloir affecter aux secteurs ne possédant pas de planète un bonus d’exploration.
Dans un second temps, on choisira les planètes mères des deux joueurs en ajustant la production de ressources par tour en conséquence. Une flotte de puissance 1 sera également présente dans ces secteurs.

### 2.2 Passage au tour suivant

Au début de chaque tour, il va falloir mettre à jour la galaxie, puis laisser opérer la stratégie de chaque joueur pour le tour suivant. La mise à jour de la galaxie consiste en deux étapes. D’abord, la production en ressources pour les planètes possédées par les joueurs est actualisée. Ceci entraîne la construction automatique de vaisseaux sur les planètes ayant suffisamment de ressources accumulées. Ensuite, pour chaque secteur de la galaxie où des flottes doivent arriver, il va falloir gérer les différents cas de figure (présence de conflit résultant en bataille, exploration sans bonus, exploration avec bonus et colonisation).


### 2.3 La stratégie de chaque joueur

Une fois que la galaxie a été mise à jour en début de tour, chaque joueur met en œuvre sa stratégie. Les deux joueurs doivent pouvoir connaître leurs colonies, la localisation et la puissance de leurs flottes, et doivent bien sûr pouvoir envoyer des flottes à des destinations choisies. Alors que le joueur humain déploie sa stratégie via une interface utilisateur abordée dans le paragraphe suivant, l’ordinateur possède sa propre stratégie. Un exemple de stratégie pour l’ordinateur vous est fourni dans les fichiers ai.c et ai.h à l’adresse https://www.lri.fr/~zaharia/C2017.

### 2.4 Interface utilisateur

Les annexes 1 à 5 proposent un exemple d’interface utilisateur.


