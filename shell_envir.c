#include "shell.h"

/**
 * printEnvironment - Prints the current environment variables
 * @info: Struct containing potential arguments
 *
 * Return: Always 0.
 */
int printEnvironment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getEnvironmentVariable - Gets the value of an environment variable
 * @info: Struct containing potential arguments
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *getEnvironmentVariable(info_t *info, const char *name)
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
 * setEnvironmentVariable - Initializes a new environment
 *                    variable or modifies an existing one
 * @info: Struct containing potential arguments
 *
 * Return: 0 on success, 1 on error
 */
int setEnvironmentVariable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * unsetEnvironmentVariable - Removes the environment variable
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int unsetEnvironmentVariable(info_t *info)
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
 * populateEnvironmentList - Populates the environment linked list
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&node, environ[n], 0);

	info->env = node;
	return (0);
}
