#include "shell.h"

/**
 * clear_information - creates the info_t struct
 * @information: structure for the address
 */
void clear_information(info_t *information)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_information - establishes the info_t struct
 * @information: structure for the address
 * @av: argument vector
 */
void set_information(info_t *information, char **av)
{
	int n = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
			;
		info->argc = n;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * free_information - liberates info_t struct fields
 * @information: structure for the address
 * @all: if freeing all fields, then
 */
void free_information(info_t *information, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
