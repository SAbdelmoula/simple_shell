#include "shell.h"

/**
 *_memset - creates a constant byte in memory
 *@s: the memory location
 *@buf: fill *str with bytes
 *@num: bytes that must be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char buf, unsigned int num)
{
	unsigned int n;

	for (n = 0; n < num; n++)
		s[n] = buf;
	return (s);
}

/**
 * ffree - releases a group of strings
 * @pp: all of the strings
 */
void ffree(char **pp)
{
	char **i = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(i);
}

/**
 * _realloc - reassigns a memory block
 * @parameter: indicate latest malloc'd block
 * @old_size: the previous block's byte size
 * @current_size: byte size of current block
 * Return: pointer to the old block
 */
void *_realloc(void *parameter, unsigned int old_size,
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
