#include "shell.h"

/**
 * Shellnteractive - back to true if the shell is Shellinteractive mode
 * @information: structure address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int Shellnteractive(info_t *information)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * Isfunctiondelimeter - test if the char is a delimeter
 * @c: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int Isfunctiondelimeter(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 *ISfunctionalpha - test the alphabetic char
 *@c: The char to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int ISfunctionalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *SHellatoi - transform a string to an integ
 *@s: string to be transformed
 *Return: 0 if no numbers in string, transformed number otherwise
 */

int SHellatoi(char *s)
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
