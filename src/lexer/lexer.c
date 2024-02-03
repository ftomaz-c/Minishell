
#include "../../includes/minishell.h"

void	add_word_to_node(char *word, int start, int end, t_lexer **lexer)
{
	t_lexer	*node;
	char	*segment;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	segment = ft_substr(word, start, end - start);
	if (!segment)
	{
		free(node);
		return;
	}
	node->words = segment;
	node->token = '\0';
	node->next = NULL;
	node->pre = NULL;
	ft_lstaddback(lexer, node);
}

void	add_token_to_node(char token, t_lexer **lexer)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	node->words = NULL;
	node->token = token;
	node->next = NULL;
	node->pre = NULL;
	ft_lstaddback(lexer, node);
}

void add_line_to_lexer_struct(char **line_split, t_lexer **lexer)
{
	int i = 0;
	while (line_split[i] != NULL)
	{
		int j = 0;
		int start = 0;
		while (line_split[i][j] != '\0')
		{
			if (check_if_token(line_split[i][j]))
			{
				if (start < j)
					add_word_to_node(line_split[i], start, j, lexer);
				add_token_to_node(line_split[i][j], lexer);
				start = j + 1;
			}
			j++;
		}
		if (start < j)
			add_word_to_node(line_split[i], start, j, lexer);
		i++;
	}
}

//                   AUXILIARY FUNCTIONS TO PRINT THE LIST AND COUNT NUMBER OF NODES

// void print_lexer(t_lexer **lexer)
// {
// 	t_lexer *current = *lexer;
// 	while (current != NULL)
// 	{
// 		if (current->words != NULL)
// 			printf("Word: %s\n", current->words);
// 		else //if (current->token != '\0') // if i change to else if, the first Token node doesn't show
// 			printf("Token: %c\n", current->token);
// 		current = current->next;
// 	}
// }

// int count_nodes(t_lexer *lexer)
// {
// 	int count = 0;
// 	t_lexer *current = lexer;

// 	while (current != NULL)
// 	{
// 		count++;
// 		current = current->next;
// 	}
// 	return (count);
// }

// ------------------------------------------------------------------------------------------------------------------

int	lex_line(char *line, t_lexer **lexer, char **envp)
{
	char	**line_split_quotes;

	init_lexer(lexer);
	line_split_quotes = lexer_split(line, ' ');
	expander(line_split_quotes, envp);
	add_line_to_lexer_struct(line_split_quotes, lexer);

	// ----------------     Uncomment section bellow to see splitted line   ------------------------------------------
	int	i = 0;
	while (line_split_quotes[i])  // To see the splitted and expanded array
	{
		printf("word: %s\n", line_split_quotes[i]);
		free(line_split_quotes[i]);
		i++;
	}

	printf("\n"); // To separate the splited array from the final structure

	int num_nodes = count_nodes(*lexer);
	printf("Number of nodes: %d\n", num_nodes);  // To see how many nodes were created. NOTE: It has 1 extra
	print_lexer(lexer); // To see what's in each node in the list

	free(line_split_quotes);
	return (1);
}
