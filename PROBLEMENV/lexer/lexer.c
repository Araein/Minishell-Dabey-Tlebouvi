// Lex : c'est un 
/*
 - un fichier.y pour definir les expression arithmitiques,
 definir les tokens et les expresions
 - la compilation ce fait avec => bison -d calc.y cela donnera
 un calc.tab.c et un calc.tab.h
 */
/*
 - un calc.l on definie les macros du calc.y 
 - la compilation ce fait avec =>  flex calc.l et elle produit
 le lex.yy.c
 */
/*
 - un fichier.c pour avoir un main 
*/
/*
 - on compile tout avec => gcc -o calc calc.c calc.tab.c lex.yy.c
*/
// MOT = echo | cd | pwd | export | unset | env | exit | des paragraphes d'affichages  
/*
> < >> << | ' " $ $?
