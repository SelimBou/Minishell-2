/*
** EPITECH PROJECT, 2023
** my_strcpy.c
** File description:
** my_strcpy.c
*/

#include "shell_two.h"

char *my_strcpy(char *dest, char *src)
{
    int index = 0;

    while (src[index] != '\0') {
        dest[index] = src[index];
        index ++;
    }
    dest[index] = '\0';
    return dest;
}
