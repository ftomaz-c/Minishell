/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 14:36:46 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Executes the minishell.
 * 
 * This function handles the execution of the minishell. It adds the input line
 * to the history file, checks for unclosed quotes, lexes the input line,
 * parses it, and executes the parsed commands using the executor.
 * 
 * @param tools A pointer to the tools structure containing
 * environment variables and history information.
 * @param line The input line to be executed.
 * @return None.
 */
void	minishell(t_tools *tools, char *line)
{
	tools->nprompts++;
	add_history_file(tools, line, ".minishell_history");
	if (check_unclosed_quotes(line))
	{
		if (!lexer(line, tools))
		{
			free_lexer(&tools->lexer);
			return ;
		}
		//print_lexer(tools);
		if (!parser(tools))
			return ;
		// print_parser(tools);
		if (tools->lexer)
			free_lexer(&tools->lexer);
		if (tools->parser)
		{
			executor(tools);
			free_parser(&tools->parser);
		}
	}
	else
		ft_putstr_fd("minishell: input with unclosed quotes\n", STDERR_FILENO);
}

/**
 * @brief Handles non-interactive mode execution.
 * 
 * This function handles the execution of the minishell
 * in non-interactive mode.
 * It reads lines from standard input, trims them, executes 
 * them using the minishell,
 * and then frees the memory allocated for the lines.
 * 
 * @param tools A pointer to the tools structure containing environment 
 * variables and line count information.
 * @param line The input line read from standard input.
 * @return None.
 */
void	non_interactive_mode(t_tools *tools, char *line)
{
	int		n;
	int		i;
	char	*tmp;

	n = 0;
	tools->lines = ft_calloc(sizeof(char **), 1024);
	tools->nint_mode = 1;
	line = get_next_line(0);
	while (line)
	{
		tmp = ft_strtrim(line, "\n");
		tools->lines[n] = ft_strdup(tmp);
		n++;
		free(line);
		free(tmp);
		line = get_next_line(0);
	}
	i = 0;
	while (i < n)
	{
		tools->line_count++;
		minishell(tools, tools->lines[i++]);
	}
	tools->exit = 1;
}

/**
 * @brief Handles interactive mode execution.
 * 
 * This function handles the execution of the minishell in interactive mode.
 * It prompts the user for input, executes the input line using the minishell,
 * and then frees the memory allocated for the input line.
 * 
 * @param tools A pointer to the tools structure containing 
 * environment variables and line count information.
 * @param line The input line provided by the user.
 * @return None.
 */
void	interactive_mode(t_tools *tools, char *line)
{
	prompt_line(tools);
	// line = readline (tools->prompt);
	line = readline(".minishell: ");
	free(tools->prompt);
	if (!line)
	{
		tools->exit = 1;
		ft_putstr_fd("exit\n", STDIN_FILENO);
		return ;
	}
	minishell(tools, line);
	free(line);
}
