/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** my_strrchr.c
*/

#include "shell_two.h"

char *my_strrchr(const char *s, int c)
{
    const char *last_occurrence = NULL;

    while (*s != '\0') {
        if (*s == c) {
            last_occurrence = s;
        }
        s++;
    }
    if (c == '\0') {
        return (char *)s;
    }
    return (char *)last_occurrence;
}
