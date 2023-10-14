#include "shell.h"

/**
 * ClearInformation - initialize info_t structure
 * @information: structure the address
 */
void ClearInformation(info_t *information)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * SetInformation - initialize info_t structure
 * @info: structure the address
 * @av: argument vector
 */
void SetInformation(info_t *information, char **av)
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
 * FreeInformation - frees info_t structure field
 * @information: the structure address
 * @all: true if freeing all field
 */
void FreeInformation(info_t *information, int all)
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
