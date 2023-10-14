#include "shell.h"

/**
 * AddNode - Add the node to the beginning of the list
 * @head: the address pointer to head node
 * @structure: structure the field of the node
 * @number: node index used by history
 * Return: size of the list
 */
list_t *AddNode(list_t **head, const char *structure, int number)
{
	list_t *currenthead;

	if (!head)
		return (NULL);
	currenthead = malloc(sizeof(list_t));
	if (!currenthead)
		return (NULL);
	_memset((void *)currenthead, 0, sizeof(list_t));
	currenthead->number = number;
	if (structure)
	{
		currenthead->structure = _strdup(structure);
		if (!currenthead->structure)
		{
			free(currenthead);
			return (NULL);
		}
	}
	currenthead->next = *head;
	*head = currenthead;
	return (currenthead);
}

/**
 * AddNode_End - add the node to the backing of the list
 * @head: the address pointer to head node
 * @structure: structure field of the node
 * @number: node index used by history
 * Return: size of the list
 */
list_t *AddNode_End(list_t **head, const char *structure, int number)
{
	list_t *current_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	current_node = malloc(sizeof(list_t));
	if (!current_node)
		return (NULL);
	_memset((void *)current_node, 0, sizeof(list_t));
	current_node->number = number;
	if (structure)
	{
		current_node->structure = _strdup(structure);
		if (!current_node->structure)
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
 * PrintListstructure - Print only the element structure of
 *                     the list_t linked list
 * @head: pointer to the first node
 * Return: size the list
 */
size_t PrintListstructure(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		_puts(head->structure ? head->structure : "(nil)");
		_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * DeleteNodeIndex - Delete the node at the given index
 * @head: the address pointer to the first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int DeleteNodeIndex(list_t **head, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->structure);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			previous_node->next = node->next;
			free(node->structure);
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
 * FreeList - free all the nodes from the list
 * @head_parameter: the address pointer to head node
 * Return: void
 */
void FreeList(list_t **head_parameter)
{
	list_t *node, *upcoming_node, *head;

	if (!head_parameter || !*head_parameter)
		return;
	head = *head_parameter;
	node = head;
	while (node)
	{
		upcoming_node = node->next;
		free(node->structure);
		free(node);
		node = upcoming_node;
	}
	*head_parameter = NULL;
}
