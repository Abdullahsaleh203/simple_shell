#include "shell.h"

/**
 * _strlen - Returns the length of a str.
 * @s: A Ptr to the str.
 * Return: The length of the str.
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * _strcmp - Compares two str.
 * @s1: Ptr to the first str.
 * @s2: Ptr to the second str.
 * Return: 0 if strs are equal, positive + if s1 > s2, - negative if s1 < s2.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (0);
}

/**
 * _strdup - Creates a duplicate of a str.
 * @str: The str to duplicate.
 * Return: A Ptr to the duplicated str.
 */
char *_strdup(char *str)
{
	int len;
	char *arr;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);
	arr = malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);

	_str_cpy(arr, str);
	return (arr);
}

/**
 * _str_cpy - Copies a str.
 * @dest: destination buffer.
 * @src: Source st.
 * Return: A Ptr to the destination str.
 */
char *_str_cpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _str_cat - concatenates two str.
 * @dest: Destination str.
 * @src: Source str.
 * Return: A Ptr to the resulting str.
 */
char *_str_cat(char *dest, char *src)
{
	int len = _strlen(dest);
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[len + i] = src[i];
	}
	dest[len + i] = '\0';
	return (dest);
}


