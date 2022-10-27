//< infile wc << stop < infile infile infile
// heredoc> coucou
// heredoc> stop
//  3  5 21 infile
//  3  5 21 infile
//  6 10 42 total





/*


contenu de la struc ->
                        - int input   (fd d'entree aui prendra stdin)
                        - int output   (fd de sortie qui prendra stdout)
                        - int input2  ?
                        - int output2 ?

arguments de main -> 
                        - ligne de commande parsee
                        - infos du lexer
                        - structure
                        - liste env







                                POUR EXECUTER UNE SEULE COMMANDE SANS PIPE




MAIN
{
    -> Va recevoir une string de commande "safe"


    1. Ouvrir les fd necessaires a l'execution de la commande
        -> Verifie la presence de > < >> << dans la commande
            -> A chaque occurence execute la fonction associee
                -> La fonction associee ouvre/cree le here doc ou le fichier et le lit
                -> Puis execute puis attribue le pipe de sortie ou d'entree a celui ci
        -> Remplacer STDIN et STDOUT avec dup2
        -> Sistdin et stdout ne sont pas modifies -> utiliser STDIN STDOUT classiques

    2. Verifier que la commande a executer soit un Built-In ou non.
        -> Parser la ligne de commande  la recherche d'un builtin (infos grace au lexer?) 
        -> Normalement il  ne devrait pas y avoir d'erreur d'argument
        -> si un builtin est present executer la fonction associee
            -> la fonction du buildin est executee et on Exit (Sauf si Pipe)
    
    3. Verifier si il y a un $ ou une autre variable qui influe l'environnement
        -> Executer les fonctions associees
    
    4. Si la commande n'est pas un Built-In, envoyer le fd d'entree et de sortie comme argument pour la fonction d'execution  
        -> Fork
        -> Recuperer le PATH de la commande
        -> Execve la commande

}




















*/












