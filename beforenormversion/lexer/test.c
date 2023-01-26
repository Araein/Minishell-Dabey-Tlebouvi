// /*#include <stdio.h>

// #include <stdlib.h>

// #include <string.h>



// // Structure pour stocker les informations de redirection et de pipe

// struct cmd_info {

//     char *input_file;

//     char *output_file;

//     char *herdoc_delimiter;

//     int is_append;

//     int is_herdoc;

//     int is_pipe;

//     char **argv;

// };



// // Fonction pour parser la commande

// void parse_cmd(char *cmd, struct cmd_info *info) {

//     char *token, *temp;

//     int argc = 0, i;



//     // Initialisation de la structure

//     info->input_file = NULL;

//     info->output_file = NULL;

//     info->herdoc_delimiter = NULL;

//     info->is_append = 0;

//     info->is_herdoc = 0;

//     info->is_pipe = 0;

//     info->argv = (char**)malloc(sizeof(char*) * 100);



//     // Boucle pour séparer les mots de la commande

//     token = strtok(cmd, " \t\n");

//     while (token != NULL) {

//         // Si le mot est une redirection d'entrée

//         if (strcmp(token, "<") == 0) {

//             // Récupération du nom du fichier d'entrée

//             token = strtok(NULL, " \t\n");

//             info->input_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->input_file, token);

//         }

//         // Si le mot est une redirection de sortie

//         else if (strcmp(token, ">") == 0) {

//             // Récupération du nom du fichier de sortie

//             token = strtok(NULL, " \t\n");

//             info->output_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->output_file, token);

//         }

//         // Si le mot est une redirection de sortie en mode append

//         else if (strcmp(token, ">>") == 0) {

//             // Récupération du nom du fichier de sortie

//             token = strtok(NULL, " \t\n");

//             info->output_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->output_file, token);

//             info->is_append = 1;

//         }

//         // Si le mot est un herdoc

//         else if (strcmp(token, "<<") == 0) {

//             // Récupération du délimiteur du herdoc

//             token = strtok(NULL, " \t\n");

//             info->herdoc_delimiter = (char*)malloc(sizeof(char) * (strlen(

// //Voici un exemple de fonction qui parse une commande d'un shell qui contient des redirections, 
// //des herdocs, des simples guillemets, des doubles guillemets et des pipes :

// */
// #include <stdio.h>

// #include <stdlib.h>

// #include <string.h>



// // Structure pour stocker les informations de redirection et de pipe

// struct cmd_info {

//     char *input_file;

//     char *output_file;

//     char *herdoc_delimiter;

//     int is_append;

//     int is_herdoc;

//     int is_pipe;

//     char **argv;

// };


// // Fonction pour parser la commande

// void parse_cmd(char *cmd, struct cmd_info *info) {

//     char *token, *temp;

//     int argc = 0, i;



//     // Initialisation de la structure

//     info->input_file = NULL;

//     info->output_file = NULL;

//     info->herdoc_delimiter = NULL;

//     info->is_append = 0;

//     info->is_herdoc = 0;

//     info->is_pipe = 0;

//     info->argv = (char**)malloc(sizeof(char*) * 100);



//     // Boucle pour séparer les mots de la commande

//     token = strtok(cmd, " \t\n");

//     while (token != NULL) {

//         // Si le mot est une redirection d'entrée

//         if (strcmp(token, "<") == 0) {

//             // Récupération du nom du fichier d'entrée

//             token = strtok(NULL, " \t\n");

//             info->input_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->input_file, token);

//         }

//         // Si le mot est une redirection de sortie

//         else if (strcmp(token, ">") == 0) {

//             // Récupération du nom du fichier de sortie

//             token = strtok(NULL, " \t\n");

//             info->output_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->output_file, token);

//         }

//         // Si le mot est une redirection de sortie en mode append

//         else if (strcmp(token, ">>") == 0) {

//             // Récupération du nom du fichier de sortie

//             token = strtok(NULL, " \t\n");

//             info->output_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->output_file, token);

//             info->is_append = 1;

//         }

//         // Si le mot est un herdoc

//         else if (strcmp(token, "<<") == 0) {

//             // Récupération du délimiteur du herdoc

//             token = strtok(NULL, " \t\n");

//             info->herdoc_delimiter = (char*)malloc(sizeof(char) * (strlen( token) + 1));// suite

//             strcpy(info->herdoc_delimiter, token);

//             info->is_herdoc = 1;

//         }

//         // Si le mot est une guillemet simple

//         else if (strcmp(token, "'") == 0) {

//             temp = (char*)malloc(sizeof(char) * 100);

//             i = 0;

//             // Récupération de la chaîne entre les guillemets simples

//             token = strtok(NULL, "'");

//             while (token != NULL) {

//                 temp[i] = token[i];

//                 i++;

//             }

