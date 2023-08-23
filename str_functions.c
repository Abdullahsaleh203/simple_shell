#include "shell.h"

/**
 * _strlen - returns the length of a String.
 * @s: a pointer to the strings
 * in the string using a loop. It returns the length of
 * Return: the length of the string *s
 */
int _strlen(char *s)
{
	int len;

	len = 0;
	if (s[0] == '\0')
		return (0);

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * _strcmp - compares too the strings
 * @s1: ptr of the first string
 * @s2: ptr of the second string
 * Return: 0
 */
int _strcmp(char *s1, char *s2)
{
    int i = 0;

    while ((s1[i] != '\0') || (s2[i] != '\0'))
    {
        if (s1[i] - s2[i] != 0)
            return (s1[i] - s2[i]);
        i++;
    }

    return 0;
}

/**
 * _strdup - creates an array of chars
 * @str: The array size
 * Return: array refrance or NULL
 */
char *_strdup(char *str)
{
	int len;
	char *arr;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	arr = malloc((sizeof(char) * len) + 1);
	if (arr == NULL)
		return (NULL);
	arr[len] = '\0';
	while (len--)
		arr[len] = str[len];
	return (arr);
}
/**
 * _strcpy - copies a string pointed
 * @dest: char ptr
 * @src: char ptr
 * Return: char ptr to destination
 */
char *_strcpy(char *dest, char *src)
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
 * _strcat - concatenates two arrays(string)
 * @dest: character pointer left side
 * @src: character pointer right side
 * Return: return a pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int len, i;

	len = _strlen(dest);
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[len + i] = src[i];
	}
	dest[len + i] = '\0';
	return (dest);
}
