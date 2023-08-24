#include "shell.h"

/**
 * main - Entry point to the shell program.
 * @argc: Argument count.
 * @argv: Argument values.
 * @env: Environment vector.
 * Return: Exit status of the shell program.
 */
int main(int argc, char *argv[], char *env[])
{
	int o_mode, counter = 0, *status, t = 0, non_int_count = 1;
	char *line, **line_vector = NULL, **lines = NULL;
	_list_paths *current;

	status = &t;
	o_mode = check_mode(argc);
	if (o_mode != INTERACTIVE)
		lines = get_commands(o_mode, argv[1], argv[0]);
	current = set_all_paths_to_list();

	while (++counter && non_int_count)
	{
		if (o_mode == NON_INTERACTIVE_PIPED || o_mode == NON_INTERACTIVE_FILE)
		{
			if (lines[counter - 1])
				line = lines[counter - 1];
			else
			{
				free(lines);
				break;
			}
		}
		else if (o_mode == INTERACTIVE)
			line = get_command_from_user(current);

		if (!line)
			continue;
		line_vector = get_av_with_flags(line, *status);
		if (!line_vector)
		{
			free(line);
			continue;
		}

		if (is_dir(line_vector[0], argv, counter, line_vector, status, line) == 0)
			continue;

		if (is_built_in(line, line_vector, current, argv[0], counter, status, NULL, lines, argv) != 0)
			is_not_built_in(line_vector, env, status, counter, current, argv);

		free_li_vec(line, line_vector);
	}

	free_list(current);
	exit(*status);
}

/**
 * print_list - Print a list of paths.
 * @p: Reference to list of paths.
 * Return: The size of the list.
 */
size_t print_list(const _list_paths *p)
{
	int size = 0;

	if (p == NULL)
		return (0);

	while (p)
	{
		if (p->path == NULL)
		{
			printf("[0] (nil)\n");
			fflush(stdout);
		}
		else
		{
			printf("[%d] %s\n", p->len, p->path);
			fflush(stdout);
		}
		p = p->next;
		size++;
	}
	return (size);
}

/**
 * set_list_env - Set the environment list.
 * @p: Reference to list of paths.
 */
void set_list_env(_list_paths *p)
{
	int size, list_size;
	char **env;

	size = 0;
	if (p == NULL)
		return;
	list_size = env_list_len(p);
	env = malloc(sizeof(char *) * (list_size));
	if (env == NULL)
	{
		perror("don't have size for env");
		return;
	}
	while (p)
	{
		if (p->path != NULL)
		{
			env[size++] = p->path;
			p = p->next;
		}
	}
	environ = env;
}

/**
 * env_list_len - Calculate the length of the env list.
 * @p: Reference to list of paths.
 * Return: The size of the list.
 */
size_t env_list_len(const _list_paths *p)
{
	int size = 0;

	if (p == NULL)
		return (0);

	while (p)
	{
		p = p->next;
		size++;
	}
	if (size - 2 > 0)
		return (size - 2);
	else
		return (0);
}

/**
 * is_not_built_in - Execute non-built-in commands.
 * @line_vector: Arg vector.
 * @env: Env vector.
 * @status: Exit status.
 * @counter: Command counter.
 * @current: Current paths list.
 * @argv: Arg values.
 */
void is_not_built_in(char **line_vector, char *env[], int *status,
		int counter, _list_paths *current, char *argv[])
{
	char *new_path;

	if (access(line_vector[0], X_OK) == 0)
		execute_command(line_vector[0], line_vector, env, status);
	else
	{
		new_path = check_access(line_vector[0], current);
		if (new_path)
		{
			execute_command(new_path, line_vector, env, status);
			free(new_path);
		}
		else
		{
			if (access(line_vector[0], F_OK) == 0)
			{
				print_error(argv[0], counter, line_vector[0], PERMISSION_DENIED);
				*status = PERMISSION_DENIED;
			}
			else
			{
				print_error(argv[0], counter, line_vector[0], NOT_FOUND);
				*status = NOT_FOUND;
			}
		}
	}
}

