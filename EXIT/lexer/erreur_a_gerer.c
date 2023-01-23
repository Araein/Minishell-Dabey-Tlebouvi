/*
/***********************DEBUT************************\
 * 
=> ./minishell text => doit renvoyer une erreur



/***********************MILIEUX************************\
=> verifier le export avec text5485text
=> tester les "test"text
* => le exit ne marche pas comme il faut : le probleme c'est le SHLVL qui change 
de 2 a 1 lors du remplicage de la liste chainee
=> echo $HOME $home test  test $home $HOME '$HOME'=> erreur lors de
l'interpretation du 2 eme $HOME  


////////// code test //////////
Minishell$> echo $HOME$HOME
str_d_origin = HOME$HOME
str_cmd[0]=echo .


Minishell$> echo $HOME $HOME
str_d_origin = HOME
str_d_origin = �NgHOME
str_cmd[0]=echo /mnt/nfs/homes/dabey .

/mnt/nfs/homes/dabey
Minishell$> echo $HOME test $HOME
str_d_origin = HOME
str_d_origin = OgHOME
str_cmd[0]=echo /mnt/nfs/homes/dabey test .

/mnt/nfs/homes/dabey test

////////////////
/***********************FIN************************\
*/
/*
#include <stdio.h>
#include <stdlib.h>
int ft_strlen(const char *s){
int i= 0;
if (!s)
return (0);
while(s[i])
i++;
return (i);}
int close_quote(char *line, int i){
while (line[i]){
if (line[i] && line[i] != '\'')
i++;
else
return(++i);}
return (-1);}
char *ft_new_cmd(char *line, char *str_d, int j)
{
  int i,k,x,len_t;
  char    *str_1;

  i = 0;
  k = 0;
  x = 0;
  len_t = ft_strlen(line) + ft_strlen(str_d);
  str_1 = malloc(sizeof(char) * (len_t - j + 1));// le dollar est il inclus
  if (!str_1)
      return (NULL);
  while (line[i])
  {
    while (line[i] && line[i] != '$' && line[i] != '\'')
        str_1[k++] = line[i++];
    // printf("str_1 = %s\n\n",str_1);
    if (line[i] == '$')
    {
      i = i + j;
      j = 0;
      while (str_d && str_d[j])// a voir 
          str_1[k++] = str_d[j++];
      // printf("i = %d et j = %d\n", i,j);
  }
    while (line[i])
        str_1[k++] = line[i++];
    str_1[k] = '\0';
  }
  // free(str_d);
  // str_d = str_1;
  return (str_1);
}
char    *find_expand_dollar(char *line)
{
  int  i,j, k,x;
  char    *str_d;
  i = 0;
  j = 0;
  k = 0;
  x = 0;
  str_d = NULL;
  while (line[i])
  {
    if (line[i] == '\'')
        i = close_quote(line, ++i);
    else if (line[i] == '$')
    {
      j = i;
      while (line[j] && line[j] != ' ' && line[j] != '\''
      && line[j] != '\"')
          j++;
      x = j - i + 1;
      str_d = malloc(sizeof(char) * x);
      j = i;
      k = 0;
      while (line[j] && line[j] != ' ' && line[j] != '\"'
          && line[j] != '\'')
          str_d[k++] = line[j++];
      str_d[k] = '\0';
      // printf("str_dollar = %s et j = %d\n\n", str_d, j - 1);
      str_d = "/dabey";
      // printf("str_d_1 = %s\n\n", str_d);
      // if (str_d)
      // {
      str_d = ft_new_cmd(line, str_d, x);
      // printf("str_d_2 = %s\n", str_d);
      line = str_d;
    }
    else
      i++;
}
  return (line);
}
int main() {
char *cmd = malloc(sizeof(char) * 30);
cmd = "t $HO $ME";
cmd = find_expand_dollar(cmd);
return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(const char *s){
int i= 0;
if (!s)
return (0);
while(s[i])
i++;
return (i);}
int close_quote(char *line, int i){
while (line[i]){
if (line[i] && line[i] != '\'')
i++;
else
return(++i);}
return (-1);}
char *ft_new_cmd(char *line, char *str_d, int x, int *index)
{
  int i,k,len_t;
  char    *str_1;

  i = 0;
  k = 0;
  len_t = ft_strlen(line) + ft_strlen(str_d);
  str_1 = malloc(sizeof(char) * (len_t - x + 1));
  if (!str_1)
      return (NULL);
  while (line[i])
  {
    while (line[i] && line[i] != '$' && line[i] != '\'')
        str_1[k++] = line[i++];
    if (line[i] == '$')
    {
      *index = i + x;//4
      i += x;
      x = 0;
      while (str_d && str_d[x])
          str_1[k++] = str_d[x++];
  }
    while (line[i])
        str_1[k++] = line[i++];
    str_1[k] = '\0';
  }
  return (str_1);
}
char    *find_expand_dollar(char *line)
{
  int  i,j, k,x;
  char    *str_d;
  i = 0;
  j = 0;
  k = 0;
  x = 0;
  str_d = NULL;
  while (line[i])
  {
    if (line[i] == '\'')
        i = close_quote(line, ++i);
    else if (line[i] == '$')
    {
      j = i;
      while (line[j] && line[j] != ' ' && line[j] != '\''
      && line[j] != '\"')
          j++;
      x = j - i + 1;
      str_d = malloc(sizeof(char) * x);
      j = i;
      k = 0;
      while (line[j] && line[j] != ' ' && line[j] != '\"'
          && line[j] != '\'')
          str_d[k++] = line[j++];
      str_d[k] = '\0';
      str_d = "/mnt/nfs/homes/dabey";
      str_d = ft_new_cmd(line, str_d, x - 1, &i);
      line = str_d;
    }
    else
      i++;
}
  return (line);
}
int main() {
char *cmd = malloc(sizeof(char) * 30);
cmd = "tata $HOME et du text $HOME et un autre $HOME titi";
cmd = find_expand_dollar(cmd);
printf("cmd = %s\n\n",cmd);
return 0;
}