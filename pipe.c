#include "shell.h"
/**
 * handle_pipe - function that handle chaining command with pipe
 * @input: the input of the user
 * return: return void
 */
void handle_pipe(char *input)
{
	char **commands = NULL;
	int i = 0, status;
	int pipe_fd[2];
	int fd_in = 0;
	char **tkk = NULL, *patt = NULL;
	pid_t pid;

	commands = tokenie(input, "|");
	while (commands[i] != NULL)
	{
		pipe(pipe_fd); /* Create a pipe */
		pid = fork();
		if (pid == 0)
		{ /* Child process */
			close(pipe_fd[0]); /* Close the read */
			if (commands[i + 1] != NULL)
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (i > 0)
				dup2(fd_in, STDIN_FILENO);
			tkk = tokenie(commands[i], " ");
			patt = path_handler(tkk[0], environ);
			if (patt != NULL)
				execute_command(tkk, patt, "nofork");
			if (patt == NULL)
			{
				patt = _strdup(tkk[0]);
				execute_command(tkk, patt, "nofork");
			}
			free_func(commands);
			exit(1);
		}
		else
		{ /* Parent process */
			close(pipe_fd[1]); /* Close the write end of the pipe */
			waitpid(pid, &status, 0); /* Wait for the child process to finish */
			fd_in = pipe_fd[0]; /* Set the input for the next command */
		}
		i++;
	}
	free_func(commands);
}

