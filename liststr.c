#include "shell.h"

/**
 * add_node - brings a node to the list's beginning.
 * @head: the head node's pointer address
 * @str: string field of a node
 * @number: using history's node index
 * Return: size of the list
 */
list_t *add_node(list_t **head, const char *str, int number)
{
	list_t *current_head;

	if (!head)
		return (NULL);
	current_head = malloc(sizeof(list_t));
	if (!current_head)
		return (NULL);
	_memset((void *)current_head, 0, sizeof(list_t));
	current_head->num = number;
	if (str)
	{
		current_head->str = _strdup(str);
		if (!current_head->str)
		{
			free(current_head);
			return (NULL);
		}
	}
	current_head->next = *head;
	*head = current_head;
	return (current_head);
}

/**
 * add_node_end - adds a node to the list's end
 * @head: the head node's pointer address
 * @str: string field of the node
 * @number: using history's node index
 * Return: size of the list
 */
list_t *add_node_end(list_t **head, const char *str, int number)
{
	list_t *current_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	current_node = malloc(sizeof(list_t));
	if (!current_node)
		return (NULL);
	_memset((void *)current_node, 0, sizeof(list_t));
	current_node->num = number;
	if (str)
	{
		current_node->str = _strdup(str);
		if (!current_node->str)
		{
			free(current_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = current_node;
	}
	else
		*head = current_node;
	return (current_node);
}

/**
 * print_list_str - only outputs a list_t linked list's str element
 * @head: reference to the root node
 * Return: size the list
 */
size_t print_list_str(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - removes a node at a specified index
 * @head: address of the first node's pointer
 * @index: index of the deleted node
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			previous_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - releases every node on a list
 * @head_parameter: address of the head node's pointer
 * Return: void
 */
void free_list(list_t **head_parameter)
{
	list_t *node, *upcoming_node, *head;

	if (!head_parameter || !*head_parameter)
		return;
	head = *head_parameter;
	node = head;
	while (node)
	{
		upcoming_node = node->next;
		free(node->str);
		free(node);
		node = upcoming_node;
	}
	*head_parameter = NULL;
}
