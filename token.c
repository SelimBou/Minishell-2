/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** token.c
*/

#include "shell_two.h"

int other_commands(params_t *params, char **env)
{
    pid_t pid;
    char *path = params->token_list[0];
    struct stat path_stat;

    check_if_dir(path, &path_stat);
    if (params->token_list[0][0] != '.' && params->token_list[0][0] != '/')
        path = which_path(params->token_list[0]);
    else
        path = params->token_list[0];
    if (exe_command2(params, env) == 0)
        return 0;
    else {
        pid = fork();
        if (pid == 0)
            redirect(params);
        return exe_command(pid, params, env, path);
    }
}

static int if_pipe_true(params_t *params, int i, int j, int *count_of_pipes)
{
    if (params->semicolons_off[i][j] == '|') {
        (*count_of_pipes)++;
    }
    return 0;
}

int count_pipes(params_t *params)
{
    int count_of_pipes = 0;

    for (int i = 0; params->semicolons_off[i] != NULL; i ++) {
        for (int j = 0; params->semicolons_off[i][j] != '\0'; j ++) {
            if_pipe_true(params, i, j, &count_of_pipes);
        }
    }
    return count_of_pipes;
}

int search_for_pipe(params_t *params, char **env)
{
    int total_pipes = count_pipes(params);
    int index = 0;
    char *pipe_command;
    int code_retour = 0;

    params->pipe_off = malloc(sizeof(char *) * (total_pipes + 1));
    for (int i = 0; params->semicolons_off[i] != NULL; i ++) {
        pipe_command = strtok(my_strdup(params->semicolons_off[i]), "|");
        while (pipe_command != NULL) {
            params->pipe_off[index] = my_strdup(pipe_command);
            index ++;
            pipe_command = strtok(NULL, "|");
        }
        free(pipe_command);
    }
    params->pipe_off[index] = NULL;
    execute_pipes(params, env);
}

int count_semicolons(char *line)
{
    int semicolons = 0;

    for (int i = 0; line[i] != '\0'; i ++) {
        if (line[i] == ';') {
            semicolons ++;
        }
    }
    return semicolons;
}

int read_and_tokenize(char *line, char **env)
{
    params_t params;
    int code_retour = 0;
    char *command;
    int index = 0;
    int num_of_semicolons = count_semicolons(line);

    params.semicolons_off = malloc(sizeof(char *) * num_of_semicolons);
    command = my_strtok(line, index, ";");
    while (command != NULL) {
        if (my_strrchr(line, '|') == NULL)
            code_retour = args_to_token(command, env);
        params.semicolons_off[index] = my_strdup(command);
        index++;
        command = my_strtok(line, index, ";");
    }
    for (int i = 0; i < index; i ++) {
        if (my_strrchr(params.semicolons_off[i], '|') != NULL)
            search_for_pipe(&params, env);
    }
    return code_retour;
}
