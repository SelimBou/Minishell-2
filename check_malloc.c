/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** check_malloc.c
*/

#include "shell_two.h"

int check_args_cd(params_t *params)
{
    if (params->number_token > 2) {
        my_printf("cd: Too many arguments.\n");
        return 1;
    }
    return 0;
}

int last_case_cd(params_t *params)
{
    if (params->number_token == 2 &&
        my_strcmp(params->token_list[1], "~") != 0 &&
        my_strcmp(params->token_list[1], "-") != 0) {
        if (change_dir(params->token_list[1]) != 0) {
            my_printf("%s: Not a directory.\n",
                params->token_list[1]);
            return 1;
        }
        return 0;
    }
}

int check_if_dir(char *path, struct stat *path_stat)
{
    stat(path, path_stat);
    if (S_ISDIR(path_stat->st_mode)) {
        my_printf("%s: Permission denied.\n", path);
        exit(1);
    }
}

int is_malloc_correct(params_t *params)
{
    if (params->token_list == NULL)
        return -1;
}

int exe_command2(params_t *params, char **env)
{
    int status = 0;
    char **segf = malloc(sizeof(char *) * 10);
    pid_t pid = fork();

    if (pid == 0) {
        segf[0] = malloc(sizeof(char) * my_strlen(params->token_list[0]) + 2);
        my_strcat(segf[0], "./");
        my_strcat(segf[0], params->token_list[0]);
        if (execve(segf[0], segf, env) == -1) {
            exit(1);
        }
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            my_printf("Segmentation fault\n");
            return 0;
        }
    }
}
