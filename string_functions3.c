#include "shell.h"

/**
 **_strncpy - cut the string
 *@destination: replicating the final string
 *@source: string a source
 *@num: the quantity of copied characters
 *Return: the str concatenated
 */
char *_strncpy(char *destination, char *source, int num)
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
 **_strncat - the concatenate of 2 strings
 *@destination: the 1st string
 *@source: the 2nd string
 *@num: utilised bytes in terms of size
 *Return: sting to concatenated
 */
char *_strncat(char *destination, char *source, int num)
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
 **_strchr - finds a character within a string
 *@st: to be parsed is the string
 *@c: look for char
 *Return: (st) a pointer to the memory area str
 */
char *_strchr(char *st, char c)
{
	do {
		if (*st == c)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
