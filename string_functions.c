#include "shell.h"

/**
 * _strlen - gives back a string's length
 * @st: checking the length of the string
 *
 * Return: strings with integer length
 */
int _strlen(char *st)
{
	int n = 0;

	if (!st)
		return (0);

	while (*st++)
		n++;
	return (n);
}

/**
 * _strcmp - compares two strings lexicographically.
 * @st1: 1st stranger
 * @st2: 2nd stranger
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *st1, char *st2)
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
 * starts_with - sees whether the haystack comes before the needle
 * @haystack: searching a string
 * @needle: the necessary substring to locate
 *
 * Return: address of upcomming char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - attaches two strings together
 * @destination: the target buffer
 * @source: the origin buffer
 *
 * Return: identifier of the final buffer
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
