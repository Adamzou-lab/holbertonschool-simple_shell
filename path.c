#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: variable name
 * @env: environment variables array
 *
 * Description: iterates through env and looks for name followed
 * by '=' to return its value
 *
 * Return: pointer to the value, or NULL if not found
 */
char *_getenv(const char *name, char **env)
{
	int i = 0;
	int len = strlen(name);

	while (env[i]) /* go through each env variable */
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1); /* return value after '=' */
		i++;
	}
	return (NULL);
}

/**
 * copy_str - duplicates a string using malloc and strcpy
 * @str: the string to copy
 *
 * Description: allocates memory and copies str into it
 *
 * Return: allocated copy of str or NULL if malloc fails
 */
char *copy_str(char *str)
{
	char *copy;

	copy = malloc(strlen(str) + 1); /* allocate space for copy */
	if (!copy)
		return (NULL);
	strcpy(copy, str);
	return (copy);
}

/**
 * build_path - builds a full path from directory and command
 * @dir: directory
 * @cmd: command name
 *
 * Description: allocates exactly the right size and concatenates
 * dir, '/' and cmd into a new string
 *
 * Return: allocated full path, or NULL if malloc fails
 */
char *build_path(char *dir, char *cmd)
{
	char *full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2); /* dir + / + cmd + \0 */
	if (!full_path)
		return (NULL);
	strcpy(full_path, cmd); /* copy command */
	strcat(full_path, "/"); /* add separator */
	strcat(full_path, dir); /* add directory */
	return (full_path);
}

/**
 * find_path - finds the full path of a command
 * @cmd: the command to find
 * @env: environment variables array
 *
 * Description: if cmd contains '/', tests it directly, otherwise
 * retrieves PATH from env and checks each directory for the command
 *
 * Return: allocated full path (caller must free), or NULL if not found
 */
char *find_path(char *cmd, char **env)
{
	char *path, *dir, *full_path;
	int i = 0;

	while (cmd[i] && cmd[i] != '/') /* move forward until '/' or end of string */
		i++;
	if (cmd[i] == '/') /* direct path given */
	{
		if (access(cmd, X_OK) == 0) /* check if cmd is executable */
			return (copy_str(cmd));
		return (NULL);
	}
	dir = _getenv("PATH", env); /* get PATH value from environment */
	if (!dir)
		return (NULL);
	path = copy_str(dir); /* copy PATH before strtok modifies it */
	if (!path)
		return (NULL);
	dir = strtok(path, ":"); /* first directory */
	while (dir)
	{
		full_path = build_path(dir, cmd); /* build full path */
		if (!full_path)
		{
			free(path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0) /* check if executable */
		{
			free(path);
			return (full_path);
		}
		free(full_path); /* not found, try next directory */
		dir = strtok(NULL, ":"); /* next directory */
	}
	free(path);
	return (NULL);
}
