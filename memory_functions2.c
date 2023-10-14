#include "shell.h"

/**
 * Bfree - free the pointer and NULL the Address
 * @parameter: Address the pointer to free
 * Return: 1 if freed, otherwise 0
 */
int Bfree(void **parameter)
{
	if (parameter && *parameter)
	{
		free(*parameter);
		*parameter = NULL;
		return (1);
	}
	return (0);
}
