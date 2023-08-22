#include "shell.h"
/**
 * The header file 
 * function bulit_in
 * @print_env:
 * @status: i
 * Return: void
 */
void print_env(int *status)
{
	int s;

	for (s = 0; environ[s] != NULL; s++)
	{
		write(STDOUT_FILENO, environ[s], _strlen(environ[s]));
		write(STDOUT_FILENO, "\n", 1);
	}
	*status = 0; 
	/*success
	*status = 0 
	*/
}
/**
 * @get_status:
 * @n:
 * Return:ppid_s
 */
char *get_status(int n)
{
	char *status;

	status = num_to_char(n);
	return (status);
}
/**
 * get_process_id : ()
 * Return: ppid_s
 */
char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = num_to_char(pid);

	return (ppid_s);
}
/**
 * is_built_in - 
 * @line: 
 * @line_vector: 
 * @current: 
 * @program_shell: program_shell
 * @counter: 
 * @status: 
 * @env_list: 
 * @lines: 
 * @argv: 
 * Return: (-1)
 */
int is_built_in(char *line, char **line_vector, _list_paths *current,
	char *program_shell, int counter, int *status, _list_paths *env_list,
	char **lines, char **argv)
{
	int i, x = -1;
	char *built_in[] = {"env", "exit", "cd", "setenv", "unsetenv"};

	for (i = 0; i < 5; i++)
	{
		if (_strcmp(built_in[i], line_vector[0]) == 0)
		{
			x = i;
			break;
		}
	}
	if (x == -1)
		return (x);

	switch (x)
	{
		case 0:
			print_env(status);
			break;
		case 1:
			is_exit(line, line_vector, current, program_shell,
					counter, status, env_list, lines);
			break;
		case 2:
			_cd(line_vector, argv);
			break;
		case 3:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		case 4:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		default:
			return (-1);
	}
	return (0);
}
/**
 * @_setenv: functions
 * @name: bulit in function
 * @value: pointer value
 * @env_list: enveromint list
 * Return: NULL
 */
void _setenv(char *name, char *value, _list_paths *env_list)
{
	_list_paths *var;
	char *full_var;
	int count;

	count = _strlen(name) + _strlen(value) + 2;
	full_var = malloc(count);
	if (full_var == NULL)
	{
		perror("setenv ERROR");
	}
	full_var = _strcpy(full_var, name);
	full_var[_strlen(name)] = '=';
	full_var[_strlen(name) + 1] = '\0';
	full_var = _strcat(full_var, value);
	full_var[count - 1] = '\0';
	var = get_variable(name, env_list);
	if (var == 0)
	{
		free(var->path);
		var->path = full_var;
		var->len = _strlen(full_var);
	}
	else
	{
		add_node(&env_list, full_var);
		var->len = _strlen(full_var);
	}
	print_list(env_list);
}
