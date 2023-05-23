#include "shell.h"

/**
 *strtow - divide  a string into words
 * @str: the string
 * @d: delimeter string
 * Return: a pointer to an array of strings
 */

char **strtow(char *str, char *d)
{
	int k, l, z, b, numwords = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (k = 0; str[k] != '\0'; k++)
		if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) || !str[k + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	r = malloc((1 + numwords) * sizeof(char *));
	if (!r)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (is_delim(str[k], d))
			k++;
		z = 0;
		while (!is_delim(str[k + z], d) && str[k + z])
			z++;
		r[l] = malloc((z + 1) * sizeof(char));
		if (!r[l])
		{
			for (z = 0; z < l; z++)
				free(r[z]);
			free(r);
			return (NULL);
		}
		for (b = 0; b < z; b++)
			r[l][b] = str[k++];
		s[l][b] = 0;
	}
	r[l] = NULL;
	return (r);
}

/**
 * **strtow2 - divides a string
 * @str:input string
 * @d:  delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int k, l, z, b, numwords = 0;
	char **r;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		if ((str[k] != d && str[k + 1] == d) ||
		    (str[k] != d && !str[k + 1]) || str[k + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	r = malloc((1 + numwords) * sizeof(char *));
	if (!r)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (str[k] == d && str[k] != d)
			k++;
		z = 0;
		while (str[k + z] != d && str[k + z] && str[k + z] != d)
			z++;
		r[l] = malloc((z + 1) * sizeof(char));
		if (!r[l])
		{
			for (z = 0; z < l; z++)
				free(r[z]);
			free(r);
			return (NULL);
		}
		for (b = 0; b < z; b++)
			r[l][b] = str[k++];
		r[l][b] = 0;
	}
	r[l] = NULL;
	return (r);
}
