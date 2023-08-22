#include "shell.h"
/**** 
 * helper functions
 * @et_av_with_flags_helper:
 * Return: cmd
 */ 
char *get_av_with_flags_helper(char *token, char *line, char **av, int status)
{
		char *var, *cmd, *line_cpy;

	line_cpy = line;
		if (token == NULL)
	{
		free(av);
		free(line_cpy);
		return (NULL);
	}
	if (_strcmp("$$", token) == 0)
		cmd = get_process_id();
	else if (_strcmp("$?", token) == 0)
		cmd = get_status(status);
	else if ((token[0] == '$') && (token[1]))
	{
		var = _getenv(&token[1]);
		if (var)
			cmd = _strdup(var);
		else
			cmd = _strdup("");
	}
	else
		cmd = _strdup(token);

	return (cmd);
}
/***
 * @get_av_with_flags:
 * Return: av
 */ 
char **get_av_with_flags(char *line, int status)
{
	char *line_cpy, *token, **av, *var, *cmd;
	int i = 0, c_count;

	handle_comments(line);
	if (line[0] == '\0')
		return (NULL);
	line_cpy = _strdup(line);
	if (line_cpy == NULL)
		return (NULL);
	c_count = char_count(line_cpy, ' ');
	av = malloc((c_count + 1) * sizeof(char *));
	token = _strtok(line_cpy, TOK_D);
	cmd = get_av_with_flags_helper(token, line, av, status);
	av[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, TOK_D);
		if (token != NULL)
		{
			if (_strcmp("$$", token) == 0)
				cmd = get_process_id();
			else if (_strcmp("$?", token) == 0)
				cmd = get_status(status);
			else if ((token[0] == '$') && (token[1]))
			{
				var = _getenv(&token[1]);
				if (var)
					cmd = _strdup(var);
				else
					cmd = _strdup("");
			}
			else
				cmd = _strdup(token);
			av[i++] = cmd;
		}
	}
	av[i] = NULL;
	free(line_cpy);
	return (av);
}
/****
 * @exit_check:
 * Return: void
 */
void exit_check(int nread, char *exit_cmd)
{
	if (nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
}

/****
 * @_getenv:
 * Return:  NULL
 */
char *_getenv(char *name)
{
	int i = 0, j = 0;

	if (name == NULL)
		return (NULL);
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '=')
		{
			if (environ[i][j] != name[j])
				break;
			if (environ[i][j] == name[j] && (environ[i][j + 1] == '='))
				return (&environ[i][_strlen(name) + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*****
 * @char_count:
 * Return:  count + 1
 */
unsigned int char_count(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str != c && *(str + 1) == c)
			count++;
		str++;
	}
	return (count + 1);
}
