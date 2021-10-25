/*
** EPITECH PROJECT, 2020
** checkword
** File description:
** 
*/

#include "my.h"

char *getword()
{
    char *word = NULL;
    size_t t = 0;

    printf("\n>");
    getline(&word, &t, stdin);
    return word;
}
