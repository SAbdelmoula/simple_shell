#include "shell.h"

/**
 *_eputs - displays a string of input
 * @str: the string to be shown
 * Return: Nothing
 */
void _eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_eputchar(str[n]);
		n++;
	}
}

/**
 * _eputChar - stderr is updated with the character C
 * @c: Printing the character
 * Return: On success 1
 */
int _eputChar(char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}

/**
 * _putfd - Fill in the provided fd with the char "c"
 * @c: Printing the character
 * @fd: written file descriptor
 * Return: On success 1
 */
int _putfd(char c, int fd)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}

/**
 * _putsfd - pull up the string entered
 * @str: Printing the character
 * @fd: written file descriptor
 * Return: the number of the chars entered
 */
int _putsfd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += _putfd(*str++, fd);
	}
	return (n);
}
