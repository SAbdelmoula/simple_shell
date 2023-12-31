#include "shell.h"

/**
 * input_buf - chained operations using buffers
 * @info: structure for the parameter
 * @buffer: buffer's address
 * @Len: the location of the available len
 * Return: read's byte
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *Len)
{
	ssize_t n = 0;
	size_t Len_p = 0;

	if (!*Len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buffer, &Len_p, stdin);
#else
		n = _getline(info, buffer, &Len_p);
#endif
		if (n > 0)
		{
			if ((*buffer)[n - 1] == '\n')
			{
				(*buffer)[n - 1] = '\0';
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*Len = n;
				info->cmd_buf = buffer;
			}
		}
	}
	return (n);
}

/**
 * get_input - obtains a queue without the courrent line
 * @info: structure for the parameter
 * Return: read byte
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' cmd buffer chain */
	static size_t a, k, Len;
	ssize_t n = 0;
	char **buffer_p = &(info->arg), *position;

	_putchar(BUF_FLUSH);
	n = input_buf(info, &buffer, &Len);
	if (n == -1)
		return (-1);
	if (Len)	/* There are still commands in the chain buffer */
	{
		k = a; /* start a new iterator at the current point of the buf */
		position = buffer + a; /* obtain the return pointer */

		check_chain(info, buffer, &k, a, Len);
		while (k < Len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &k))
				break;
			k++;
		}

		a = k + 1; /* increment past nulled ';'' */
		if (a >= Len) /* reached end of buffer? */
		{
			a = Len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = position;
		return (_strlen(position));
	}

	*buffer_p = buffer;
	return (n);
}

/**
 * read_buf - the buffer to be read
 * @info: sturcture for the parameter
 * @buffer: buffer
 * @i: size
 * Return: n
 */
ssize_t read_buf(info_t *info, char *buffer, size_t *i)
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
 * _getline - obtains the following line of input from STDIN
 * @info: structure for the parameter
 * @ptr: address of a buffer pointer that is preallocated or NULL
 * @length:if not NULL, size of preallocat pointer buffer
 * Return: a
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t e;
	ssize_t n = 0, a = 0;
	char *position = NULL, *new_p = NULL, *c;

	position = *ptr;
	if (position && length)
		a = *length;
	if (m == len)
		m = len = 0;

	n = read_buf(info, buf, &len);
	if (n == -1 || (n == 0 && len == 0))
		return (-1);

	c = _strchr(buf + n, '\n');
	e = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(position, a, a ? a + e : e + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (position ? free(position), -1 : -1);

	if (a)
		_strncat(new_p, buf + m, e - m);
	else
		_strncpy(new_p, buf + m, e - m + 1);

	a += e - m;
	m = e;
	position = new_p;

	if (length)
		*length = a;
	*ptr = position;
	return (a);
}

/**
 * sigintHandler - ctrl-C blocks
 * @sig_number: the signal digit
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
