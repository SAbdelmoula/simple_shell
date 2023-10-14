#include "shell.h"

/**
 * getEnvironment - Returns a copy of the environment strings array
 * @shellInfo: Struct containing potential arguments
 *
 * Return: The environment strings array
 */
char **getEnvironment(shellInfo_t *shellInfo)
{
	if (!shellInfo->environment || shellInfo->envChanged)
	{
		shellInfo->environment = listToStrings(shellInfo->envList);
		shellInfo->envChanged = 0;
	}

	return (shellInfo->environment);
}

/**
 * unsetEnvironmentVar - Remove an environment variable
 * @shellInfo: Struct containing potential arguments
 *
 * @varName: The name of the environment variable to remove
 * Return: 1 if the variable is removed, 0 otherwise
 */
int unsetEnvironmentVar(shellInfo_t *shellInfo, char *varName)
{
	list_t *currentNode = shellInfo->envList;
	size_t index = 0;
	char *equalsSignPosition;

	if (!currentNode || !varName)
		return (0);

	while (currentNode)
	{
		equalsSignPosition = startsWith(currentNode->str, varName);
		if (equalsSignPosition && *equalsSignPosition == '=')
		{
			shellInfo->envChanged = deleteNodeAtIndex(&(shellInfo->envList), index);
			index = 0;
			currentNode = shellInfo->envList;
			continue;
		}
		currentNode = currentNode->next;
		index++;
	}
	return (shellInfo->envChanged);
}

/**
 * setEnvironmentVar - Initialize a new environment variable
 *                    or modify an existing one
 * @shellInfo: Struct containing potential arguments
 * @varName: The name of the environment variable
 * @value: The value to set for the environment variable
 * Return: Always 0
 */
int setEnvironmentVar(shellInfo_t *shellInfo, char *varName, char *value)
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
	currentNode = shellInfo->envList;
	while (currentNode)
	{
		equalsSignPosition = startsWith(currentNode->str, varName);
		if (equalsSignPosition && *equalsSignPosition == '=')
		{
			free(currentNode->str);
			currentNode->str = envString;
			shellInfo->envChanged = 1;
			return (0);
		}
		currentNode = currentNode->next;
	}
	addNodeEnd(&(shellInfo->envList), envString, 0);
	free(envString);
	shellInfo->envChanged = 1;
	return (0);
}
