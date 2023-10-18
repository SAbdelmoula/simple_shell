#include "shell.h"

/**
 * _myhistory - Show the line number-based command history list
 * @info: Arrangement with possible arguments
 * Return: always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - puts alias in the string
 * @info: variable struct
 * @str: The alias string to unset
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *n, tempChar;
	int ret;

	n = _strchr(str, '=');
	if (!n)
		return (1);

	tempChar = *n;
	*n = 0;

	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*n = tempChar;
	return (ret);
}

/**
 * set_alias - changes alias to a string
 * @info: variable struct
 * @str: The alias string to set
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *n;

	n = _strchr(str, '=');
	if (!n)
		return (1);

	if (!*++n)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - displays a string of alias
 * @node: an alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *n = NULL, *i = NULL;

	if (node)
	{
		n = _strchr(node->str, '=');
		for (i = node->str; i <= n; i++)
			_putchar(*i);

		_putchar('\'');
		_puts(n + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * _myalias - imitates the built-in alias
 * @info: Arrangement with possible arguments
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *n = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (a = 1; info->argv[a]; a++)
	{
		n = _strchr(info->argv[a], '=');
		if (n)
			set_alias(info, info->argv[a]);
		else
		print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
