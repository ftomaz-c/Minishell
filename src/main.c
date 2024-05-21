/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/21 19:30:34 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char	*line;

	line = NULL;
	config_tools(&tools, envp);
	update_history(&tools, ".minishell_history");
	error_check(argc, argv);
	while (1)
	{
		handle_sigaction();
		if (!isatty(STDIN_FILENO))
			non_interactive_mode(&tools, line);
		else
			interactive_mode(&tools, line);
		if (tools.exit)
			break ;
	}
	free_and_exit(&tools, g_status);
	return (0);
}
