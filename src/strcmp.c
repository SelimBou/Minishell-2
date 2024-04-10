/*
** EPITECH PROJECT, 2023
** recode
** File description:
** strcmp.c
*/
#include "shell_two.h"

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}
