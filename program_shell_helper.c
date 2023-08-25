#include "shell.h"

/**
 * checker_mode - Determine the operating mode of the shell.
 * @argc: Argument count.
 * Return: Operating mode.
 */
int checker_mode(int argc)
{
	struct stat stdin_stat;

	fstat(STDIN_FILENO, &stdin_stat);
	if (isatty(STDIN_FILENO) && argc == 1)
		return (INTERACTIVE);
	if ((!isatty(STDIN_FILENO) && argc == 1))
		return (NOT_INTERACTIVE_PIPED);
	if ((argc >= 1))
		return (NOT_INTERACTIVE_FILE);

	return (ERROR);
}

/**
 * is_exit - Check if the command is an "exit" command.
 * @line: Command line.
 * @line_vector: Command line split into arg.
 * @current: Ptr to the current path list.
 * @program_shell: Name of the shell program.
 * @counter: Command counter.
 * @status: Ptr to the exit status.
 * @env: Ptr to the environment path list.
 * @lines: Ptr to command lines.
 */
void is_exit(char *line, char **line_vector, _list_paths *current,
		char *program_shell, int counter
		, int *status, _list_paths *env, char **lines)
{
	int n;

	if (_strcmp(line_vector[0], "exit") == 0)
	{
		if (line_vector[1] == NULL)
		{
			free_all(lines, counter, env, current, line, line_vector);
			exit(*status);
		}
		else if (line_vector[1] != NULL)
		{
			if (_strlen(line_vector[1]) <= 9)
			{
				n = _atoi(line_vector[1]);
				if (n != -1)
				{
					free_all(lines, counter, env, current, line, line_vector);
					exit(n);
				}
				else
				{
					*status = EXIT_ERROR;
					print_error(program_shell, counter, line_vector[1], EXIT_ERROR);
				}
			}
			else
			{
				*status = EXIT_ERROR;
				print_error(program_shell, counter, line_vector[1], EXIT_ERROR);
			}
		}
	}
}

/**
 * _atoi - convert a str to an int.
 * @s: Input str.
 * Return: converted int, or -1 if not a valid int.
 */
int _atoi(char *s)
{
	unsigned int x, l;
	char positive = 0;

	x = 0;
	l = 0;
	while (s[l] != '\0')
	{
		if (!((s[l] >= '0') && (s[l] <= '9')))
		{
			return (-1);
		}
		if (((s[l] >= '0') && (s[l] <= '9')))
		{
			x = (x * 10) + (s[l] - '0');
		}
		else if (s[l] == '+')
			positive++;

		l++;
	}

	return (x);
}

/**
 * execute_command - Exe a command.
 * @path: Path of the command.
 * @av: Command arg.
 * @env: env var.
 * @status: exit status.
 */
void execute_command(char *path, char **av, char **env, int *status)
{
	pid_t pid;

	pid = fork();
	if (pid == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, av, env) == -1)
			exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, status, WUNTRACED);
		*status  = WEXITSTATUS(*status);
	}
}

/**
 * free_vec - free a vec of strings.
 * @argv: Vec to free.
 */
void free_vec(char **argv)
{
	char **curr;

	if (argv == NULL)
		return;

	curr = argv;
	while (*curr != NULL)
	{
		free(*curr);
		curr++;
	}

	free(argv);
}



