#include "shell.h"

char** copy_environ()
{
	/* Count the number of elements in the 'environ' array */
	int env_count = 0;
	int i;
	size_t len;
	char **new_environ;

	while (environ[env_count] != NULL) {
		env_count++;
	}

	/* Allocate memory for the new environment array */
	new_environ = (char**)malloc((env_count + 1) * sizeof(char*));

	if (new_environ == NULL) {
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	/* Copy each string in 'environ' to the new array */
	for (i = 0; i < env_count; i++) {
		len = strlen(environ[i]) + 1; /* +1 for the null terminator */
		new_environ[i] = (char*)malloc(len);
		if (new_environ[i] == NULL) {
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		strcpy(new_environ[i], environ[i]);
	}

	new_environ[env_count] = NULL; /* Set the last element of the new array to NULL */

	return new_environ;
}
