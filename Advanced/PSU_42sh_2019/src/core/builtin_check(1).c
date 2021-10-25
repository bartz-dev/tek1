/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** builtin_check.c
*/

#include "shell.h"

command_return_t builtin_check(command_t command, dictionary_t *builtins)
{
    command_return_t (*builtin)(int, char **, dictionary_t **) =
        dict_get(builtins, command.argv[0]);

    if (builtin)
        return builtin(command.argc, command.argv, command.env);
    else
        return check_command(command);
}