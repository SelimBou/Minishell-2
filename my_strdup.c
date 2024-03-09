/*
** EPITECH PROJECT, 2023
** B-CPE-110-MAR-1-1-organized-selim.bouasker
** File description:
** my_strdup.c
*/

#include "shell_two.h"

char *my_strdup(char *str)
{
    int str_len = my_strlen(str) + 1;
    char *str_dup = malloc(str_len);

    if (str_dup == NULL) {
        write(2, "Error in memeory allocation\n", 29);
        return NULL;
    }
    str_dup = my_strcpy(str_dup, str);
    str_dup[str_len - 1] = '\0';
    return str_dup;
}
