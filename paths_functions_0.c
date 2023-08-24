#include "shell.h"
/**
 * add_node - a function to modify the path.
 * @head: the first node of the path.
 * @path: .
 * Return: pointer.
 */
_list_paths *add_node(_list_paths **head, char *path)
{
	char *s_cpy;
	_list_paths *l;

	l = malloc(sizeof(_list_paths));
	if (l == NULL)
		return (NULL);

	if (path)
	{
		s_cpy = _strdup(path);
		if (s_cpy == NULL)
		{
			free(l);
			return (NULL);
		}
		l->path = s_cpy;
		l->len = _strlen(s_cpy);
	}
	else
	{
		l->path = NULL;
		l->len = 0;
	}
	l->next = (*head);
	*head = l;
	return (l);
}

/***
 * free_list - frees a list_t list.
 * @head: pointer to a head pointer
 * free(head)
 */
void free_list(_list_paths *head)
{

	if (head == NULL)
	{
		return;
	}
	free_list(head->next);
	if (head->path)
		free(head->path);
	free(head);
}
/***
 * @set_all_paths_to_list:
 * Return:paths_list
 */
_list_paths *set_all_paths_to_list()
{
	char *path_variable, *path_var_cpy, *token;
	_list_paths *paths_list;

	paths_list = NULL;

	path_variable = _getenv("PATH");
	if (path_variable == NULL)
		return (NULL);

	path_var_cpy = _strdup(path_variable);
	if (path_var_cpy == NULL)
		return (NULL);

	token = _strtok(path_var_cpy, ":");
	while (token != NULL)
	{
		add_node(&paths_list, token);
		token = _strtok(NULL, ":");
	}
	free(path_var_cpy);
	return (paths_list);
	/*does't have access*/
}
/**
 * _list_paths:.
 * @set_all_vector_to_list:
 * Return: paths_list
 */
_list_paths *set_all_vector_to_list()
{
	char *path_var_cpy;
	_list_paths *paths_list;
	int x = 0;

	paths_list = NULL;

	if (environ == NULL)
		return (NULL);
	while (environ[x])
	{
		path_var_cpy = environ[i];
		if (path_var_cpy == NULL)
			return (NULL);
		add_node(&paths_list, path_var_cpy);
		x++;
	}
	return (paths_list); /*Retrun paths_list*/
}
/**
 * check_access .
 * @line_av_1:.
 * @current: pointer to the current.
 * Return:	NULL
 */

char *check_access(char *line_av_1, _list_paths *current)
{
	char *full_path;
	int found = 0, len;

	if (current == NULL)
		return (NULL);
	while (current)
	{
		len = _strlen(current->path) + _strlen(line_av_1) + 2;
		if (len > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}
		full_path = (char *)malloc(len * sizeof(char));
		_strcpy(full_path, current->path);
		_strcat(full_path, "/");
		_strcat(full_path, line_av_1);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		else
			free(full_path);

		current = current->next;
	}
	if (found)
		return (full_path);

	else
		return (NULL);
}
