#include "shell.h"

/**
 * SHellerratoi - transform a string to an integ
 * @s: string to be transformed
 * Return: 0 if no numbers in string, transformed number otherwise
 *       -1 on error
 */
int SHellerratoi(char *s)
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
 * PrintShellerror - pull a message error
 * @information: the parameter & backing information structure
 * @str: string with the indicated error type
 * Return: 0 if no numbers in string, transformed number otherwise
 *        -1 on error
 */
void PrintShellerror(info_t *information, char *str)
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
 * Printfunction_d - function outputs an integer decimal (base 10) number
 * @input: input
 * @fd: writing to the file descriptor
 *
 * Return: the characters number to be printed
 */
int Printfunction_d(int input, int fd)
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
 * ConvertShellnumber - transfer function, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *ConvertShellnumber(long int number, int base, int flags)
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
		*--parmeter = array[i % base];
		i /= base;
	} while (i != 0);

	if (sign)
		*--parmeter = sign;
	return (parmeter);
}

/**
 * RemoveShellcomment -replace 1st function instance of '#' with '\0'
 * @buffer: address of the modified string
 *
 * Return: Always 0
 */
void RemoveShellcomment(char *buffer)
{
	int n;

	for (n = 0; buffer[n] != '\0'; n++)
		if (buffer[n] == '#' && (!n || buffer[n - 1] == ' '))
		{
			buffer[n] = '\0';
			break;
		}
}
