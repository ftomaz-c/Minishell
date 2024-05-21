#include "../../includes/minishell.h"

void	free_and_exit(t_tools *tools, int status)
{
	int	i;

	i = 3;
	while (i < 1024)
		close(i++);
	free_parser(&tools->parser);
	free_tools(tools);
	exit (status);
}

void	ignore_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_status = 130;
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
		g_status = 130;
	}
	return ;
}

void	handle_sigaction(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
