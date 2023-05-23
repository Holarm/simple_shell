#include "shell.h"
/**
 * is_chain -test whether it is a delimeter
 * @info: parameter structure
 * @buf: the char buffer
 * @p: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 if not a chain delimeter
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t l = *p;

	if (buf[l] == '|' && buf[l + 1] == '|')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[l] == '&' && buf[l + 1] == '&')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[l] == ';') /* found end of this command */
	{
		buf[l] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = l;
	return (1);
}

/**
 * check_chain - continue chainig based on the last status of the checking
 * @info: parameter structure
 * @buf: the char buffer
 * @p: checks on the address  of current position in buffer
 * @i:  position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t l = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			l = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			l = len;
		}
	}

	*p = l;
}

/**
 * replace_alias - replaces an aliases
 * @info: parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int k;
	list_t *node;
	char *p;

	for (k = 0; k < 10; k++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars 
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int k = 0;
	list_t *node;

	for (k = 0; info->argv[k]; k++)
	{
		if (info->argv[k][0] != '$' || !info->argv[k][1])
			continue;

		if (!_strcmp(info->argv[k], "$?"))
		{
			replace_string(&(info->argv[k]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[k], "$$"))
		{
			replace_string(&(info->argv[k]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[k][1], '=');
		if (node)
		{
			replace_string(&(info->argv[k]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address informing the old string
 * @new:  adress new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
