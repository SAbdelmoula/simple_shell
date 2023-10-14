#include "shell.h"

/**
 * _stringcopy - copy a string
 * @destination: Destination
 * @source: Source
 *
 * Return: pointer to destination
 */
char *_stringcopy(char *destination, char *source)
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
 * _stringduplicate - Duplicate the string
 * @string: string a duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_stringduplicate(const char *string)
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
 *_putstr - pull the string input
 *@string: string to  print
 *
 * Return: Nothing
 */
void _putstr(char *string)
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
 * _putchars - print the character c to stdout
 * @c: The chars to print
 *
 * Return: On success 1
 * On error, -1 is returned, and errno is set appropriately
 */
int _putchars(char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}
