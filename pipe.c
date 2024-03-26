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

int process_child(int i, char **env, params_t *params)
{
    char *path;

    dup2(params->prev_fd, STDIN_FILENO);
    if (params->pipe_off[i + 1] != NULL) {
        dup2(params->fd[1], STDOUT_FILENO);
    }
    close(params->fd[0]);
    args_to_token2(params, params->pipe_off[i], env);
    path = which_path(params->token_list[0]);
    execve(path, params->token_list, env);
    exit(1);
}

void handle_fork(pid_t pid, int i, params_t *params, char **env)
{
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        process_child(i, env, params);
    } else {
        wait(NULL);
        close(params->fd[1]);
        params->prev_fd = params->fd[0];
    }
}

int execute_pipes(params_t *params, char **env)
{
    pid_t pid;

    params->prev_fd = 0;
    for (int i = 0; params->pipe_off[i] != NULL; i++) {
        pipe(params->fd);
        pid = fork();
        handle_fork(pid, i, params, env);
    }
    return 0;
}
