#include "../includes/minishell.h"

int	g_status = 0;

void	handle_shlvl(char *pre_lvl, char **new_lvl, size_t lvl)
{
	if (!pre_lvl)
		lvl = 1;
	else
		lvl = ft_atoll(pre_lvl);
	if ((int)lvl < 0)
		*new_lvl = ft_itoa(0);
	else
		*new_lvl = ft_itoa(lvl + 1);
	if (ft_atoll(*new_lvl) > 1000)
	{	
		*new_lvl = ft_itoa(1);
		ft_putstr_fd("bash: warning: shell level (", STDERR_FILENO);
		ft_putstr_fd(ft_itoa(lvl + 1), STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to ", STDERR_FILENO);
		ft_putstr_fd(*new_lvl, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	update_env(t_tools *tools)
{
	int			i;
	size_t		lvl;
	char		*new_lvl;
	char		*pre_lvl;
	int			flag;

	i = 0;
	flag = 0;
	lvl = 0;
	while (tools->env[i])
	{
		if (strncmp("SHLVL", tools->env[i], 5) == 0)
		{
			flag = 1;
			get_new_var_value(&pre_lvl, tools->env[i]);
			handle_shlvl(pre_lvl, &new_lvl, lvl);
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("SHLVL=", new_lvl);
			free(pre_lvl);
			free(new_lvl);
		}
		i++;
	}
	if (!flag)
		export_variable_to_env(tools, "SHLVL=1");
}


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	update_history(".minishell_history");
	error_check(argc, argv);
	if (!config_tools(&tools, envp))
	{
		printf ("Error: Failed to allocate memory for tools\n");
		free_tools(&tools);
		exit (EXIT_FAILURE);
	}
	update_env(&tools);
	while (1)
	{
		//line = prompt_line(&tools);
		line = readline(".minishell: ");
		add_history_file(line, ".minishell_history");
		if (check_unclosed_quotes(line))
		{
			if (!lex_line(line, &tools))
			{
				free(line);
				// free_tools(&tools);
				free_lexer(&tools.lexer);
				// g_status = 2;
				continue ;
			}
			// print_lexer(&tools);

			parser(&tools);

			// print_parser(&tools);

			if (tools.lexer)
				free_lexer(&tools.lexer);
			if (tools.parser)
			{
				executor(&tools);
				free_parser(&tools.parser);
			}
		}
		else
			printf("Error: input with unclosed quotes\n");
		free(line);
		if (tools.exit)
			break ;
	}
	free_tools(&tools);
	exit (g_status);
}
