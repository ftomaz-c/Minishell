#include "../../includes/parser.h"

void	handle_and_opertor(t_parser *current, int *start)
{
	if (current && current->token == '&' && current->next && current->next->token == '&')
	{
		int pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			tools->parser->special_operator = 1;
			return (1);
		}
		else
		{
			int	status;
			wait_status(pid, &status);
			if (g_status)
			{
				current = current->next;
				start++;
				while (current && ((current->token != '&' && current->next && current->next->token != '&')
				|| (current->token != '|' && current->next && current->next->token != '|')))
				{
					current = current->next;
					start++;
				}
				if (current->next == NULL)
				{
					free_lexer(&tools->lexer);
					free_parser(&tools->parser);
					return (0);
				}
				continue ;
			}
			current = current->next;
			start++;
		}
	}
}

void	handle_or_opertor(t_parser *current, int *start)
{
	if (current && current->token == '|' && current->next && current->next->token == '|')
	{
		int pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			tools->parser->special_operator = 1;
			return (1);
		}
		else
		{
			int	status;
			wait_status(pid, &status);
			free_parser(&tools->parser);
			tools->parser = NULL;
			if (!g_status)
			{
				current = current->next;
				start++;
				while (current && current->token != '&' && current->next && current->next->token != '&')
				{
					current = current->next;
					start++;
				}
				if (current->next == NULL)
				{
					free_lexer(&tools->lexer);
					free_parser(&tools->parser);
					return (0);
				}
				continue ;
			}
			current = current->next;
			start++;
		}
	}
}