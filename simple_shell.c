#include "shell.h"
/**
 * main - entry point for the simple shell program
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @env: environment variables array
 *
 * Description: This function ignores the standard ac and av parameters
 * and immediately calls the shell's main execution loop, passing
 * the system environment variables.
 *
 * Return: Always 0 (Success).
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	return (run_shell(av[0], env));
}
/**
 * run_shell - runs the main loop of the shell
 * @env: the environment variables array
 *
 * Description: Reads input from the user in a loop, displays a prompt if
 * in interactive mode, and passes the input to the execution function.
 * Handles End-Of-File (EOF) and frees memory appropriately.
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

		last_status = execute(line, prog_name, env, count, last_status);
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
 * @env: the environment variables array
 * @count: number of commands executed since the shell started
 * @last_status: exit status of the last executed command
 *
 * Description: Parses the input line into arguments, checks for built-in
 * commands, searches the system PATH for the executable, and forks a
 * new process to run the command if found.
 *
 * Return: exit status of the command (0 on success, 127 if not found)
 */
int execute(char *line, char *prog_name, char **env, int count, int last_status)
{
	char **args = NULL;
	char *path = NULL;

	args = parse(line); /* split line into words */
	if (args == NULL || args[0] == NULL) /* empty line */
	{
		free_args(args);
		return (last_status);
	}
	if (is_builtin(args[0])) /* check if command is a builtin (exit or cd) */
	{
		exec_builtin(args, env, last_status);
		free_args(args);
		return (last_status);
	}
	path = find_path(args[0], env); /* search command in PATH */
	if (path == NULL) /* command not found */
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, args[0]);
		free_args(args);
		return (127);
	}
	fork_exec(path, args, env);
	free(path);
	free_args(args);
	return (0);
}
