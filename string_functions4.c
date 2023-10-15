#include "shell.h"

/**
 * stringwords - makes word divisions in a string,
 *             It ignores repeated delimiters
 * @string: string input
 * @delimeter: string delimeter
 * Return: pointer an array of string, or NULL on failure
 */

char *stringwords(char *string, char *delimeter)
{
	int n, a, z, e, wordsnumber = 0;
	char *r;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (n = 0; string[n] != '\0'; n++)
		if (!isChainDelimiter(string[n], delimeter) &&
			    (isChainDelimiter(string[n + 1], delimeter) || !string[n + 1]))
			wordsnumber++;

	if (wordsnumber == 0)
		return (NULL);
	r = malloc((1 + wordsnumber) * sizeof(char *));
	if (!r)
		return (NULL);
	for (n = 0, a = 0; a < wordsnumber; a++)
	{
		while (isChainDelimiter(string[n], delimeter))
			n++;
		z = 0;
		while (!isChainDelimiter(string[n + z], delimeter) && string[n + z])
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
			r[a][e] = string[n++];
		r[a][e] = 0;
	}
	r[a] = NULL;
	return (r);
}

/**
 * string2w - separates words from a string
 * @string: the string input
 * @delimeter: the delimeter
 * Return: pointer an array of string, or NULL on failure
 */
char *string2w(char *string, char delimeter)
{
	int n, a, z, e, wordsnumber = 0;
	char *r;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (n = 0; string[n] != '\0'; n++)
		if ((string[n] != delimeter && string[n + 1] == delimeter) ||
		    (string[n] != delimeter && !string[n + 1]) || string[n + 1] == delimeter)
			wordsnumber++;
	if (wordsnumber == 0)
		return (NULL);
	r = malloc((1 + wordsnumber) * sizeof(char *));
	if (!r)
		return (NULL);
	for (n = 0, a = 0; a < wordsnumber; a++)
	{
		while (string[n] == delimeter && string[n] != delimeter)
			n++;
		z = 0;
		while (string[n + z] != delimeter && string[n + z] &&
			      string[n + z] != delimeter)
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
			r[a][e] = string[n++];
		r[a][e] = 0;
	}
	r[a] = NULL;
	return (r);
}
