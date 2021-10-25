/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** main.c
*/

#include "my.h"
#include "shell2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int checker = 0;
    char *path = "< ";
    char *env;
    char *str;
    char **tab; // = init_function();
    char **order;
    size_t buff_size = 5;

    if (my_strcmp(env = init_env(), "ERROR84") == 1)
        return 84;
    while (true) {
        my_putstr(path);
        if (checker = getline(&str, &buff_size, stdin) < 0)
            return 84;
        order = findcmd(str, my_strlen(str) - 1);
    }
}