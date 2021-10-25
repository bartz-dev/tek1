/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell
*/

#ifndef SHELL_H_
#define SHELL_H_
#include "linked.h"
#include "tools.h"

#define OPERATOR_NONE 0
#define OPERATOR_OR 1
#define OPERATOR_AND 2
#define OPERATOR_NEWLINE 3

typedef struct expression {
    char *command;
    int argc;
    char **argv;
    int pipe_stdout;
    char *stdin;
} expression_t;

typedef struct command_return {
    char *stdout;
    int return_value;
} command_return_t;

char *get_command_line(void);
int display_prompt(dictionary_t *env);
int parse_input(char *command, dictionary_t **env_vars, dictionary_t *builtins);
dictionary_t *env_init(char **envp);
dictionary_t *env_set(dictionary_t *env_vars, char *index, char *value);
char **env_to_array(dictionary_t *env_vars);
int builtin_cd(int argc, char **argv, dictionary_t **env_vars);
int builtin_exit(int argc, char **argv, dictionary_t **env_vars);
int builtin_echo(int argc, char **argv, dictionary_t **env);
int builtin_env(int argc, char **argv, dictionary_t **env_vars);
int builtin_setenv(int argc, char **argv, dictionary_t **env_vars);
int builtin_unsetenv(int argc, char **argv, dictionary_t **env_vars);
dictionary_t *builtin_init(void);
int get_uid(char *username);
int builtin_check(int argc, char **argv, dictionary_t **env,
    dictionary_t *builtins);
int get_path_line(char *path);
char **malloc_parsed_path(char **parsed_path, char *path);
char **parse_path(char *path);
int check_folder(char *folder_path, char *binary);
char *check_existence(dictionary_t *env, char *binary_name);
int check_right(char *binary_path, char *binary_name);
int check_command(int argc, char **argv, dictionary_t *env);
int error_checker(int argc, char **argv, dictionary_t *env, char *cmd);
char *get_current_dir(dictionary_t *env);
#endif /* !SHELL_H_ */