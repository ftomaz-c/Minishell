/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/23 00:05:14 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	eof_sig_msg_exit(t_tools *tools, char *line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(tools->nprompts, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	free(line);
	free_and_exit(tools, EXIT_SUCCESS);
}

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

void	child_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	global_status()->nbr = 130;
}

void	handle_child_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = child_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction (SIGQUIT, &sa, NULL);
}

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
