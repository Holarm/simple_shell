#include "shell.h"
/**
 * is_cmd - determines if a file is an executable command
 * @info: information of a structure
 * @path: path of a file
 * Return: 1 if it is true, 0 if not
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars -prints the  duplicates characters
 * @pathstr: path of a string
 * @start: enrty index
 * @stop: ending  index
 * Return: pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int k = 0, z = 0;

	for (z = 0, k = start; k < stop; k++)
		if (pathstr[k] != ':')
			buf[z++] = pathstr[k];
	buf[z] = 0;
	return (buf);
}

/**
 * find_path - finds the  PATH string
 * @info: information structure
 * @pathstr: the PATH string
 * @cmd: fins the cmd
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int k = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[k] || pathstr[k] == ':')
		{
			path = dup_chars(pathstr, curr_pos, k);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[k])
				break;
			curr_pos = k;
		}
		k++;
	}
	return (NULL);
}
