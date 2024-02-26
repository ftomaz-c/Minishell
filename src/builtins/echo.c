#include "../../includes/builtins.h"

char	first_quote_found(t_parser *command, int pos)
{
	char	quote;
	int		j;

	j = 0;
	while (command->str[pos][j])
	{
		if (command->str[pos][j] && (command->str[pos][j] == 34 
			|| command->str[pos][j] == 39))
		{
			quote = command->str[pos][j];
			return (quote);
		}
		j++;
	}
	return ('\0');
}

void	echo_n_print(t_parser *command, int	pos)
{
	int		j;
	char	first_quote;

	pos++;
	while (command->str[pos])
	{
		j = 0;
		first_quote = first_quote_found(command, pos);
		while (command->str[pos][j])
		{
			if (command->str[pos][j] == first_quote)
				j++;
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
	char	first_quote;

	while (command->str[pos])
	{
		j = 0;
		first_quote = first_quote_found(command, pos);
		while (command->str[pos][j])
		{
			if (command->str[pos][j] == first_quote)
				j++;
			if (j >= (int)ft_strlen(command->str[pos]))
				break ;
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
	global_status = EXIT_SUCCESS;
	return (global_status);
}
