#include "shell.h"

/**
 * **strtow - makes word divisions in a string.It ignores repeated delimiters
 * @str: the text input
 * @del: string of the delimeter
 * Return: a pointer to a string array, or NULL on failure
 */

char **strtow(char *str, char *del)
{
	int n, a, z, e, countword = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], del) && (is_delim(str[n + 1], del) || !str[n + 1]))
			countword++;

	if (countword == 0)
		return (NULL);
	r = malloc((1 + countword) * sizeof(char *));
	if (!r)
		return (NULL);
	for (n = 0, a = 0; a < countword; a++)
	{
		while (is_delim(str[n], del))
			n++;
		z = 0;
		while (!is_delim(str[n + z], del) && str[n + z])
			z++;
		r[a] = malloc((z + 1) * sizeof(char));
		if (!r[a])
		{
			for (z = 0; z < a; z++)
				free(r[z]);
			free(r);
			return (NULL);
		}
		for (e = 0; e < z; e++)
			r[a][e] = str[n++];
		r[a][e] = 0;
	}
	r[a] = NULL;
	return (r);
}

/**
 * **strtow2 - separates words from a string
 * @str: string for the input
 * @del: the delimeter
 * Return: a pointer to a string array, or NULL on failure
 */
char **strtow2(char *str, char del)
{
	int n, a, z, e, countword = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != del && str[n + 1] == del) ||
		    (str[n] != del && !str[n + 1]) || str[n + 1] == del)
			countword++;
	if (countword == 0)
		return (NULL);
	r = malloc((1 + countword) * sizeof(char *));
	if (!r)
		return (NULL);
	for (n = 0, a = 0; a < countword; a++)
	{
		while (str[n] == del && str[n] != del)
			n++;
		z = 0;
		while (str[n + z] != del && str[n + z] && str[n + z] != del)
			z++;
		r[a] = malloc((z + 1) * sizeof(char));
		if (!r[a])
		{
			for (z = 0; z < a; z++)
				free(r[z]);
			free(r);
			return (NULL);
		}
		for (e = 0; e < z; e++)
			r[a][e] = str[n++];
		r[a][e] = 0;
	}
	r[a] = NULL;
	return (r);
}
