#include "shell.h"
/**
 * main - entry point for the simple shell program
 * @ac: argument count (unused)
 * @av: argument vector, av[0] is used as the program name
 * @env: environment variables array
 *
 * Description: Immediately calls the shell's main execution loop,
 * passing argv[0] as the program name and the environment variables.
 *
 * Return: exit status of the last command executed.
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	return (run_shell(av[0], env));
}
/**
 * run_shell - runs the main loop of the shell
 * @prog_name: name of the program (argv[0])
 * @env: the environment variables array
 *
 * Description: Reads input from the user in a loop, displays a prompt if
 * in interactive mode, and passes the input to the execution function.
 * Handles End-Of-File (EOF) and frees memory appropriately.
 *
 * Return: exit status of the last command executed.
 */
int run_shell(char *prog_name, char **env)
{
	char *line = NULL;
	size_t n = 0;
	int count = 1;
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO)) /* display prompt only in interactive mode */
			write(1, "$ ", 2);

		if (getline(&line, &n, stdin) == -1) /* EOF or error, exit loop */
			break;

		last_status = execute(line, prog_name, env, count);
		count++;
		free(line);
		line = NULL;
	}
	free(line);
	return (last_status);
}
/**
 * execute - handles the execution logic of a command
 * @line: the raw input string from the user
 * @prog_name: name of the program (argv[0])
 * @env: the environment variables array
 * @count: number of commands executed since the shell started
 *
 * Description: Parses the input line into arguments, checks for built-in
 * commands, searches the system PATH for the executable, and forks a
 * new process to run the command if found.
 *
 * Return: exit status of the command (0 on success, 127 if not found).
 */
int execute(char *line, char *prog_name, char **env, int count)
{
	char **args = NULL;
	char *path = NULL;

	args = parse(line); /* split line into words */
	if (args == NULL || args[0] == NULL) /* empty line */
	{
		free_args(args);
		return (0);
	}
	if (is_builtin(args[0])) /* check if command is a builtin */
	{
		exec_builtin(args, env, line);
		free_args(args);
		return (0);
	}
	path = find_path(args[0], env); /* search command in PATH */
	if (path == NULL) /* command not found */
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, count, args[0]);
		free_args(args);
		return (127);
	}
	fork_exec(path, args, env);
	free(path);
	free_args(args);
	return (0);
}
