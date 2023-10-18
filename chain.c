#include "shell.h"

/**
 * is_chain - verify if the buffer's current character
 *                 is a chain delimeter
 * @info: structure for the parameter
 * @buffer: The buffer character
 * @position: current workplace address in buffer
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buffer, size_t *position)
{
	size_t n = *position;

	if (buffer[n] == '|' && buffer[n + 1] == '|')
	{
		buffer[n] = 0;
		n++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[n] == '&' && buffer[n + 1] == '&')
	{
		buffer[n] = 0;
		n++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[n] == ';') /* Found the end of this cmd */
	{
		buffer[n] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*position = n;
	return (1);
}

/**
 * check_chain - Checks whether we should continue chaining
 *              based on the last check
 * @info: structure for the parameter
 * @buffer: buffer character
 * @position: Address of the new  position in the buffer
 * @startIndex: Starting position in the buffer
 * @length: Length of the buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buffer, size_t *position,
		size_t startIndex, size_t length)
{
	size_t n = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[startIndex] = 0;
			n = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[startIndex] = 0;
			n = length;
		}
	}

	*position = n;
}

/**
 * replace_alias - substitutes a tokenized string's aliases
 * @info: structure for the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *aliasValue;

	for (n = 0; n < 10; n++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		aliasValue = _strchr(node->str, '=');
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
 * replace_vars - alters the tokenized string's variables
 * @info: structure for the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!_strcmp(info->argv[n], "$?"))
		{
			replace_string(&(info->argv[n]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[n], "$$"))
		{
			replace_string(&(info->argv[n]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[n][1], '=');
		if (node)
		{
			replace_string(&(info->argv[n]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[n], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - swap out a string
 * @oldString: Location of the previous string
 * @newString: current string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldString, char *newString)
{
	free(*oldString);
	*oldString = newString;
	return (1);
}
