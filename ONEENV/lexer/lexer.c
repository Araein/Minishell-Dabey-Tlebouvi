// Lex : c'est un 
/*
 - un fichier.y pour definir les expression arithmitiques,
 definir les tokens et les expresions
 - la compilation ce fait avec => bison -d calc.y cela donnera
 un calc.tab.c et un calc.tab.h

 - un calc.l on definie les macros du calc.y 
 - la compilation ce fait avec =>  flex calc.l et elle produit
 le lex.yy.c

 - un fichier.c pour avoir un main 

 - on compile tout avec => gcc -o calc calc.c calc.tab.c lex.yy.c

// MOT = echo | cd | pwd | export | unset | env | exit | des paragraphes d'affichages  
> < >> << | ' " $ $?

faut un analyseur lexical qui va lire les caracteres d'entree et qui produit une suite 
d'unite lexical qui va etre traite par l'analyseur syntaxique, il elimine les cacractere
{\t, '\n', ' ', commentaires ...} et il gere aussi les erreur et affiche la ligne ou y a l'erreur

l'unite lexical ou token : c'est un couple compose d'un nom et d'une valeur optionnelle
quelque nom d;unite lexical :
- identifiers : nom de variables ou de fonctions choisis par le programmeur du code analysé. Ne peut être un mot réservé du langage
- keywords : mots réservés du langage
- separators : caractères de ponctuation simples comme les points et les virgules ou composés comme les parenthèses et les crochets
- operators : symboles s'appliquant sur des arguments et produisant un résultat 
- literals : suite de caractères représentant une valeur numérique, logique, etc.
 
Un modele est une regle associer a une unite lexical  

************************* Code LEX *****************************
%{ //section des declarations
declarer des variables globales.
declarer des fonctions globales.
inclure des fichiers.
}%
///////////////////////////////////////////////////////
%% // section du code utilisateur
on ajoute des REGLES : une regle contient 2 elements :
- une expression reguliere
- et du code C.
%%
la fonction main et les autres fonctions.
main() {
yylex();\\ c'est la routine qui effectue l’appel explicite de l’analyseur lexical
execution de code ;
}
///////////////////////////////////
avoir une liste chainee de token qui a la structure suivante : 
- enum type :	none
				arg
				file_in ">"
				herdoc_in "<<"
				file_out "<" 
				herdoc_out ">>"
				name_file_in
				stop_herdoc
				name_file_out
				file_out_herdoc

- char *word
- struct token *next
*/