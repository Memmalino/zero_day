#include "shell.h"

/**
 * main - the main function
 * @argc: the argument count plus the ame of file
 * @argv: arrays of arguments and name of file
 * Return: 0 on succes
 */
int main(int argc, char **argv)
{
	size_t n = 0;
	char *buf  = NULL;
	char *fnm = argv[0];
	char **tkn = NULL;
	char *path = NULL;
	(void)argc;

	while (ON)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
		if (getline(&buf, &n, stdin) == -1)
			break;
		buf[_strcspn(buf, "\n")] = '\0';
		if (_strlen(buf) == 0)
			continue;
		if (_white(buf) == 1)
			continue;
		count_quotes(buf);
		if (_strncmp(buf, "exit", 4) == 0)
		{
			if(buf[4] == ' ' || buf[4] == '\0')
				builtins(buf, fnm);
		}
		if (_contains_pipe(buf) == 1)
			handle_pipe(buf);
		else
		{
			tkn = tokenie(buf, " ");
			path = path_handler(tkn[0], environ);
		if (path == NULL)
		{
			path = _strdup(tkn[0]);
			execute_command(tkn, path, "fork");
		}

			else
				execute_command(tkn, path, "fork");
			free(path);
			free_func(tkn);
		}
	}
	free(buf);
	return (0);

}
