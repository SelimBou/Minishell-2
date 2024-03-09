/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** my_strcat.c
*/
#include "shell_two.h"

char *my_strcat(char *dest, char *src)
{
    char *ptr = dest;

    while (*ptr != '\0') {
        ptr++;
    }
    while (*src != '\0') {
        *ptr = *src;
        *ptr ++;
        *src ++;
    }
    *ptr = '\0';
    return dest;
}
