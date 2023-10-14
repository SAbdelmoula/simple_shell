#include "shell.h"

/**
 *_Memset - charge the memory with the constant byte
 *@s: pointer the memory area
 *@buf: byte the fill *str with
 *@num: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_Memset(char *s, char buf, unsigned int num)
{
	unsigned int n;

	for (n = 0; n < num; n++)
		s[n] = buf;
	return (s);
}

/**
 * Ffree - free the string
 * @pp: string of the strings
 */
void Ffree(char **pp)
{
	char **i = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(i);
}

/**
 * RealLocate - reallocate the block of memory
 * @parameter: pointer to last malloc'ated block
 * @old_size: byte size of last block
 * @current_size: byte size of current block
 * Return: pointer to da old block nameen
 */
void *RealLocate(void *parameter, unsigned int old_size,
		unsigned int current_size)
{
	char *position;

	if (!parameter)
		return (malloc(current_size));
	if (!current_size)
		return (free(parameter), NULL);
	if (current_size == old_size)
		return (parameter);

	position = malloc(current_size);
	if (!position)
		return (NULL);

	old_size = old_size < current_size ? old_size : current_size;
	while (old_size--)
		position[old_size] = ((char *)parameter)[old_size];
	free(parameter);
	return (position);
}
