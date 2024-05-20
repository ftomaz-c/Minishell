#include "../../includes/minishell.h"

void	close_sig_exit(t_tools *tools, int status)
{
	int	i;

	i = 2;
	while (i < 1024)
		close(i++);
	dup2(tools->original_stdin, STDIN_FILENO);
	close(tools->original_stdin);
	free_parser(&tools->parser);
	free_tools(tools);
	exit (status);
}

void	ignore_sig_handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		printf("\n");
	}
}

void	react_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	handle_sigaction(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
