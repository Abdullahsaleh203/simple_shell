#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
/**
 * _getline_Helper - .
 * @lineptr:l.
 * @n:n.
 * @stream:s.
 * Return:0.
 */
ssize_t _getline_Helper(char **lineptr, size_t *n,
		__attribute__((unused)) FILE * stream)
{
	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	return (0);
}

/**
 * _getline - .
 * @lineptr:l.
 * @n:n.
 * @stream:s.
 * Return:ptr.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t readd;
	char *buff, *ptr;
	size_t size;

	_getline_Helper(lineptr, n, stream);
	ptr = *lineptr;
	size = *n;
	while (1)
	{
		readd = read(STDIN_FILENO, ptr, size);
		if (readd == -1)
			return (-1);
		else if (readd == 0)
			break;
		ptr += readd;
		size -= readd;
		if (size == 0)
		{
			size = *n * 2;
			buff = malloc(sizeof(char) * size);
			if (buff == NULL)
				return (-1);
			*lineptr = buff;
			ptr = *lineptr + (*n - size);
			*n = size;
		}
		if (*(ptr - 1) == '\n')
			break;
	}
	if (ptr == *lineptr)
		return (-1);
	*ptr = '\0';
	return (ptr - *lineptr);
}
