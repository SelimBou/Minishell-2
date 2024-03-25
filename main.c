/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** main.c
*/

#include "shell_two.h"

static int which_command(params_t *params, char **env)
{
    if (my_strcmp(params->token_list[0], "cd") == 0)
        return cd_command(params);
    if (my_strcmp(params->token_list[0], "setenv") == 0)
        return setenv_cmd(params, env);
    if (my_strcmp(params->token_list[0], "unsetenv") == 0)
        return unsetenv_cmd(params, env);
    if (my_strcmp(params->token_list[0], "env") == 0)
        env_command(env);
    if (my_strcmp(params->token_list[0], "exit") == 0) {
        my_printf("exit\n");
        exit(EXIT_SUCCESS);
    }
    return 0;
}

int exe_command(pid_t pid, params_t *params, char **env, char *path)
{
    int status = 0;
    int code_retour = 0;

    if (pid == 0) {
        if (execve(path, params->token_list, env) == -1)
            my_printf("%s: Command not found.\n", params->token_list[0]);
            exit(1);
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return 0;
        }
    }
}

static int check_built_in(params_t *params)
{
    if (my_strcmp(params->token_list[0], "cd") == 0 ||
        my_strcmp(params->token_list[0], "setenv") == 0 ||
        my_strcmp(params->token_list[0], "unsetenv") == 0 ||
        my_strcmp(params->token_list[0], "env") == 0 ||
        my_strcmp(params->token_list[0], "exit") == 0) {
            return 0;
    }
}

char *my_getenv(const char *name)
{
    extern char **environ;
    size_t name_len = my_strlen(name);

    for (int i = 0; environ[i] != NULL; i++) {
        if (my_strncmp(environ[i], name, name_len) == 0 &&
            environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;
        }
    }
    return NULL;
}

char *which_path(char *command)
{
    char *path = my_getenv("PATH");
    char *path_tok = strtok(my_strdup(path), " \t\n:");
    char *all_path;
    char *result;

    while (path_tok != NULL) {
        all_path = malloc(sizeof(char) * (my_strlen(path_tok) +
            my_strlen(command) + 2));
        my_strcpy(all_path, path_tok);
        my_strcat(all_path, "/");
        my_strcat(all_path, command);
        if (access(all_path, X_OK) == 0) {
            result = my_strdup(all_path);
            break;
        }
        path_tok = strtok(NULL, " \t\n:");
    }
    return result;
}

static int verify_command(params_t *params, char **env)
{
    if (check_built_in(params) == 0) {
        return which_command(params, env);
    } else {
        return other_commands(params, env);
    }
}

static int num_of_tok(char *line)
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

int args_to_token(char *line, char **env)
{
    params_t params;
    int i = 0;
    size_t len = my_strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    params.number_token = num_of_tok(line);
    if (params.number_token == 0)
        return 0;
    params.token_list = malloc(sizeof(char *) * params.number_token);
    is_malloc_correct(&params);
    params.copy = my_strdup(line);
    params.token = strtok(params.copy, " \t\n");
    while (params.token != NULL) {
        params.token_list[i] = my_strdup(params.token);
        params.token = strtok(NULL, " \t\n");
        i ++;
    }
    params.token_list[i] = NULL;
    return verify_command(&params, env);
}

static int start_shell(char **env)
{
    char *line = NULL;
    char current_dir[BUF_SIZE];
    size_t len = 0;
    ssize_t read = 0;
    int code_retour = 0;

    while (1) {
        if (isatty(0) == 1) {
            getcwd(current_dir, sizeof(current_dir));
            my_printf("[$>%s]", current_dir);
        }
        read = getline(&line, &len, stdin);
        if (read == -1)
            return code_retour;
        if (my_strrchr(line, ';') != NULL || my_strrchr(line, '|') != NULL) {
            code_retour = read_and_tokenize(line, env);
        } else
            code_retour = args_to_token(line, env);
    }
    return code_retour;
}

int main(int argc, char **argv, char **env)
{
    if (argc != 1) {
        write(2, "Error in num of args\n", 22);
        return 84;
    } else {
        return start_shell(env);
    }
    return 0;
}
