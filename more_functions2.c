#include "shell.h"

/**
 * _erratoi - transform a string into integer
 * @s: string must be transformed
 * Return: 0 number transformed if there are no numbers in the string
 *       -1 on error
 */
int _erratoi(char *s)
{
	int n = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Why does this cause main to return 255? */
	for (n = 0;  s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			result *= 10;
			result += (s[n] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - pull a message error
 * @information: struct for argument and return information
 * @str: string with the indicated error type
 * Return: 0 if no numbers in string, transformed number otherwise
 *        -1 on error
 */
void print_error(info_t *information, char *str)
{
	_eputs(information->fname);
	_eputs(": ");
	print_d(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(str);
}

/**
 * print_d - a decimal (integ) number in base ten is printed by function
 * @input: input
 * @fd: writing to the file descriptor
 *
 * Return: quantity of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function is an imitation of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *parameter;
	unsigned long i = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		i = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	parameter = &buffer[49];
	*parameter = '\0';

	do	{
		*--parameter = array[i % base];
		i /= base;
	} while (i != 0);

	if (sign)
		*--parameter = sign;
	return (parameter);
}

/**
 * remove_comments -function substitutes "0" for the first occurence of "#"
 * @buffer: address of the modified string
 *
 * Return: Always 0
 */
void remove_comments(char *buffer)
{
	int n;

	for (n = 0; buffer[n] != '\0'; n++)
		if (buffer[n] == '#' && (!n || buffer[n - 1] == ' '))
		{
			buffer[n] = '\0';
			break;
		}
}
