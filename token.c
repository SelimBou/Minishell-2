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

static int check_command(params_t *params, int i)
{
    if (my_strcmp(params->semicolons_off[i], "|") == 0 ||
        my_strcmp(params->semicolons_off[i], " | ") == 0) {
        printf("Invalid null command.\n");
        return 1;
    }
    return 0;
}

int search_for_pipe(params_t *params, char **env)
{
    int total_pipes = count_pipes(params);
    int index = 0;
    char *pipe_command;
    int code_retour = 0;

    params->pipe_off = malloc(sizeof(char *) * (total_pipes + 1));
    for (int i = 0; params->semicolons_off[i] != NULL; i ++) {
        code_retour = check_command(params, i);
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
    return code_retour;
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

static void replace_newline_with_null(char *string)
{
    for (int i = 0; string[i]; i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
        }
    }
}

int read_and_tokenize(char *line, char **env)
{
    params_t params;
    int code_retour = 0;
    char *command;
    int index = 0;
    int num_of_semicolons = count_semicolons(line);

    params.semicolons_off = malloc(sizeof(char *) * (num_of_semicolons + 1));
    command = my_strtok(my_strdup(line), index, ";");
    while (command != NULL) {
        replace_newline_with_null(command);
        params.semicolons_off[index] = my_strdup(command);
        if (my_strrchr(command, '|') != NULL) {
            return search_for_pipe(&params, env);
        } else
            code_retour = args_to_token(command, env);
        index++;
        command = my_strtok(line, index, ";");
    }
    params.semicolons_off[index] = NULL;
    return code_retour;
}
