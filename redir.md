

## Si il y a une redirection le fichier est automatiquement après

bash-4.4# ls > 
bash: syntax error near unexpected token `newline'

bash-4.4# cat <
bash: syntax error near unexpected token `newline'

---

#### Si '<' alors check si le fichier dans l'argument d'après existe

---

#### < -- Si le fichier existe pas
bash-4.4# echo salut < inconnu
bash: inconnu: No such file or directory

---
#### Type de format 

- echo salut < STDIN
- < STDIN echo salut
- echo < STDIN salut

---

#### Si > alors l'argument d'après est le fichier

- > STDOUT echo salut
- echo > STDOUT salut
- echo salut > STDOUT

---

#### < > -- Exemple avec les deux

- < STDIN > STDOUT cat
- cat < STDIN > STDOUT
- < STDIN > STDOUT cat

---

#### cas special

- cat <> STDIN    --- la redir STDOUT est ignoré , l'inverse "><" ne marche pas



