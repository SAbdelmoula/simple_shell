#include "shell.h"

/**
 * get_environment - returns a duplicate of our envir string array
 * @info: Arrangement with possible arguments
 *
 * Return: The environment strings array
 */
char **get_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		info->environment = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environment);
}

/**
 * _unsetenvironment - Eliminate a setting variable
 * @info: Arrangement with possible arguments
 *
 * @varName: The name of the environment variable to remove
 * Return: 1 if the variable is removed, 0 otherwise
 */
int _unsetenvironment(info_t *info, char *varName)
{
	list_t *currentNode = info->env;
	size_t index = 0;
	char *equalsSignPosition;

	if (!currentNode || !varName)
		return (0);

	while (currentNode)
	{
		equalsSignPosition = starts_with(currentNode->str, varName);
		if (equalsSignPosition && *equalsSignPosition == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			currentNode = info->env;
			continue;
		}
		currentNode = currentNode->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenvironment - Set up a fresh environment variable,
 *                    or change a current one
 * @info: Arrangement with possible arguments
 * @varName: The name of the environment variable
 * @value: The value to set for the environment variable
 * Return: Always 0
 */
int _setenvironment(info_t *info, char *varName, char *value)
{
	char *envString = NULL;
	list_t *currentNode;
	char *equalsSignPosition;

	if (!varName || !value)
		return (0);

	envString = malloc(_strlen(varName) + _strlen(value) + 2);
	if (!envString)
		return (1);
	_strcpy(envString, varName);
	_strcat(envString, "=");
	_strcat(envString, value);
	currentNode = info->env;
	while (currentNode)
	{
		equalsSignPosition = starts_with(currentNode->str, varName);
		if (equalsSignPosition && *equalsSignPosition == '=')
		{
			free(currentNode->str);
			currentNode->str = envString;
			info->env_changed = 1;
			return (0);
		}
		currentNode = currentNode->next;
	}
	add_node_end(&(info->env), envString, 0);
	free(envString);
	info->env_changed = 1;
	return (0);
}
