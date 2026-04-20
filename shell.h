#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /** getline */
#include <unistd.h> /** write, isaty, STDIN_FILENO, execve */
#include <stdlib.h> /** free, exit */
#include <sys/types.h> /** pid_t */
#include <sys/wait.h> /** wait */
#include <string.h> /** strcmp, strtok */

/* simple_shell.c */
int main(int ac, char **av, char **env);
int run_shell(char *prog_name, char **env);
int execute(char *line, char *prog_name, char **env, int count);

/** parser.c */
char **parse(char *line);
void free_args(char **args);

/** builtins.c */
int is_builtin(char *cmd);
void exec_builtin(char **args, char **env, char *line);
void builtin_exit(char **args, char **env, char *line);
void builtin_env(char **args, char **env);

/* executor.c */
void fork_exec(char *path, char **args, char **env);

/* path.c */
char *_getenv(const char *name, char **env);
char *copy_str(char *str);
char *build_path(char *dir, char *cmd);
char *find_path(char *cmd, char **env);

#endif
