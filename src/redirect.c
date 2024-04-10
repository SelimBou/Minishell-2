/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** redirect.c
*/

#include "shell_two.h"

void left_redirect(params_t *params, int i)
{
    int fd = open(params->token_list[i + 1], O_RDONLY);

    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        exit(EXIT_FAILURE);
    }
    close(fd);
    params->token_list[i] = NULL;
}

void right_redirect(params_t *params, int i)
{
    int fd = open(params->token_list[i + 1], O_WRONLY | O_CREAT |
        O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        exit(EXIT_FAILURE);
    }
    close(fd);
    params->token_list[i] = NULL;
}

void double_right_redirect(params_t *params, int i)
{
    int fd = open(params->token_list[i + 1], O_WRONLY | O_CREAT | O_APPEND,
        S_IRUSR | S_IWUSR);

    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        exit(EXIT_FAILURE);
    }
    close(fd);
    params->token_list[i] = NULL;
}

void check_directions(params_t *params, int i)
{
    if (my_strcmp(params->token_list[i], "<") == 0) {
        left_redirect(params, i);
        return;
    }
    if (my_strcmp(params->token_list[i], ">") == 0) {
        right_redirect(params, i);
        return;
    }
    if (my_strcmp(params->token_list[i], ">>") == 0) {
        double_right_redirect(params, i);
        return;
    }
}

void redirect(params_t *params)
{
    int i = 0;

    while (params->token_list[i] != NULL) {
        check_directions(params, i);
        i++;
    }
}
