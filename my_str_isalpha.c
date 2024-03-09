/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** my_str_isalpha.c
*/

#include "shell_two.h"

int my_str_isalpha(const char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z'))
            return 1;
        i ++;
    }
    return 0;
}
