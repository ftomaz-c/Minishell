/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:37:33 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/30 16:02:19 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_lexer	lexer;

	// error_check(argc, argv);
	(void)envp;
	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		add_history_file(line);
		if (!lex_line(line, &lexer))
		{
			free(line);
			return (1);	
		}
		free(line);
	}
	return (0);
}