#include "shell.h"

/**
 * interactive - shell is true if it returns interactive mode
 * @info: structure address
 * Return:  interactive mode is 1 if not it is 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if char is a delimeter
 * @y: the character to check
 * @delim: delimeter string
 * Return: 1 is true, 0 is false
 */
int is_delim(char y, char *delim)
{
	while (*delim)
		if (*delim++ == y)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabet chararacter
 * @y: character input
 * Return: y is alphabetic
 */

int _isalpha(int y)
{
	if ((y >= 'a' && y <= 'z') || (y >= 'A' && y <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts into integer
 * @s: string is converted
 * Return: 0 if no numbers
 */

int _atoi(char *s)
{
	int k, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0; s[k] != '\0' && flag != 2; k++)
	{
		if (s[k] == '-')
			sign *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[k] - '0');
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

