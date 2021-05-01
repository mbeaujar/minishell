- echo : 


- pwd : affiche le chemin absolu

	- ne refresh pas pwd

- cd : 

	- refresh pwd 

	- oldpwd prend la value de PWD (meme si elle est fausse)
		-	si on set PWD=test et qu'on 'cd ..' OLDPWD va prendre comme valeur 'test' et PWD va prendre le vrai chemin absolu

	- cd .. toto -- bash: cd: too many arguments

	- cd ~ -- cd $HOME

	- cd -- cd $HOME

	- cd - -- cd $OLDPWD // ! bash: cd: OLDPWD not set

- unset : détruit une variable et son contenue // elle n'apparait plus dans env et export

	- prend en argument le nom des variables à unset 

	- fonctionne avec des arguments invalid 

	- unset -- ne fait rien

- export : augmente le scope de la variable // si on export pas une variable elle existe que dans le terminal ou elle est et est non reconnue par les commandes env et export

	- export -- affiche les env trié par ascii
	- export RA -- affiche RA dans les exports
	- RO=salut -- affiche pas RO dans les exports
	- RO=salut && export RO -- affiche RO dans les exports avec sa value

	- RO=salut -- définie la value 'salut' pour la variable 'RO' mais elle n'est pas affiché dans export ni env 
	pour afficher une variable dans env ou export il faut l'export

	- RA= yo -- bash: yo: command not found

- env : affiche les variables export qui ont une valeur
	
	- env -- affiche les variables d'environnement qui ont une value et sont export de façon non trié 

	-- env TEST=OUI -- affiche la variable 'TEST' avec la value 'OUI' dans env MAIS si on retape la commande la variable 'TEST' ne reste pas


- Exemple : comande -- output

	export RA="" -- affiche dans export 'export RA="" ' -- affiche dans env 'RA='
	export RA    -- affiche dans export 'export RA' -- affiche rien dans env
	export RA=salut RO=je RI=un RP=test  -- affiche dans export et env les 3 variables avec leurs values





 - notes : 


	- test tricky : < Makefile cat | cat 
