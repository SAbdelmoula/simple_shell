#include "shell.h"

/**
 * BufferInput - Buffer the chained cmd
 * @information: parameter structure
 * @buffer: the address of the buffer
 * @Len: the address of the len varriable
 * Return: byte read
 */
ssize_t BufferInput(info_t *information, char **buffer, size_t *Len)
{
	ssize_t n = 0;
	size_t Len_p = 0;

	if (!*Len)
	{
		/*bfree((void **)information->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buffer, &Len_p, stdin);
#else
		n = _getline(information, buffer, &Len_p);
#endif
		if (n > 0)
		{
			if ((*buffer)[n - 1] == '\n')
			{
				(*buffer)[n - 1] = '\0';
				n--;
			}
			information->linecount_flag = 1;
			remove_comments(*buffer);
			BuildHistory_List(information, *buffer, information->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*Len = n;
				information->cmd_buffer = buffer;
			}
		}
	}
	return (n);
}

/**
 * GetInput - get the line minus of the new line
 * @information: the parameter structure
 * Return: byte read
 */
ssize_t GetInput(info_t *information)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t a, k, Len;
	ssize_t n = 0;
	char **buffer_p = &(info->arg), *position;

	_putchar(BUF_FLUSH);
	n = input_buf(information, &buffer, &Len);
	if (n == -1) /* EOF */
		return (-1);
	if (Len)	/* we have commands left in the chain buffer */
	{
		k = a; /* init new iterator to current buf position */
		position = buffer + a; /* get pointer for return */

		checkChain(information, buffer, &k, a, Len);
		while (k < Len) /* iterate to semicolon or end */
		{
			if (isChainDelimiter(information, buffer, &k))
				break;
			k++;
		}

		a = k + 1; /* increment past nulled ';'' */
		if (a >= Len) /* reached end of buffer? */
		{
			a = Len = 0; /* reset position and length */
			info->cmd_buffer_type = CMD_NORM;
		}

		*buffer_p = position;
		return (_strlen(position));
	}

	*buffer_p = buffer;
	return (n);
}

/**
 * ReadBuffer - read the buf
 * @information: the parameter sturcture
 * @buffer: buffer
 * @i: size
 * Return: n
 */
ssize_t ReadBuffer(info_t *information, char *buffer, size_t *i)
{
	ssize_t n = 0;

	if (*i)
		return (0);
	n = read(info->readfd, buffer, READ_BUF_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}

/**
 * _getline - get the next line of the input from STDIN
 * @information: the parameter structure
 * @ptr: the address of the pointer to buf, preallocated or NULL
 * @length: size of preallocated ptr buf if not NULL
 * Return: a
 */
int _getline(info_t *information, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t e;
	ssize_t n = 0, a = 0;
	char *position = NULL, *new_p = NULL, *c;

	position = *ptr;
	if (position && length)
		a = *length;
	if (i == len)
		i = len = 0;

	n = read_buf(info, buffer, &Len);
	if (n == -1 || (n == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	e = c ? 1 + (unsigned int)(c - buffer) : Len;
	new_position = _realloc(p, a, a ? a + e : e + 1);
	if (!new_position) /* MALLOC FAILURE! */
		return (position ? free(position), -1 : -1);

	if (a)
		_strncat(new_position, buffer + i, e - i);
	else
		_strncpy(new_position, buffer + i, e - i + 1);

	a += e - i;
	i = e;
	position = new_position;

	if (length)
		*length = a;
	*ptr = position;
	return (a);
}

/**
 * Siginthandler - block the ctrl-C
 * @sig_number: the signal number
 * Return: void
 */
void Siginthandler(__attribute__((unused))int sig_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}