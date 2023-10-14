#include "shell.h"

/**
 * isChainDelimiter - Checks if the current character
 *                 in the buffer is a chain delimiter
 * @info: The parameter structure
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int isChainDelimiter(info_t *info, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[index] == ';') /* Found the end of this command */
	{
		buffer[index] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*position = index;
	return (1);
}

/**
 * checkChain - Checks whether we should continue chaining
 *              based on the last status
 * @info: The parameter structure
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 * @startIndex: Starting position in the buffer
 * @length: Length of the buffer
 *
 * Return: Void.
 */
void checkChain(info_t *info, char *buffer, size_t *position,
		size_t startIndex, size_t length)
{
	size_t index = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[startIndex] = 0;
			index = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[startIndex] = 0;
			index = length;
		}
	}

	*position = index;
}

/**
 * replaceAlias - Replaces aliases in the tokenized string
 * @info: The parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
	int n;
	list_t *node;
	char *aliasValue;

	for (n = 0; n < 10; n++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		aliasValue = strchr(node->str, '=');
		if (!aliasValue)
			return (0);

		aliasValue = _strdup(aliasValue + 1);
		if (!aliasValue)
			return (0);

		info->argv[0] = aliasValue;
	}
	return (1);
}

/**
 * replaceVars - Replaces variables in the tokenized string
 * @info: The parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!_strcmp(info->argv[n], "$?"))
		{
			replaceString(&(info->argv[n]),
					_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[n], "$$"))
		{
			replaceString(&(info->argv[n]), _strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[n][1], '=');
		if (node)
		{
			replaceString(&(info->argv[n]), _strdup(strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replaceString - Replace a string
 * @oldString: Address of the old string
 * @newString: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **oldString, char *newString)
{
	free(*oldString);
	*oldString = newString;
	return (1);
}
