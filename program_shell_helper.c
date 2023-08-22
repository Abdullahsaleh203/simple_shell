#include "shell.h"


// check_mode 

int check_mode(int argc)
{
	struct stat stdin_stat;

	fstat(STDIN_FILENO, &stdin_stat);
	if (isatty(STDIN_FILENO) && argc == 1)
		return (INTERACTIVE);
	if ((!isatty(STDIN_FILENO) && argc == 1))
		return (NON_INTERACTIVE_PIPED);
	if ((argc >= 1))
		return (NON_INTERACTIVE_FILE);

	return (ERROR);
}


//is_exit 
void is_exit(char *line, char **line_vector, list_path *current,
		char *program_shell, int counter, int *status, list_path *env, char **lines)
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
// _atoi 
int _atoi(char *s)
{
	unsigned int x, l;
	char positive;
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

// >> execute_command <<
void execute_command(char *path, char **av, char **env, int *status)
{
	pid_t pid;
// fork();
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
// >> free_vector 
void free_vector(char **argv)
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
	// free argv.
}
