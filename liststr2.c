#include "shell.h"

/**
 * list_len - specifies the linked list's length
 * @head: pointer to the 1st node
 * Return: size of the list
 */
size_t list_len(const list_t *head)
{
	size_t n = 0;

	while (head)
	{
		head = head->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - backing a list of strings using the list->str
 * @head: pointer to 1st node
 * Return: method of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t n = list_len(head), a;
	char **strs;
	char *str;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (a = 0; a < n; a++)
				free(strs[a]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[n] = str;
	}
	strs[n] = NULL;
	return (strs);
}


/**
 * print_list - displays all of a list_t linked list's components
 * @head: pointer to 1st node
 * Return: size the list
 */
size_t print_list(const list_t *head)
{
	size_t n = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - provides a node whose string prefixes
 * @node: identifier for the list head
 * @prefix: matching string
 * @c: the following char to match after prefix
 *
 * Return: either the node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *position = NULL;

	while (node)
	{
		position = starts_with(node->str, prefix);
		if (position && ((c == -1) || (*position == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - obtaining a node's index
 * @head: list head identifier
 * @node: identifier for the list head
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
