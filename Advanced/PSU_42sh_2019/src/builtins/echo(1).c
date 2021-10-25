/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** echo.c
*/

#include "shell.h"

char *print_stdout(char *stdout, char *to_add)
{
    my_putstr(to_add);
    return my_free_assign(stdout, my_strconcat(stdout, to_add));
}

command_return_t builtin_echo(int argc, char **argv, dictionary_t **env)
{
    int i = 1;
    command_return_t ret;

    ret.return_value = 0;
    ret.stdout = my_strdup("");
    UNUSED(env);
    if (argc <= 1) {
        ret.stdout = print_stdout(ret.stdout, "\n");
        return ret;
    }
    if (my_strcmp(argv[1], "-n") == 0)
        i = 2;
    while (i < argc) {
        ret.stdout = print_stdout(ret.stdout, argv[i]);
        if (i < argc - 1) ret.stdout = print_stdout(ret.stdout, " ");
        i++;
    }
    if (my_strcmp(argv[1], "-n") == 1)
        ret.stdout = print_stdout(ret.stdout, "\n");
    return ret;
}