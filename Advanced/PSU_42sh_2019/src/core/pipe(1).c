/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** pipe.c
*/

#include "shell.h"
#include <unistd.h>
#include <signal.h>

command_return_t parse_pipes(char *command, dictionary_t **env_vars,
    dictionary_t *builtins)
{
    char **split_command = my_strsplit(command, '|');
    command_return_t ret;
    pipe_param_t params = {0, ""};

    params.stdin = my_strdup("");
    for (int i = 0; split_command[i]; i++) {
        params.pipe_stdout = (split_command[i + 1] != 0);
        ret = parse_command(split_command[i], env_vars, builtins, params);
        params.stdin = ret.stdout;
    }
    return ret;
}

command_return_t parent_exec(command_t command, pipes_t pipes,
    int child_pid)
{
    struct sigaction sa;
    struct sigaction old_sa;
    char buff[65536];
    command_return_t ret;

    sa.sa_handler = signal_handler;
    close(pipes.stdout[1]);
    close(pipes.stdin[0]);
    write(pipes.stdin[1], command.stdin, my_strlen(command.stdin));
    close(pipes.stdin[1]);
    sigaction(SIGINT, &sa, &old_sa);
    ret.return_value = wait_loop(child_pid);
    sigaction(SIGINT, &old_sa, NULL);
    read(pipes.stdout[0], buff, 65536);
    close(pipes.stdout[0]);
    ret.stdout = my_strdup(buff);
    return ret;
}

void child_exec(command_t command, pipes_t pipes)
{
    close(pipes.stdout[0]);
    close(pipes.stdin[1]);
    if (command.pipe_stdout) {
        dup2(pipes.stdout[1], 1);
        dup2(pipes.stdout[1], 2);
    } else write(pipes.stdout[1], "", 0);
    dup2(pipes.stdin[0], 0);
    close(pipes.stdout[1]);
    execve(command.command, command.argv, env_to_array(*command.env));
}