#include "shell.h"

/**
 * _myenv - Prints the new environment variables
 * @info: Arrangement with potential arguments,used to preserve
 *              the prototype of the constant function
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Obtains the value of a variable in the envir
 * @info: Struct containing potential arguments
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *i;

	while (node)
	{
		i = starts_with(node->str, name);
		if (i && *i)
			return (i);
		node = node->next;
	}

	return (NULL);
}

/**
 * _mysetenv - Create a new environment variable
 *                    or edit an already existing one
 * @info: Struct containing potential arguments
 *
 * Return: 0 on success, 1 on error
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenv - Eliminate a setting variable
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (n = 1; n < info->argc; n++)
		_unsetenv(info, info->argv[n]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&node, environ[n], 0);

	info->env = node;
	return (0);
}
