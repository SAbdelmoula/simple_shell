#include "shell.h"

/**
 * GetFile_History - obtaining the history file
 * @information: the structure parameter
 * Return: history file in the allocated string
 */

char *GetFile_History(info_t *information)
{
	char *buffer, *currentDir;

	currentDir = _getenv(information, "HOME=");
	if (!currentDir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(currentDir)
				+ _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buf[0] = 0;
	_strcpy(buffer, currentDir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * WriteHistory -make the file to an existing file
 * @information: the parameter structure
 * Return: 1 on success, else -1
 */
int WriteHistory(info_t *information)
{
	ssize_t fd;
	char *filename = GetFile_History(information);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * ReadHistory - examine history from the file
 * @information: the parameter structure
 * Return: histcount on success, 0 otherwise
 */
int ReadHistory(info_t *information)
{
	int n, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = GetFile_History(information);

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
			BuildHistory_List(info, buffer + last, linecount++);
			last = n + 1;
		}
	if (last != n)
		BuildHistory_List(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(information->history), 0);
	RenumberHistory(information);
	return (information->histcount);
}

/**
 * BuildHistory_List - add the entry to a history of the linked list
 * @information: the struct of the containing potential arguments
 * @buffer: buffer
 * @Linecount: the history linecount, histcount
 * Return: Always 0
 */
int BuildHistory_List(info_t *information, char *buffer, int Linecount)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	add_node_end(&node, buffer, Linecount);

	if (!information->history)
		information->history = node;
	return (0);
}

/**
 * RenumberHistory - renumber the history of the linked-list after changes
 * @information: struct the containing potential arguments
 * Return: new histcount
 */
int RenumberHistory(info_t *information)
{
	list_t *node = information->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (information->histcount = n);
}
