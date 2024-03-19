/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** redirect.c
*/

#include "shell_two.h"

void left_redirect(params_t *params, int *fd, int i)
{
    *fd = open(params->token_list[i + 1], O_RDONLY);
    if (*fd == -1) {
        exit(EXIT_FAILURE);
    }
    dup2(*fd, STDIN_FILENO);
    close(*fd);
    params->token_list[i] = NULL;
}

void right_redirect(params_t *params, int *fd, int i)
{
    *fd = open(params->token_list[i + 1], O_WRONLY | O_CREAT |
        O_TRUNC, S_IRUSR | S_IWUSR);
    if (*fd == -1) {
        exit(EXIT_FAILURE);
    }
    dup2(*fd, STDOUT_FILENO);
    close(*fd);
    params->token_list[i] = NULL;
}

void redirect(params_t *params)
{
    int i = 0;
    int fd;

    while (params->token_list[i] != NULL) {
        if (my_strcmp(params->token_list[i], "<") == 0) {
            left_redirect(params, &fd, i);
        }
        if (my_strcmp(params->token_list[i], ">") == 0) {
            right_redirect(params, &fd, i);
        }
        i++;
    }
}
