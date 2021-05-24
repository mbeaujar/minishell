

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


#### redir pipe

- echo salut > salut | echo 
- echo salut | echo > salut


- echo salut | cat > file | cat | cat --- affiche salut + écrit salut dans file



- echo bonjour > file | cat --- affiche bonjour + écrit bonjour dans file

    in        out       in      out 
    0         file      file      1


- echo salut | cat < file -- affiche salut + contenu de file 

    in         out      in      out
    0            1 ?    file          1


- echo salut | cat < file > salut --- affiche salut + contenu du file dans salut


    in      out          in              out
    0        salut?      file          salut


- cat salut < file  -- affiche le contenu du fichier en arguments


  cmd1 | cmd2

Si stdin de cmd2 est redirigé : 
    - stdout cmd1 est égal à stdout cmd2


echo pourquoisqs > test | wc

 in         out                 in                  out
0           wc                test + echo ??        1