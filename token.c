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

int read_and_tokenize(char *line, char **env)
{
    int code_retour = 0;
    char *command;
    int index = 0;

    command = my_strtok(line, index, ";");
    while (command != NULL) {
        code_retour = args_to_token(command, env);
        index++;
        command = my_strtok(line, index, ";");
    }
    return code_retour;
}
