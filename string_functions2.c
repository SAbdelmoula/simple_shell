#include "shell.h"

/**
 * _strcpy - duplicates a string
 * @destination: Destination
 * @source: Source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int n = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[n])
	{
		destination[n] = source[n];
		n++;
	}
	destination[n] = 0;
	return (destination);
}

/**
 * _strdup - Double the string
 * @string: repicate the string
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int len = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--string;
	return (ret);
}

/**
 *_puts - pull the string input
 *@string: show string
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int n = 0;

	if (!string)
		return;
	while (string[n] != '\0')
	{
		_putchar(string[n]);
		n++;
	}
}

/**
 * _putchar - creates a stdout file with the character C
 * @c: fill chars
 *
 * Return: On success 1
 * On error, -1 is returned, and errno is set appropriately
 */
int _putchar(char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}
