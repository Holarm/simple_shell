#include "shell.h"

/**
 * input_buf - buffers commands
 * @info: struct
 * @buf: address to the buffer
 * @len: address to the  len var
 *
 * Return: bytes information
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t len_p = 0;

	if (!*len) /* if thereni is nothing  in the buffer, fill i */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &len_p, stdin);
#else
		a = _getline(info, buf, &len_p);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0'; /* remove newline */
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - gets a line without a new line
 * @info:  struct
 *
 * Return: bytes information
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t k, l, len;
	ssize_t a = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &len);
	if (a == -1) /* EOF */
		return (-1);
	if (len)
	{
		l = k; /* init new iterator to current buf position */
		p = buf + k; /* get pointer for return */

		check_chain(info, buf, &l, k, len);
		while (l < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}

		k = l + 1; 
		if (l >= len) /* reached end of buffer? */
		{
			k = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (a);
}

/**
 * read_buf - interprets the buffer
 * @info: struct
 * @buf: buffer
 * @i: size
 *
 * Return: the letter r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *k)
{
	ssize_t a = 0;

	if (*k)
		return (0);
	k = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*k = a;
	return (a);
}

/**
 * _getline - gets the  line of input from STDIN
 * @info:  struct
 * @ptr: address of pointer to buffer NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t k, len;
	size_t z;
	ssize_t a = 0, r = 0;
	char *p = NULL, *new_p = NULL, *y;

	p = *ptr;
	if (p && length)
		r = *length;
	if (k == len)
		k = len = 0;

	a = read_buf(info, buf, &len);
	if (a == -1 || (a == 0 && len == 0))
		return (-1);

	y = _strchr(buf + k, '\n');
	z = y ? 1 + (unsigned int)(y - buf) : len;
	new_p = _realloc(p, r, r ? r + z : z + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (r)
		_strncat(new_p, buf + k, z - k);
	else
		_strncpy(new_p, buf + k, z - k + 1);

	r += z - k;
	k = z;
	p = new_p;

	if (length)
		*length = r;
	*ptr = p;
	return (r);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the number signal
 *
 * Return: void nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
