/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** shell2.h
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef __SHELL__
#define __SHELL__
#define true (1)

/*typedef struct shell2_s*/

int main(int ac, char **av, char** envp);
char *init_env(char **env2);
char **findcmd(char *cmd, int len);
int cd(cmd);
char *my_argselect(char *s,int first);
int my_strlendeli(char *str, int start);

#endif // ! __SHELL__ ! \\