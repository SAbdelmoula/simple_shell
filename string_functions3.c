#include "shell.h"

/**
 **_stringcpy - copy the string
 *@destination: duplicate the destination string
 *@source: the string source
 *@num: the amount of the char to copy
 *Return: the str concatenated
 */
char *_stringcpy(char *destination, char *source, int num)
{
	int a, k;
	char *m = destination;

	a = 0;
	while (source[a] != '\0' && a < num - 1)
	{
		destination[a] = source[a];
		a++;
	}
	if (a < num)
	{
		k = a;
		while (k < num)
		{
			destination[k] = '\0';
			k++;
		}
	}
	return (m);
}

/**
 **_stringcat - the concatenate of 2 strings
 *@destination: the 1st string
 *@source: the 2nd string
 *@num: the amount of bytes to be used
 *Return: the sting concatenated
 */
char *_stringcat(char *destination, char *source, int num)
{
	int a, k;
	char *m = destination;

	a = 0;
	k = 0;
	while (destination[a] != '\0')
		a++;
	while (source[k] != '\0' && k < num)
	{
		destination[a] = source[k];
		a++;
		k++;
	}
	if (k < num)
		destination[a] = '\0';
	return (m);
}

/**
 **_stringchars - the locate a character in the str
 *@str: string to  parsed
 *@c: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *_stringchars(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
