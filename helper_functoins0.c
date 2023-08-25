#include "shell.h"

/**
 * get_variable - Get a var from a linked list.
 * @name: The name of the var.
 * @head: The head of the linked list.
 *
 * Return: Pointer to the var node or NULL if not found.
 */
_list_paths *get_variable(char *name, _list_paths *head)
{
	while (head)
	{
		if (_var_cmp(name, head->path))
			return (head);
		head = head->next;
	}

	return (NULL);
}

/**
 * _var_cmp - compare variable names.
 * @var_name: the variable name to compare.
 * @full_var: the full var str.
 *
 * Return: (-1).
 */
int _var_cmp(char *var_name, char *full_var)
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

/**
 * number_to_char - convert a number to a string.
 * @num: the number to convert.
 *
 * Return: the converted str.
 */
char *number_to_char(int num)
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

	cp_num = malloc(sizeof(char) * (cp + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}

	cp_num[cp] = '\0';
	while (cp != 0)
	{
		cp--;
		cp_num[cp] = '0' + num % 10;
		num /= 10;
	}

	return (cp_num);
}

/**
 * char_count_piped - Count occurrences of a character in a string.
 * @str: The input string.
 * @cp: The character to count.
 *
 * Return: The count of occurrences-1.
 */
unsigned int char_count_piped(char *str, char cp)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str == cp)
			count++;
		str++;
	}

	return (count + 1);
}


