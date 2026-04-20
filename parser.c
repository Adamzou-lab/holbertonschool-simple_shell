#include "shell.h"
/**
 * parse - splits a string into an array of tokens
 * @line: the string to be parsed
 *
 * Description: Counts words based on spaces, tabs, and newlines,
 * then allocates a NULL-terminated array of strings using strtok.
 *
 * Return: A pointer to the array of strings, or NULL if allocation fails.
 */
char **parse(char *line)
{
	int word_count = 0, index = 0, i = 0;
	char in_word = 0;
	char *token, **tab, *str_copy;

	while (line[index] != '\0') /** Read the string */
	{
		if (line[index] != ' ' && line[index] != '\n' && line[index] != '\t')
		/** if index is not a space and \n, \t */
		{
			if (in_word == 0) /** it's a word */
			{
				word_count++; /** the word counter increases by 1 */
				in_word = 1; /** 1 = we are inside a word */
			}
		}
		else
			in_word = 0; /** 0 = we are not inside a word */
		index++; /** we move on the next char */
	}
	tab = malloc(sizeof(char *) * (word_count + 1));
	/** alloc size of memory + NULL */

	if (tab == NULL)
		return (NULL);

	tab[word_count] = NULL;

	str_copy = strdup(line); /** copy for work on */

	token = strtok(str_copy, " \n\t"); /** first word */
	while (token != NULL)
	{
		tab[i] = strdup(token); /** copy the word in case of tab */
		i++;
		token = strtok(NULL, " \n\t"); /** next word */
	}
	free(str_copy);
	return (tab);
}
/**
 * free_args - frees an array of strings
 * @args: the NULL-terminated array of strings to be freed
 *
 * Description: Iterates through the array, freeing each individual string
 * (each argument), and then frees the pointer to the array itself.
 */
void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
