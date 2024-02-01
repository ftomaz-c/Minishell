#include "../includes/minishell.h"

void	error_check(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		printf("Error: This program does not accept arguments\n");
		printf("Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
}
