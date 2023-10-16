#include "shell.h"

/**
 * _myenvironment - Prints the new environment variables
 * @info: Arrangement with potential arguments,used to preserve
 *              the prototype of the constant function
 *
 * Return: Always 0.
 */
int _myenvironment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenvironment - Obtains the value of a variable in the envir
 * @info: Struct containing potential arguments
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *_getenvironment(info_t *info, const char *name)
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
 * _mysetenvironment - Create a new environment variable
 *                    or edit an already existing one
 * @info: Struct containing potential arguments
 *
 * Return: 0 on success, 1 on error
 */
int _mysetenvironment(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguments\n");
		return (1);
	}

	if (_setenvironment(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenvironment - Eliminate a setting variable
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int _myunsetenvironment(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (n = 1; n < info->argc; n++)
		_unsetenvironment(info, info->argv[n]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&node, environ[n], 0);

	info->env = node;
	return (0);
}