//             temp[i] = '\0';

//             // Ajout de la chaîne dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));

//             strcpy(info->argv[argc], temp);

//             argc++;

//         }
//         // Si le mot est une guillemet double

//         else if (strcmp(token, "\"") == 0) {

//             temp = (char*)malloc(sizeof(char) * 100);

//             i = 0;

//             // Récupération de la chaîne entre les guillemets doubles

//             token = strtok(NULL, "\"");

//             while (token != NULL) {

//                 temp[i] = token[i];

//                 i++;

//             }

//             temp[i] = '\0';

//             // Ajout de la chaîne dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));

//             strcpy(info->argv[argc], temp);

//             argc++;

//         }

//         // Si le mot est un pipe

//         else if (strcmp(token, "|") == 0) {

//             // Mise à jour de la variable pour indiquer qu'il y a un pipe

//             info->is_pipe = 1;

//         }

//         else {

//             // Ajout du mot dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->argv[argc], token);

//             argc++;

//         }



//         token = strtok(NULL, " \t\n");

//     }



//     // Ajout d'un marqueur de fin pour les arguments

//     info->argv[argc] = NULL;

// }



// // suite



//  token) + 1));

//             strcpy(info->herdoc_delimiter, token);

//             info->is_herdoc = 1;

//         }

//         // Si le mot est une guillemet simple

//         else if (strcmp(token, "'") == 0) {

//             temp = (char*)malloc(sizeof(char) * 100);

//             i = 0;

//             // Récupération de la chaîne entre les guillemets simples

//             token = strtok(NULL, "'");

//             while (token != NULL) {

//                 temp[i] = token[i];

//                 i++;

//             }

//             temp[i] = '\0';

//             // Ajout de la chaîne dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));

//             strcpy(info->argv[argc], temp);

//             argc++;

//         }

//         // Si le mot est une guillemet double

//         else if (strcmp(token, "\"") == 0) {

//             temp = (char*)malloc(sizeof(char) * 100);

//             i = 0;

//             // Récupération de la chaîne entre les guillemets doubles

//             token = strtok(NULL, "\"");

//             while (token != NULL) {

//                 temp[i] = token[i];

//                 i++;

//             }

//             temp[i] = '\0';

//             // Ajout de la chaîne dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));

//             strcpy(info->argv[argc], temp);

//             argc++;

//         }

//         // Si le mot est un pipe

//         else if (strcmp(token, "|") == 0) {

//             // Mise à jour de la variable pour indiquer qu'il y a un pipe

//             info->is_pipe = 1;

//         }

//         else {

//             // Ajout du mot dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->argv[argc], token);

//             argc++;

//         }



//         token = strtok(NULL, " \t\n");

//     }



//     // Ajout d'un marqueur de fin pour les arguments

//     info->argv[argc] = NULL;

// }

// /*

// Cette fonction utilise la fonction strtok() pour séparer les mots de la commande en utilisant les espaces, les tabulations et les sauts de ligne comme délimiteurs. Ensuite, il vérifie chaque mot pour voir s'il s'agit d'une redirection, d'un herdoc, d'une guillemet simple ou double ou d'un pipe et stocke les informations appropriées dans la structure struct cmd_info.

// Gardez à l'esprit





// Il est important de garder à l'esprit que cette fonction est un exemple de base et qu'elle pourrait nécessiter des améliorations ou des ajustements en fonction des besoins spécifiques de votre application. Par exemple, vous pourriez vouloir ajouter des vérifications supplémentaires pour gérer les erreurs de syntaxe, gérer les variables d'environnement et les variables utilisateur, gérer les séquences d'échappement, etc. Il est important de tester soigneusement la fonction avec différentes commandes pour s'assurer qu'elle fonctionne comme prévu.



// je veux bien ajouter au code  les erreurs de syntaxe, gérer les variables d'environnement et les variables.





// Pour gérer les erreurs de syntaxe dans la fonction parse_cmd(), vous pourriez ajouter des vérifications supplémentaires pour vérifier que les redirections et les herdocs sont utilisés de manière appropriée, par exemple en vérifiant qu'il y a un nom de fichier après les symboles de redirection, qu'il n'y a qu'un seul pipe par commande, etc. Vous pouvez également ajouter un message d'erreur pour informer l'utilisateur de l'erreur de syntaxe.

// Pour gérer les variables d'environnement et les variables utilisateur, vous pourriez ajouter des fonctions pour récupérer la valeur d'une variable en utilisant sa clé. Pour les variables d'environnement, vous pourriez utiliser la fonction getenv() et pour les variables utilisateur, vous pourriez utiliser un tableau ou un dictionnaire pour stocker les clés et les valeurs des variables. Vous pourriez également ajouter une fonction pour définir une variable en utilisant sa clé et sa valeur. Il est important de vérifier la présence des variables avant de les utiliser dans la commande.

