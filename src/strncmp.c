/*
** EPITECH PROJECT, 2023
** recode
** File description:
** strcmp.c
*/
#include "shell_two.h"

int my_strncmp(const char *s1, const char *s2, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        if (s1[i] == '\0')
            return 0;
    }
    return 0;
}
