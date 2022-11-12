
#include "../includes/minishell.h"




/*
To do list :

-gerer l'ajout d'une variable d'env
- Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
-env sans aucune option ni argument
-export sans aucune option
-unset sans aucune option
-bash: export: `$=COUCOUCAVABIEN': not a valid identifier
- faire une difference entre pwd et export (stocker export ailleur??)
-. export une variable vide
- gerer inception de shell?  (execution de ./minishell)
- Creer une fonction qui va chercher et renvoyer une ligne specifique de l'env (pour la modifier ou la supprimer ou l'afficher par ex)

   Unsetting a variable or function that was not previously set
       shall not be considered an error and does not cause the shell to
       abort.

gerer dollar de dollar
*/
