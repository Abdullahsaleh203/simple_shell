#include "shell.h"
/**** 
*header file shell.h"
 * _list_paths
 * @get_variable:
 * Return:
 */
_list_paths *get_variable(char *name, _list_paths *head)
{
	while (head)
	{
		if (_varcmp(name, head->path))
			return (head);
		head = head->next;
	}

	return (NULL);
}
/**
 * _varcmp:-
 * @var_name: 
 * @full_var:
 * Return: (-1) 
 */
int _varcmp(char *var_name, char *full_var)
{
	int l;

	for (l = 0; var_name[l]; l++)
	{
		if (full_var[l])
			if (var_name[l] - full_var[l] != 0)
				return (-1);
	}
	if (full_var[l] == '=')
		return (0);

	return (-1);
}
/****
 * @num_to_char:
 * @cp_num: number to be converted
 * @num:
 * @cp:
 * Return:  cp_num
 */
char *num_to_char(int num)
{
	int cp = 0, tmp = num;
	char *cp_num;

	if (num == 0)
	{
		cp = 1;
	}
	else
	{
		while (tmp != 0)
		{
			tmp /= 10;
			cp++;
		}
	}
	cp_num = malloc(sizeof(char) * (c + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}
	cp_num[cp] = '\0';
	while (cp != 0)
	{
		cp--;
		cp_num[c] = '0' + num % 10;
		num /= 10;
	}
	return (cp_num);
}
/**
 * @char_count_piped:
 * @str:  ptr str
 * @c: char c 
 * @count: number
 * Return:  count + 1
 */
unsigned int char_count_piped(char *str, char c)
{
	unsigned int count = 0;
// unsigned int
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count + 1);
}
