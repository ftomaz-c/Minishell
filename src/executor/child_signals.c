#include "../../includes/executor.h"

void	eof_sig_msg_exit(t_tools *tools, char *line)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(tools->nprompts, 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(here_doc_struct()->heredoc_limiter, 2);
	ft_putstr_fd("')\n", 2);
	free(here_doc_struct()->heredoc_limiter);
	close(here_doc_struct()->fd[1]);
	free(line);
	exit (g_status);
}

void	ignore_sig_pipex(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		g_status = 130;
		close(STDIN_FILENO);
	}
}

void	sig_pipex_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	here_doc_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		g_status = 130;
		close(STDIN_FILENO);
	}
}

void	handle_pipex_heredoc(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}

void	handle_pipex_sigaction(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
