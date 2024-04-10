/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** is_alpha.c
*/

int is_alpha(char c)
{
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        return 1;
    return 0;
}
