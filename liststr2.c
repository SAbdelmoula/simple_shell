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
	char **structures;
	char *structure;

	if (!head || !n)
		return (NULL);
	structures = malloc(sizeof(char *) * (n + 1));
	if (!structures)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		structure = malloc(_strlen(node->structure) + 1);
		if (!structure)
		{
			for (a = 0; a < n; a++)
				free(structures[a]);
			free(structures);
			return (NULL);
		}

		structure = _strcpy(structure, node->structure);
		structures[n] = structure;
	}
	structures[n] = NULL;
	return (structures);
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
		_puts(head->structure ? head->structure : "(nil)");
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
		position = starts_with(node->structure, prefix);
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
