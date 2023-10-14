#include "shell.h"

/**
 * IsShellcommand - Dictate whether a file is an executable or not
 * @information: structure the information
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int IsShellcommand(info_t *information, char *path)
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
 * DuplicateShellchars - the duplicate chars
 * @pathstring: the path string
 * @start: starting the index
 * @stop: stopping the index
 * Return: pointer to the new buf
 */
char *DuplicateShellchars(char *pathstring, int start, int stop)
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
 * FindStrpath- observe this command in the path of string
 * @information: structure information
 * @pathstring: the path string
 * @command: the cmd to observe
 * Return: full path of command if found or NULL
 */
char *FindStrpath(info_t *information, char *pathstring, char *command)
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
