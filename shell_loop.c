#include "main.h"


void shell_loop(char **argv, char **env)
{
	char *string = NULL;
	int i, status;
	size_t n = 0;
	ssize_t num_char;
	char *args[] = {NULL, NULL};
	pid_t child_pid;

	int loop = 1;

	while (loop)
	{
		if (isatty(STDIN_FILENO))
			write(1, "($) ", 4);

		num_char = getline(&string, &n, stdin);
		if (num_char == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (string[i])
		{
			if (string[i] == '\n')
				string[i] = 0;
			i++;
		}
		args[0] = string;
		child_pid = fork();
		if (child_pid == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execve(args[0], args, env) == -1)
			{
				write(1, argv[0], 6);
				write(1, ": No such file or directory\n", 29);
			}
		}
		else
			wait(&status);
	}
}
