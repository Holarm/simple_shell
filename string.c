#include "shell.h"

/**
 * _strlen - prints lenght of the string
 * @s: the length to be checked
 * Return: lenght of the string
 */
int _strlen(char *s)
{
	int k = 0;

	if (!s)
		return (0);

	while (*s++)
		k++;
	return (k);
}

/**
 * _strcmp - performs  comparison between the two  strangs.
 * @s1:  first strang
 * @s2:  second strang
<<<<<<< HEAD
 * Return: prints negative on s1 < s2, positive on s1 > s2, zero on  s1 == s2
=======
 * Return:prints  negative on s1 < s2
 * during positive on s1 > s2, zero on  s1 == s2
>>>>>>> 675bb50ffdf56a2901761b713e97981b3946a7e2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks whether haystack is at the start
 * @haystack: string on search
 * @needle: the substring to find
 *
 * Return: address of next char or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - combines two strings
 * @dest: buffer destination
 * @src: buffer source
 *
 * Return: pointerpointing to the buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
