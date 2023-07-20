#include "shell.h"
/**
 * _getline - func that gets user input
 * @lineptr: pointer to a pointer that holds the input
 * @n: the size of the string
 * @stream: the stream to get from stderr, stdin, or stdout
 * Return: -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t line_length;
	ssize_t buffer_size;
	int c;
	static char buffer[BUFFER_SIZE];
	static int buffer_index;
	static int buffer_size_read;
	char *new_lineptr;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	line_length = 0;
	buffer_size = (ssize_t)(*n);
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buffer_index >= buffer_size_read)
		{
			buffer_size_read = read(fileno(stream), buffer, BUFFER_SIZE);
			buffer_index = 0;
			if (buffer_size_read <= 0)
			{
				if (line_length > 0)
				{
					(*lineptr)[line_length] = '\0';
					return (line_length);
				}
				return (-1);
			}
		}	
		c = buffer[buffer_index++];
		if (line_length >= buffer_size - 1)
		{
			buffer_size *= 2;
			new_lineptr = (char *)malloc(buffer_size);
			if (new_lineptr == NULL)
				return (-1);
			_memcpy(new_lineptr, *lineptr, line_length);
			free(*lineptr);
			*lineptr = new_lineptr;
		}
		(*lineptr)[line_length++] = (char)c;

		if (c == '\n')
		{
			(*lineptr)[line_length] = '\0';
			return (line_length);
		}
	}
}

