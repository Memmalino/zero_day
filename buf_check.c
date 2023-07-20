#include "shell.h"
/**
 * is_file_exists - function that check if file name is the same with input
 * @filename: the input file to check
 * Return: 0 when not found but 1 when found
 */

int is_file_exists(const char *filename)
{
	int match = 0;
	struct dirent *entry;
	DIR *dir = opendir(".");

	if (dir == NULL)
	{
		perror("Unable to open directory");
		return (0);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG && strcmp(filename, entry->d_name) == 0)
		{
			match = 1;
			break;
		}
	}

	closedir(dir);
	return (match);
}
/**
 * count_quotes - function that check for perfect quotes
 * @str: the string to work on
 * Return: void
 */
void count_quotes(char *str)
{
	int count = 0, i, k, j = 0, cndt = 0, conditionn = 0;
	int len = _strlen(str);

	for (i = 0; i < len; i++)
	{
		if (str[i] == '"' && str[i] != '\'')
		{
			conditionn = 1;
			count++;
		}
		if (str[i] == '\'' && str[i] != '"')
		{
			cndt = 1;
			count++;

		}

	}
	if (conditionn && !cndt)
	{
		if (count % 2 == 0)
		{

			for (k = 0; k < len; k++)
			{
				if (str[k] != '"')
					str[j++] = str[k];

			}

			str[j] = '\0';

		}
	}
	else if (cndt && !conditionn)
	{
		if (count % 2 == 0)
		{

			for (k = 0; k < len; k++)
			{
				if (str[k] != '\'')
					str[j++] = str[k];

			}

			str[j] = '\0';
		}
	}

}
