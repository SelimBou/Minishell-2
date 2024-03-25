/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** pipe.c
*/

#include "shell_two.h"

static int num_of_tok2(char *line)
{
    int number_token = 0;
    char *copy = my_strdup(line);
    char *token = strtok(copy, " \t\n");

    while (token != NULL) {
        number_token++;
        token = strtok(NULL, " \t\n");
    }
    return number_token;
}

int args_to_token2(params_t *params, char *line, char **env)
{
    int i = 0;
    size_t len = my_strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    params->number_token = num_of_tok2(line);
    if (params->number_token == 0)
        return 0;
    params->token_list = malloc(sizeof(char *) * params->number_token);
    is_malloc_correct(params);
    params->copy = my_strdup(line);
    params->token = strtok(params->copy, " \t\n");
    while (params->token != NULL) {
        params->token_list[i] = my_strdup(params->token);
        params->token = strtok(NULL, " \t\n");
        i ++;
    }
    params->token_list[i] = NULL;
    return 0;
}

void child_process(params_t *params, char **env, int i, int *fd)
{
    char *path;

    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    args_to_token2(params, params->pipe_off[i], env);
    path = which_path(params->token_list[i]);
    execve(path, params->token_list, env);
    exit(0);
}

void parent_process(params_t *params, char **env, int i, int *fd)
{
    char *path;

    if (fork() == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        args_to_token2(params, params->pipe_off[i + 1], env);
        path = which_path(params->token_list[i]);
        printf("path: %s\n", path);
        execve(path, params->token_list, env);
        exit(0);
    } else {
        close(fd[1]);
        close(fd[0]);
        wait(0);
        wait(0);
    }
}

int execute_pipes(params_t *params, char **env)
{
    int fd[2];

    for (int i = 0; params->pipe_off[i] != NULL; i++) {
        pipe(fd);
        if (fork() == 0) {
            child_process(params, env, i, fd);
        } else {
            parent_process(params, env, i, fd);
        }
    }
    return 0;
}
