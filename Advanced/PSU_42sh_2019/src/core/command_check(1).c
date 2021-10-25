/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** command_check.c
*/

#include "shell.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *check_existence(dictionary_t *env, char *binary_name)
{
    char *path = dict_get(env, "PATH");
    char **parsed_path = path ? my_strsplit(path, ':') : 0;
    char *current = my_strdup("");
    int binary_not_found = 1;
    int line = 0;

    while (parsed_path && parsed_path[line] && !my_strstr(binary_name, "/")) {
        current = my_free_assign(current, my_strconcat("/", binary_name));
        current = my_free_assign(current,
            my_strconcat(parsed_path[line], current));
        binary_not_found = access(current, F_OK);
        if (!binary_not_found) return current;
        line++;
    }
    if (my_strstr(binary_name, "/"))
        return access(binary_name, F_OK) ? 0 : binary_name;
    return 0;
}

command_return_t check_command(command_t command)
{
    char *binary_name = command.argv[0];
    char *bin = check_existence(*command.env, binary_name);
    command_return_t ret;
    int right;

    ret.stdout = 0;
    if (bin != 0) right = access(bin, X_OK);
    else {
        my_printf("42sh: no such file or directory: %s\n", command.argv[0]);
        ret.return_value = 127;
        return ret;
    }
    if (right == 0) {
        command.command = bin;
        return exec(command);
    } else {
        my_printf("42sh: permission denied: %s\n", command.argv[0]);
        ret.return_value = 126;
        return ret;
    }
}