#include "shell.h"

/**
 *_eputsInput - print the string input
 * @structure: print the string
 * Return: Nothing
 */
void _eputsInput(char *structure)
{
	int n = 0;

	if (!structure)
		return;
	while (structure[n] != '\0')
	{
		_eputchar(structure[n]);
		n++;
	}
}

/**
 * _eputChars - write the character c to the stderr
 * @c: print the character
 * Return: On success 1
 */
int _eputChars(char c)
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
 * @c: print the char
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
 * @structure: print the string
 * @fd: written file descriptor
 * Return: the number of the chars entered
 */
int _putsfd(char *structure, int fd)
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
