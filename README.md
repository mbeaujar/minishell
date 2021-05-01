# MINISHELL

## LIEN :

- table ascii ctrl : http://www.physics.udel.edu/~watson/scen103/ascii.html

- termcaps list : http://manpages.ubuntu.com/manpages/bionic/fr/man5/termcap.5.html

- quotes : https://www.gnu.org/software/bash/manual/bash.html#Double-Quotes

- redirection : https://putaindecode.io/articles/maitriser-les-redirections-shell/

- tuto écrire son propre shell : https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

- bash : https://learnxinyminutes.com/docs/bash/

- algo : https://fr.wikipedia.org/wiki/Algorithme_Shunting-yard

- algo : https://fr.wikipedia.org/wiki/Arbre_de_la_syntaxe_abstraite

- env : https://fr.wikipedia.org/wiki/Env

- parsing : https://mywiki.wooledge.org/BashParser#:~:text=Bash%20always%20reads%20your%20script,with%20a%20literal%20newline%20inbetween

https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

termcap : https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_4.html

  
## DOC :

- fork : crée un process child qui est une copie du process parent 

- wait : suspend le processus appelant jusqu'à ce que l'un de ses childs se termine

- waitpid : susprend le processus appelant jusqu'à ce que le child spécifié dans le pid ait changé d'état
	
- wait3 : La même chose que waitpid mais retourne des informations sur l'utilisation des ressources par le child depuis la struct rusage

- wait4 : La même chose que wait3 mais contrairement à wait3 qui prend tout les childs, wait4 peut en spécifier qu'un seul

- signal : gestion de signaux, en fonction du gestionnaire il peut ignoré comme faire des actions en fonction des signaux

- kill : envoi un signal à un processus, le signal dépend du pid

- getcwd : copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par buf, qui est de longueur size

- chdir : remplace le répertoire de travail courant du processus appelant par celui indiqué dans le chemin path -- utile pour la commande "cd"

- stat : récupère l'état du fichier pointé par path et remplit le tampon buf, remplit une structure d'informations sur un fichier -- utile pour la commande "ls"

- lstat : est identique à stat(), sauf que si path est un lien symbolique, il donne l'état du lien lui-même plutôt que celui du fichier visé

- fstat : est identique à stat(), sauf que le fichier ouvert est pointé par le descripteur fd

- execve : execute le fichier en arguments -- utile pour la commande "./"

- dup : return une copie du descripteur de fichier en arguments

- dup2 : pareil que dup mais avec des sécurités et un new fd spécifique

- pipe : tube avec 2 descripteurs de fichier, une extrémité du tube écrit et met dans un tampon en attendant que l'autre extrémité la lise

- opendir : open classique mais pour un répertoire

- readdir : consulter / lire un répertoire -- utile pour "ls" ? 

- closedir : ferme le répertoire qui a été ouvert avec opendir

- strerror : Obtenir un message en fonction du code erreur -- utile pour la gestion d'erreur

- errno : code de la dernière erreur

- isatty : booléen, renvoi 1 si desc est un descripteur de fichier ouvert connecté à un terminal, sinon 0

- ttyname : si le fd est connecté à un terminal il retourne le chemin (absolu ?) dans un char* 

- ttyslot : renvoie la position de l'entrée du terminal en cours dans un fichier

- ioctl : Contrôler les périphériques (pas bien compris)

- getenv : prend une variable d'env et retourne la value de la variable dans un char *

##### termcap library

- tcgetattr : remplit une structure "termios" d'informations sur un terminal depuis un fd

- tcsetattr : comme tcgetattr mais il accepte des options en paramètres en + 

- tgetent : 

- tgetflag : 

- tgetnum : 

- tgetstr : 

- tgoto : déplacer le curseur a des coordonnées 

- tputs : 
