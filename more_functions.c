#include "shell.h"

/**
 * interactive -displays true if the shell is in interactive mode
 * @info: structure of the address
 *
 * Return: 1 if interactive mode,otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - determines whether a character is a delimeter
 * @c: the char to verify
 * @delimeter: string of the delimeter
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - verifies alphabetic characters
 *@c: character to enter
 *Return: 1 if c is alphabetic,otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - transform a string into an integer
 *@s: string to be transformed
 *Return: 0 if no numbers in string, transformed number otherwise
 */

int _atoi(char *s)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0;  s[n] != '\0' && flag != 2; n++)
	{
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
