#include "shell.h"

/**
 * get_history_file - obtaining the history file
 * @info: structure for the  parameter
 * Return: history file in the allocated string
 */

char *get_history_file(info_t *info)
{
	char *buffer, *currentDir;

	currentDir = _getenv(info, "HOME=");
	if (!currentDir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(currentDir)
				+ _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, currentDir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history -make the file to an existing file
 * @info: structure for the parameter
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - uses a file to read history
 * @info: structure for the parameter
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int n, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (n = 0; n < fsize; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			build_history_list(info, buffer + last, linecount++);
			last = n + 1;
		}
	if (last != n)
		build_history_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - creates a new entry in a history-linked list
 * @info: the structure of the possible arguments
 * @buffer: buffer
 * @linecount: history linecount and history count
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - updates the history linked list after changes
 * @info: Building with possible arguments
 * Return: courrent histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}
