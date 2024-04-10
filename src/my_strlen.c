/*
** EPITECH PROJECT, 2023
** my_strlen.c
** File description:
** my 7th program
*/

#include "shell_two.h"

int my_strlen(char const *str)
{
    int index = 0;

    while (str[index] != '\0') {
        index += 1;
    }
    return index;
}
