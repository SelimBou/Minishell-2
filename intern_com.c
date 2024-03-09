/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** intern_com.c
*/

#include "shell_two.h"

int change_dir(char *dir)
{
    if (chdir(dir) != 0)
        return 1;
    return 0;
}

int cd_command(params_t *params)
{
    char *current_dir = getcwd(NULL, 0);
    char *old_dir = my_getenv("OLDPWD");

    if (check_args_cd(params) == 1)
        return 1;
    if (params->number_token == 2 &&
        my_strcmp(params->token_list[1], "-") == 0) {
        if (change_dir(old_dir) != 0)
            return 1;
        return 0;
    }
    if (params->number_token == 1 || (params->number_token == 2 &&
        my_strcmp(params->token_list[1], "--") == 0)) {
        if (change_dir("/") != 0)
            return 1;
        return 0;
    }
    last_case_cd(params);
    return 0;
}

void env_command(char **env)
{
    for (int i = 0; env[i] != NULL; i ++) {
        my_printf("%s\n", env[i]);
    }
}

static int check_args_unsetenv(params_t *params)
{
    if (params->number_token < 2)
        return 1;
    return 0;
}

static void re_order_env(char **env, int i)
{
    int j = i;

    while (env[j] != NULL) {
        env[j] = env[j + 1];
        j ++;
    }
    env[j] = NULL;
}

int unsetenv_cmd(params_t *params, char **env)
{
    char *name = NULL;
    char *temp = NULL;

    if (check_args_unsetenv(params) == 1) {
        my_printf("unsetenv: Too few arguments\n");
        return 1;
    }
    for (int i = 0; env[i] != NULL; i++) {
        temp = my_strdup(env[i]);
        name = strtok(temp, "=");
        if (name != NULL && my_strcmp(name, params->token_list[1]) == 0) {
            re_order_env(env, i);
            return 0;
        }
        free(temp);
    }
    return 0;
}

static int check_malloc(params_t *params)
{
    if (params->new_value == NULL)
        return 1;
}

static int check_args_setenv(params_t *params)
{
    if (params->number_token > 3) {
        my_printf("setenv: Too many arguments.\n");
        return 1;
    }
    if (params->number_token > 1 && is_alpha(params->token_list[1][0]) == 1) {
        my_printf("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (params->number_token > 1 && alpha_num(params->token_list[1]) == 1) {
        my_printf("setenv: Variable name must contain alphanumeric ");
        my_printf("characters.\n");
        return 1;
    }
    return 0;
}

static void verif(params_t *params)
{
    if (params->number_token == 2) {
        params->new_value = malloc(my_strlen(params->token_list[1]) + 2);
        check_malloc(params);
        my_strcpy(params->new_value, params->token_list[1]);
        my_strcat(params->new_value, "=");
        my_strcat(params->new_value, "\0");
    } else {
        params->new_value = malloc(my_strlen(params->token_list[1])
        + my_strlen(params->token_list[2]) + 2);
        check_malloc(params);
        my_strcpy(params->new_value, params->token_list[1]);
        my_strcat(params->new_value, "=");
        my_strcat(params->new_value, params->token_list[2]);
    }
}

int setenv_cmd(params_t *params, char **env)
{
    int n = 0;

    if (check_args_setenv(params) == 1)
        return 1;
    if (params->number_token == 1) {
        env_command(env);
        return 0;
    }
    verif(params);
    for (int i = 0; env[i] != NULL; i ++) {
        if (my_strncmp(env[i], params->token_list[1],
            my_strlen(params->token_list[1])) == 0) {
            env[i] = params->new_value;
            return 0;
        }
        n ++;
    }
    env[n] = params->new_value;
    env[n + 1] = NULL;
    return 0;
}
