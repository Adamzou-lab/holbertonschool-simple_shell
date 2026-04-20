#include "shell.h"
/**
 * is_builtin - checks if a command is a shell built-in
 * @cmd: the command string to check
 *
 * Description: Compares the input command against a list of
 * internally supported commands like "exit" and "env".
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(char *cmd)
{
	if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

/**
 * builtin_env - prints the current environment variables
 * @args: the array of arguments (unused)
 * @env: the array of environment variables
 *
 * Description: Iterates through the env array and prints each
 * environment variable followed by a new line.
 */
void builtin_env(char **args, char **env)
{
	unsigned int i;

	(void)args;
	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);
}

/**
 * builtin_exit - exits the shell
 * @args: the array of arguments (unused for now)
 * @env: the environment variables array (unused)
 *
 * Description: Terminates the shell process immediately with a
 * success status (0).
 */
void builtin_exit(char **args, char **env, int last_status)
{
	(void)env;
	free_args(args);
	exit(last_status);
}

/**
 * exec_builtin - identifies and executes the correct built-in command
 * @args: the array of command arguments
 * @env: the array of environment variables
 *
 * Description: Compares the first argument to known built-in strings
 * and calls the corresponding function to handle the command.
 */
void exec_builtin(char **args, char **env, int last_status)
{
	if (strcmp(args[0], "exit") == 0)
		builtin_exit(args, env, last_status);

	if (strcmp(args[0], "env") == 0)
		builtin_env(args, env);
}
