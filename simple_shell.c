#include "shell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    run_shell(env);
    return (0);
}

void run_shell(char **env)
{
    char    *line = NULL;
    size_t  n = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO)) /* display prompt only in interactive mode */
            write(1, "$ ", 2);

        if (getline(&line, &n, stdin) == -1) /* EOF or error, exit loop */
            break;

        execute(line, env);

        free(line);
        line = NULL;
    }
    free(line);
}

void execute(char *line, char **env)
{
    char    **args = NULL;
    char    *path = NULL;

    args = parse(line); /* split line into words */
    if (args == NULL || args[0] == NULL) /* empty line */
    {
        free(args);
        return;
    }
    if (is_builtin(args[0])) /* check if command is a builtin */
    {
        exec_builtin(args, env);
        free(args);
        return;
    }
    path = find_path(args[0], env); /* search command in PATH */
    if (path == NULL) /* command not found */
    {
        fprintf(stderr, "hsh: 1: %s: not found\n", args[0]);
        free(args);
        return;
    }
    fork_exec(path, args, env);
    free(path);
    free(args);
}
