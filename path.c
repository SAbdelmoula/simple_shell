#include "shell.h"

/**
 * is_command - Dictate whether a file is an executable or not
 * @information: structure the information
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_command(info_t *information, char *path)
{
	struct stat st;

	(void)information;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - character duplication
 * @pathstring: path is a string
 * @start: initial index
 * @stop: halting index
 * Return: identifier of a new buffer
 */
char *dup_chars(char *pathstring, int start, int stop)
{
	static char buffer[1024];
	int a = 0, n = 0;

	for (n = 0, a = start; a < stop; a++)
		if (pathstring[a] != ':')
			buffer[n++] = pathstring[a];
	buffer[n] = 0;
	return (buffer);
}

/**
 * find_path- observe command in the path string
 * @information: structure for the information
 * @pathstring: path a string
 * @command: the cmd to use
 * Return: complete path of the cmd, if found, or NULL
 */
char *find_path(info_t *information, char *pathstring, char *command)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command(information, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[a] || pathstring[a] == ':')
		{
			path = dup_chars(pathstring, curr_pos, a);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command(information, path))
				return (path);
			if (!pathstring[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
