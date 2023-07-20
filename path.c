#include "shell.h"
#include <string.h>

/**
 * get_env - func that gets environment variable
 * @envv: pointer to an array of strings
 * @key: they string of what to look for
 * Return: pointer to the found member
 */

char *get_env(char **envv, const char *key)
{
	int i = 0;
	size_t keyLength = _strlen(key);

	while (envv[i] != NULL)
	{

		if (_strncmp(envv[i], key, keyLength) == 0 && envv[i][keyLength] == '=')
		{
			return (&envv[i][keyLength + 1]);
		}
		i++;
	}

	return (NULL);
}

/**
 * isInPath - func that checks for a command in path
 * @input: the user input to check
 * @env: the environment variables
 * Return: the path found
 */

char *isInPath(char *input, char **env)
{

	char *path = get_env(env, "PATH");
	char *token;
	char *path_command;
	char *path_copy;

	if (path == NULL)
		return (NULL);
	path_copy = _strdup(path);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		path_command = malloc(strlen(token) + _strlen(input) + 2);

		_strcpy(path_command, token);
		_strcat(path_command, "/");
		_strcat(path_command, input);

		if (access(path_command, F_OK) == 0)
		{
			free(path_copy);
			return (path_command);
		}
		free(path_command);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * path_handler - func that handle the path
 * @input: user input
 * @env: environment variables
 * Return: pointer to the absolute path of input
 */

char *path_handler(char *input, char **env)
{
	char *token;
	char *path_command;
	char *cpy = _strdup(input);

	token = strtok(cpy, " ");

	if (token == NULL)
	{
		free(cpy);
		return (NULL);
	}
	path_command = isInPath(token, env);
	if (path_command == NULL)
	{
		free(cpy);
		return (NULL);
	}
	free(cpy);
	return (path_command);
}
