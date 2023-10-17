#include "shell.h"

/**
 * *strtow - makes word divisions in a string,
 *             It ignores repeated delimiters
 * @str: string all the input
 * @delimeter: string for delimeter
 * Return: print an array of string, or NULL on failure
 */

char *strtow(char *str, char *delimeter)
{
	int n, a, z, e, wordsnumber = 0;
	char *r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], delimeter) &&
			    (is_delim(str[n + 1], delimeter) || !str[n + 1]))
			wordsnumber++;

	if (wordsnumber == 0)
		return (NULL);
	r = malloc((1 + wordsnumber) * sizeof(char *));
	if (!r)
		return (NULL);
	for (n = 0, a = 0; a < wordsnumber; a++)
	{
		while (is_delim(str[n], delimeter))
			n++;
		z = 0;
		while (!is_delim(str[n + z], delimeter) && str[n + z])
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
 * *strtow2 - separates words from a string
 * @str: the string input
 * @delimeter: the delimeter
 * Return: pointer an array of string, or NULL on failure
 */
char *strtow2(char *str, char delimeter)
{
	int n, a, z, e, wordsnumber = 0;
	char *r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != delimeter && str[n + 1] == delimeter) ||
		    (str[n] != delimeter && !str[n + 1]) || str[n + 1] == delimeter)
			wordsnumber++;
	if (wordsnumber == 0)
		return (NULL);
	r = malloc((1 + wordsnumber) * sizeof(char *));
	if (!r)
		return (NULL);
	for (n = 0, a = 0; a < wordsnumber; a++)
	{
		while (str[n] == delimeter && str[n] != delimeter)
			n++;
		z = 0;
		while (str[n + z] != delimeter && str[n + z] &&
			      str[n + z] != delimeter)
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
