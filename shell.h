#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /** getline */
#include <unistd.h> /** write, isaty, STDIN_FILENO, execve */
#include <stdlib.h> /** free, exit */
#include <sys/types.h> /** pid_t */
#include <sys/wait.h> /** wait */
#include <string.h> /** strcmp, strtok */
#include <stddef.h>

/** parser.c */
char **parse(char *line);

/** builtins.c */
int is_builtin(char *cmd);
void exec_builtin(char **args, char **env);
void builtin_exit(char **args, char **env);
void builtin_env(char **args, char **env);

#endif
