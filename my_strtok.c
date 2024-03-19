/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** TEST.c
*/

#include "shell_two.h"

char *my_strtok(char *str, int index, char *delim)
{
    char *token;
    char *str_copy = my_strdup(str);
    char *result;
    int i = 0;

    token = strtok(str_copy, delim);
    while (token != NULL) {
        if (i == index) {
            result = my_strdup(token);
            free(str_copy);
            return result;
        }
        token = strtok(NULL, delim);
        i++;
    }
    free(str_copy);
    return NULL;
}
