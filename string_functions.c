#include "shell.h"

/**
 * StringLength - back the length of the string
 * @st: string whose length must be checked
 *
 * Return: Integ length of the string
 */
int StringLength(char *st)
{
	int n = 0;

	if (!st)
		return (0);

	while (*st++)
		n++;
	return (n);
}

/**
 * StringComparison - execute a lexical comparison of two strings.
 * @st1: 1st stranger
 * @st2: 2nd stranger
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int StringComparison(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * startwithHys - test if needle start with haystack
 * @haystack: str to search
 * @needle: substring to find
 *
 * Return: address of upcomming char of haystack or NULL
 */
char *startwithHys(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * stringSHellConcateat - concatenate 2 strings
 * @destination: the buf destination
 * @source: the buf source
 *
 * Return: pointer to the buf destination
 */
char *stringSHellConcateat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
