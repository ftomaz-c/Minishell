#include "../../includes/builtins.h"

void	echo_n_print(t_parser *command, int	pos)
{
	int		j;

	pos++;
	while (command->str[pos])
	{
		j = 0;
		while (command->str[pos][j])
		{
			printf("%c", command->str[pos][j]);
			j++;
		}
		if (command->str[pos + 1])
			printf(" ");
		pos++;
	}
}

void	echo_print(t_parser *command, int pos)
{
	int		j;

	while (command->str[pos])
	{
		j = 0;
		while (command->str[pos][j])
		{
			printf("%c", command->str[pos][j]);
			j++;
		}
		if (command->str[pos][pos + 1])
			printf(" ");
		pos++;
	}
	printf("\n");
}

int	echo(t_tools *tools, t_parser *command)
{
	int	i;

	i = 1;
	(void)tools;
	if (!command->str[i])
		printf("\n");
	else if (ft_strcmp(command->str[i], "-n") == 0)
		echo_n_print(command, i);
	else
		echo_print(command, i);
	exit (EXIT_SUCCESS);
}
