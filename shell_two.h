/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell1-selim.bouasker
** File description:
** shell_one.h
*/

#ifndef SHELL_TWO
    #define SHELL_TWO
    #define BUF_SIZE 1024
    #include <stdbool.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>
typedef struct params {
    char **token_list;
    int number_token;
    char *new_value;
    char *copy;
    char *token;
} params_t;
int check_args_cd(params_t *params);
int last_case_cd(params_t *params);
int change_dir(char *dir);
int check_if_dir(char *path, struct stat *path_stat);
int exe_command2(params_t *params, char **env);
char *my_getenv(const char *name);
int check_return(params_t *params);
int is_malloc_correct(params_t *params);
int is_alpha(char c);
int alpha_num(const char *str);
int setenv_cmd(params_t *params, char **env);
int unsetenv_cmd(params_t *params, char **env);
int cd_command(params_t *params);
void env_command(char **env);
char my_putchar(char c);
int my_printf(const char *format, ...);
int my_putstr(char *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char *src);
int my_strcmp(const char *str1, const char *str2);
char *my_strdup(char *str);
int my_str_isalpha(const char *str);
char *my_strcpy(char *dest, char *src);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strcat(char *dest, char *src);
#endif