// Voici un exemple de comment vous pourriez implémenter cela dans la fonction parse_cmd() :


// */


// void parse_cmd(char *cmd, struct cmd_info *info) {

//     char *token, *temp;

//     int argc = 0, i;



//     // Initialisation de la structure

//     info->input_file = NULL;

//     info->output_file = NULL;

//     info->herdoc_delimiter = NULL;

//     info->is_append = 0;

//     info->is_herdoc = 0;

//     info->is_pipe = 0;

//     info->argv = (char**)malloc(sizeof(char*) * 100);



//     // Boucle pour séparer les mots de la commande

//     token = strtok(cmd, " \t\n");

//     while (token != NULL) {

//         // Si le mot est une redirection d'entrée

//         if (strcmp(token, "<") == 0) {

//             // Récupération du nom du fichier d'entrée

//             token = strtok(NULL, " \t\n");

//             if (token == NULL) {

//                 printf("Erreur de syntaxe : nom de fichier manquant après <\n");

//                 exit(1);

//             }

//             info->input_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->input_file, token);

//         }

//         // Si le mot est une redirection de sortie
//         else if (strcmp(token, ">") == 0) {

//             // Récupération du nom du fichier de sortie

//             token = strtok(NULL, " \t\n");

//             if (token == NULL) {

//                 printf("Erreur de syntaxe : nom de fichier manquant après >\n");

//                 exit(1);

//             }

//             info->output_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->output_file, token);

//         }

//         // Si le mot est une redirection de sortie en mode append

//         else if (strcmp(token, ">>") == 0) {

//             // Récupération du nom du fichier de sortie

//             token = strtok(NULL, " \t\n");

//             if (token == NULL) {

//                 printf("Erreur de syntaxe : nom de fichier manquant après >>\n");

//                 exit(1);

//             }

//             info->output_file = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->output_file, token);

//             info->is_append = 1;

//         }

//         // Si le mot est un herdoc

//         else if (strcmp(token, "<<") == 0) {

//             // Récupération du délimiteur du herdoc

//             token = strtok(NULL, " \t\n");

//             if (token == NULL) {

//                 printf("Erreur de syntaxe : délimiteur manquant après <<\n");

//                 exit(1);

//             }

//             info->herdoc_delimiter = (char*)malloc(sizeof(char) * (strlen(token) + 1));

//             strcpy(info->herdoc_delimiter, token);

//             info->is_herdoc = 1;

//         }

//         // Si le mot est une guillemet simple

//         else if (strcmp(token, "'") == 0) {

//             temp = (char*)malloc(sizeof(char) * 100);

//             i = 0;

//             // Récupération de la chaîne entre les guillemets simples

//             token = strtok(NULL, "'");

//             while (token != NULL) {

//                 temp[i] = token[i];

//                 i++;

//             }

//             temp[i] = '\0';

//             // Ajout de la chaîne dans les arguments

//             info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(temp) + 1));

//             strcpy(info->argv[argc], temp);

//             argc++;

//         }

//         // Si le mot est une guillemet double

//         else if (strcmp(token, "\"") == 0) {

//             temp = (char*)malloc(sizeof(char) * 100);

//             i = 0;

//             // Récupération


//        else if (token[0] == '$') {

//             // Récupération de la valeur de la variable d'environnement ou utilisateur

//             char *var = getenv(token + 1); // Pour les variables d'environnement

//             // Ou utilisez une fonction pour récupérer la valeur de la variable utilisateur à partir de son nom

//             if (var != NULL) {

//                 // Ajout de la valeur de la variable dans les arguments

//                 info->argv[argc] = (char*)malloc(sizeof(char) * (strlen(var) + 1));

//                 strcpy(info->argv[argc], var);

//                 argc++;

//             } else {

//                 printf("Variable %s non définie\n", token);

//                 exit(1);

//             }

//         }

//         // Si le mot est un pipe

//         else if (strcmp(token, "|") == 0) {

//             // Vérification s'il y a plus d'un pipe

//             if (info->is_pipe) {

//                 printf("Erreur de syntaxe : plus d'un pipe dans la commande\n");

//                 exit(1);

//             }

//             // Mise à jour de la variable pour indiquer qu'il y a un pipe

//             info->is_pipe = 1;

//         }

// //La fonction getenv() est utilisée pour récupérer la valeur d'une variable 
// // d'environnement en utilisant sa clé. Si la variable n'est pas définie,
// //  getenv() renvoie NULL. Si vous utilisez un tableau ou un dictionnaire
// //   pour stocker les variables utilisateur, vous pouvez récupérer leur valeur 
// //   en utilisant leur nom comme clé. Il est important de vérifier la présence 
// //   des variables avant de les utiliser dans la commande, et de gérer 
// //   les erreurs en cas de non définition de la variable
 