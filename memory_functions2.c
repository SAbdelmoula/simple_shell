#include "shell.h"

/**
 * bfree - NULLs the address and releases a pointer
 * @parameter: address of the free pointer
 * Return: 1 if freed, otherwise 0
 */
int bfree(void **parameter)
{
	if (parameter && *parameter)
	{
		free(*parameter);
		*parameter = NULL;
		return (1);
	}
	return (0);
}
