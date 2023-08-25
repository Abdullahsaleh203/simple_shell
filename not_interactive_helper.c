#include "shell.h"
/**
 * get_commands - get commands based on the execution mode.
 * @o_mode: the execution mode.
 * @file_name: the file name if applicable.
 * @program_shell: the name of the shell program.
 * Return: array of strings containing the commands.
 */
char **get_commands(int o_mode, char *file_name, char *program_shell)
{
	char **lines = NULL;

	if (o_mode == NON_INTERACTIVE_PIPED)
	{
		lines = piped_non_interactive();
		if (!lines)
			exit(0);
	}
	else if (o_mode == NON_INTERACTIVE_FILE)
	{
		lines = file_non_interactive(file_name, program_shell);
		if (!lines)
			exit(0);
	}
	return (lines);
}
/**
 * piped_non_interactive - Get commands from non-interactive piped input.
 * Return: array of str containing the commands.
 */
char **piped_non_interactive()
{
	char b[2048], *text = NULL, **lines = NULL;
	ssize_t bytesRead;
	size_t totalchar = 0;
	int i, flag = 0;

	while ((bytesRead = read(STDIN_FILENO, b, 2048)) > 0)
	{
		totalchar += bytesRead;
	}
	if (bytesRead == -1)
	{
		perror("read");
		exit(ERROR);
	}
	if (totalchar > 2048)
	{
		b[2048 - 1] = '\0';
	}
	else
	{
		b[totalchar - 1] = '\0';
	}

	for (i = 0; b[i]; i++)
	{
		if (b[i] != ' ' && b[i] != '\n' && b[i] != '\t'
						&& b[i] != '\r' && b[i] != '\a')
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	totalchar = _strlen(b);
	text = (char *)malloc((totalchar + 1) * sizeof(char));
	if (text != NULL)
	{
		_strcpy(text, b);
		text[totalchar] = '\0';
		lines = text_to_vector(text);
	}
	return (lines);
}

/**
 * text_to_vector-.
 * @text: .
 * Return: lines.
 */
char **text_to_vector(char *text)
{
	char *token, *cmd;
	char **lines = NULL;
	int i = 0;
	unsigned int c_count = 0;

	c_count = char_count_piped(text, '\n');
	lines = (char **)malloc((c_count + 1) * sizeof(char *));
	token = _strtok(text, "\n");
	cmd = _strdup(token);
	lines[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, "\n");
		if (token != NULL)
		{
			cmd = _strdup(token);
			lines[i++] = cmd;
		}
	}
	free(text);
	lines[i] = NULL;
	return (lines);
}
/**
 * file_non_interactive - get commands from a non-interactive file.
 * @file_name: The name of the shell program.
 * @program_shell:  The name of the shell program.
 * Return: array of string containing the commands
 */
char **file_non_interactive(char *file_name, char *program_shell)
{
	struct stat fileStat;
	char *text, **lines;
	int file_descriptor;
	size_t letters;

	if (stat(file_name, &fileStat) != -1)
	{
		if (S_ISREG(fileStat.st_mode))
		{
			file_descriptor = open(file_name, O_RDONLY);
			if (file_descriptor  == -1)
				exit(ERROR);
			if (fileStat.st_size == 0)
				exit(0);
			text = malloc((fileStat.st_size + 1) * sizeof(char));
			if (!text)
				return (NULL);
			letters = read(file_descriptor, text, fileStat.st_size);
			if ((int) letters == -1)
			{
				perror("read");
			}
			close(file_descriptor);

			text[letters - 1] = '\0';
			if (text)
				lines = text_to_vector(text);
			return (lines);
		}
		else
			exit(0);
	}
	else
	{
		/* Print ERROR */
		print_cant_open(program_shell, 0, file_name);
		exit(127);
	}
	return (NULL);
}

