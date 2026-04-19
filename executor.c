#include "shell.h"
/**
 * fork_exec - creates a child process and executes a command
 * @path: full path of the command to execute
 * @args: array of arguments for the command
 * @env: environment variables
 *
 * Return: void
 */
void fork_exec(char *path, char **args, char **env)
{
	pid_t pid;
	
	pid = fork(); /* create child process */
	if (pid == -1)/* check if fork failed */
	{
		perror("fork");
		return;
	}

	if (pid == 0) /* child process */
	{
		execve(path, args, env);
		perror("execve"); /* only reached if execve failed */
		exit(1);
	}
	else
		wait(NULL); /* parent waits for child to finish */
}
