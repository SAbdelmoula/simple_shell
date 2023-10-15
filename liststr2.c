#include "shell.h"

/**
 * ListLen - specifies the linked list's length
 * @head: pointer to the 1st node
 * Return: size of the list
 */
size_t ListLen(const list_t *head)
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
 * Listtostrings - backing an array of strings of  list->structure
 * @head: pointer to 1st node
 * Return: an array of strings
 */
char **Listtostrings(list_t *head)
{
	list_t *node = head;
	size_t n = ListLen(head), a;
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
				free(strs[a]);
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
 * PrintList - lsit all elements of a list_t linked list
 * @head: pointer to 1st node
 * Return: size the list
 */
size_t PrintList(const list_t *head)
{
	size_t n = 0;

	while (head)
	{
		_puts(ConvertShellnumber(head->num, 10, 0));
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
 * Nodestartswith - backing node whose string starts with prefix
 * @node: pointer to the list head
 * @prefix: string to the match
 * @c: the next char after prefix to match
 *
 * Return: match the node or null
 */
list_t *Nodestartswith(list_t *node, char *prefix, char c)
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
 * GetNodeIndex - obtain the index of the node
 * @head: pointer to the head list
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t GetNodeIndex(list_t *head, list_t *node)
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
