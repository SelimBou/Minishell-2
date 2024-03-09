/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** is_digit.c
*/

#include "shell_two.h"

int alpha_num(const char *str)
{
    int i = 1;

    while (str[i] != '\0') {
        if (is_alpha(str[i]) == 0 || (str[i] >= '0' && str[i] <= '9') ||
            str[i] == '_')
            i ++;
        else
            return 1;
    }
    return 0;
}
