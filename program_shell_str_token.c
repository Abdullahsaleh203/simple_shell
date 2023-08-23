#include "shell.h"

/**
 * _strtok - .
 * @str: .
 * @delimiters: .
 * Return: .
 */
char *_strtok(char *str, const char *delimiters)
{
	return (strtok(str, delimiters));
}

/**
 * _chrCheck - .
 * @c: .
 * @str: .
 * Return: .
 */
unsigned int _chrCheck(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * free_li_vec - Entry point to the shell
 * @line: arguements count
 * @line_vec: arguements values
 */
void free_li_vec(char *line, char **line_vec)
{
	free(line);
	free_vector(line_vec);
}

/**
 * is_dir - Entry point to the shell
 * @line: arguements count
 * @argv: arguements count
 * @counter: arguements count
 * @line_vec: arguements count
 * @status: arguements count
 * @old_line: arguements count
 * Return: is dir or not
 */
int is_dir(char *line, char **argv, int counter, char **line_vec,
		int *status, char *old_line)
{
	struct stat st;

	if (stat(line, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_error(argv[0], counter, line_vec[0], PERMISSION_DENIED);
			*status = PERMISSION_DENIED;
			free_li_vec(old_line, line_vec);
			return (0);
		}
	}
	return (-1);
}
