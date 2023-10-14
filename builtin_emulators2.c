#include "shell.h"

/**
 * displayHistory - Display the command history list with line number
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int displayHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - Unsets an alias
 * @info: Parameter structure
 * @aliasString: The alias string to unset
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(info_t *info, char *aliasString)
{
	char *equals, tempChar;
	int ret;

	equals = _strchr(aliasString, '=');
	if (!equals)
		return (1);

	tempChar = *equals;
	*equals = '\0';

	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, nodeStartsWith(info->alias, aliasString, -1)));

	*equals = tempChar;
	return (ret);
}

/**
 * setAlias - Set an alias
 * @info: Parameter structure
 * @aliasString: The alias string to set
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *aliasString)
{
	char *equals;

	equals = _strchr(aliasString, '=');
	if (!equals)
		return (1);

	if (!*++equals)
		return (unsetAlias(info, aliasString));

	unsetAlias(info, aliasString);
	return (add_node_end(&(info->alias), aliasString, 0) == NULL);
}

/**
 * printAlias - Prints an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error.
 */
int printAlias(list_t *node)
{
	char *equals = NULL, *alias = NULL;

	if (node)
	{
		equals = _strchr(node->str, '=');
		for (alias = node->str; alias <= equals; alias++)
			_putchar(*alias);

		_putchar('\'');
		_puts(equals + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * manageAlias - Manages aliases, listing or setting them
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int manageAlias(info_t *info)
{
	int n = 0;
	char *equals = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}

	for (n = 1; info->argv[n]; n++)
	{
		equals = _strchr(info->argv[n], '=');
		if (equals)
			setAlias(info, info->argv[n]);
		else
			printAlias(nodeStartsWith(info->alias, info->argv[n], '='));
	}

	return (0);
}
