/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/26 22:58:24 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Displays a warning message when a here-document is delimited by 
 * end-of-file.
 * 
 * @param tools Pointer to the tools structure containing necessary data such
 * as the number of prompts.
 * @param line The line being processed.
 * @param delimiter The delimiter expected for the here-document.
 */
void	eof_sig_msg(t_tools *tools, char *line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(tools->nprompts, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	free(line);
}

/**
 * @brief Signal handler for here-document, handles SIGINT to interrupt the
 * process.
 * 
 * @param sig The signal number received.
 */
void	here_doc_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		global_status()->nbr = 130;
		close(STDIN_FILENO);
	}
}

/**
 * @brief Signal handler for child processes, handles SIGINT and SIGQUIT.
 * 
 * @param sig The signal number received.
 */
void	child_handler(int sig)
{
	rl_on_new_line();
	if (sig == SIGINT)
		global_status()->nbr = 130;
	else if (sig == SIGQUIT)
		global_status()->nbr = 131;
}

/**
 * @brief Sets up signal handlers for child processes to handle SIGINT and
 * SIGQUIT.
 */
void	handle_child_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = child_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction (SIGQUIT, &sa, NULL);
}

/**
 * @brief Sets up signal handlers for here-document processing to handle SIGINT
 * and ignore SIGQUIT.
 */
void	handle_heredoc_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = here_doc_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
