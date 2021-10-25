/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "shell.h"

int main(int argc, char **argv, char **envp)
{
    dictionary_t *env = env_init(envp);
    dictionary_t *builtins = builtin_init();
    char *command_line;
    int var = 1;

    UNUSED(argc);
    UNUSED(argv);
    while (var == 1) {
        display_prompt(env);
        command_line = get_command_line();
        error_checker(argc, argv, env, command_line);
        parse_input(command_line, &env, builtins);
    }
    return 0;
}