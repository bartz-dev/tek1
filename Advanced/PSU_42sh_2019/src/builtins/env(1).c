/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** env.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

command_return_t builtin_env(int argc, char **argv, dictionary_t **env)
{
    command_return_t ret;

    ret.return_value = 0;
    ret.stdout = "";
    UNUSED(argv);
    UNUSED(argc);
    for (dictionary_t *i = *env; i; i = i->next)
        my_printf("%s=%s\n", i->index, i->data);
    return ret;
}

command_return_t builtin_setenv(int argc, char **argv, dictionary_t **env)
{
    char *value = "";
    command_return_t ret;

    ret.return_value = 0;
    ret.stdout = "";
    if (argc == 1)
        return builtin_env(0, 0, env);
    else if (argc >= 3)
        value = argv[2];
    *env = env_set(*env, argv[1], value);
    return ret;
}

command_return_t builtin_unsetenv(int argc, char **argv, dictionary_t **env)
{
    command_return_t ret;

    ret.return_value = 0;
    ret.stdout = "";
    if (argc < 2) {
        my_printf("unsetenv: Too few arguments.\n");
        ret.return_value = 1;
        return ret;
    }
    *env = dict_remove(*env, argv[1]);
    return ret;
}