/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** parse.c
*/

#include "shell.h"
#include "string.h"
#include <stdlib.h>

linked_list_t *create_command_list(char *str)
{
    char *beginning = str;
    int i;
    linked_list_t *list = 0;
    char *which;

    if (!str) return 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ';' && !my_str_startswith(str + i, "&&") &&
            !my_str_startswith(str + i, "||")) continue;
        which = str[i] == ';' ? ";" : (my_str_startswith(str + i, "&&") ? "&&"
            : "||");
        str[i] = '\0';
        list = ll_append(list, my_strdup(beginning));
        list = ll_append(list, my_strdup(which));
        beginning = str + i + my_strlen(which);
        i += my_strlen(which) - 1;
    }
    if (beginning != str + i) list = ll_append(list, my_strdup(beginning));
    return list;
}

linked_list_t *create_word_list(char *str)
{
    char *beginning = str;
    int i;
    linked_list_t *list = 0;

    if (!str) return 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') continue;
        if (beginning == str + i) {
            beginning = str + i + 1;
            continue;
        }
        str[i] = '\0';
        list = ll_append(list, beginning);
        beginning = str + i + 1;
    }
    if (beginning != str + i)
        list = ll_append(list, beginning);
    return list;
}

command_return_t parse_command(char *command, dictionary_t **env_vars,
    dictionary_t *builtins, pipe_param_t params)
{
    linked_list_t *word_list = create_word_list(command);
    int i = 0;
    command_return_t ret = {"", 0};
    command_t comm;

    comm.argc = ll_len(word_list);
    comm.env = env_vars;
    comm.stdin = params.stdin;
    comm.pipe_stdout = params.pipe_stdout;
    if (!word_list) return ret;
    comm.command = word_list->data;
    comm.argv = malloc(sizeof(char *) * (comm.argc + 1));
    for (linked_list_t *list = word_list; list; list = list->next) {
        comm.argv[i] = my_strdup(list->data);
        i++;
    }
    comm.argv[i] = 0;
    ll_free(word_list, no_free);
    ret = builtin_check(comm, builtins);
    for (i = 0; i < comm.argc; i++) free(comm.argv[i]);
    free(comm.argv);
    return ret;
}

command_return_t parse_input(char *command, dictionary_t **env_vars,
    dictionary_t *builtins)
{
    linked_list_t *command_list = create_command_list(command);
    command_return_t ret = {"", 0};
    int operator = OPERATOR_NEWLINE;

    if (!command || !my_strcmp(command, "")) return ret;
    for (linked_list_t *i = command_list; i; i = i->next) {
        if (!my_strcmp(i->data, ";") || !my_strcmp(i->data, "&&") ||
            !my_strcmp(i->data, "||")) {
            operator = !my_strcmp(i->data, ";") ? OPERATOR_NEWLINE :
                (!my_strcmp(i->data, "&&") ? OPERATOR_AND : OPERATOR_OR);
            continue;
        }
        if (operator == OPERATOR_NEWLINE || (operator == OPERATOR_AND &&
            !ret.return_value) || (operator == OPERATOR_OR && ret.return_value))
            ret = parse_pipes(i->data, env_vars, builtins);
    }
    ll_free(command_list, free);
    return ret;
}