/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-selim.bouasker
** File description:
** token.c
*/

#include "shell_two.h"

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
