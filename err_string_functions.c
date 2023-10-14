#include "shell.h"

/**
 *_putsInput - print the string input
 * @structure: print the string
 * Return: Nothing
 */
void _putsInput(char *structure)
{
	int n = 0;

	if (!structure)
		return;
	while (structure[n] != '\0')
	{
		Eputchar(structure[n]);
		n++;
	}
}

/**
 * EputChar - write the character c to the stderr
 * @c: print the character
 * Return: On success 1
 */
int EputChar(char c)
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
 * Putfd - write the character c to the given fd
 * @c: print the char
 * @fd: file descriptor to write to
 * Return: On success 1
 */
int Putfd(char c, int fd)
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
 * Putsfd - print the input string
 * @structure: print the string
 * @fd: the file descriptor to write to
 * Return: the number of the chars put
 */
int Putsfd(char *structure, int fd)
{
	int n = 0;

	if (!structure)
		return (0);
	while (*structure)
	{
		n += Put_fd(*structure++, fd);
	}
	return (n);
}
