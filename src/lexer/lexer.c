
#include "../../includes/minishell.h"

int	last_token(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		if (check_if_token(str[i]))
			c = i;
		i++;
	}
	return (c);
}
void	ft_lstaddback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	add_word_to_node(char *word, int start, int end, t_lexer **lexer)
{
	t_lexer	*node;
	char	*segment;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	segment = ft_substr(word, start, end);
	node->words = segment;
	node->token = '\0';
	node->next = NULL;
	node->pre = NULL;
	ft_lstaddback(lexer, node);
	free(segment);
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
	node->next = NULL;
	ft_lstaddback(lexer, node);
}

void	split_word_to_nodes(char *word, int start, int position, t_lexer **lexer)
{
	// int	i;
	// char	token;

	// i = 0;
	// token = word[position];
	add_word_to_node(word, start, position, lexer);
	add_token_to_node(word[position], lexer);
	// if (ft_strlen(word) > position)
	// {
	// 	position++;
	// 	while (word[position])
	// 	{	
	// 		if (check_if_token(word[position]))
	// 			split_word_to_nodes(word, position, lexer);


	// 	}
	// }
}

void	add_line_to_lexer_struct(char **line_split, t_lexer **lexer)
{
	int	i;
	int	j;
	int	start;
	int	last_token_position;

	i = 0;
	while (line_split[i])
	{
		j = 0;
		start = 0;
		last_token_position = last_token(line_split[i]);
		printf("here\n");
		while (line_split[i][j])
		{
			if (check_if_token(line_split[i][j]))
			{	
				split_word_to_nodes(line_split[i], start, j, lexer);
				start = j++;
			}
			else
				j++;
		}
		if (j > last_token_position)
			add_word_to_node(line_split[i], last_token_position + 1, j, lexer);
		i++;
	}
}

int	lex_line(char *line, t_lexer **lexer, char **envp)
{
	char	**line_split_quotes;

	init_lexer(*lexer);
	line_split_quotes = lexer_split(line, ' '); // splits quotes considering the quotes present
	// line_split_tokens = 
	// add_line_to_lexer_struct(line_split, lexer); // next step -> separate words from the tokens found
	
	// 					Uncomment section bellow to see splitted line
	expander(line_split_quotes, envp);
	printf("here\n");
	add_line_to_lexer_struct(line_split_quotes, lexer);
	int	i = 0;
	while (line_split_quotes[i])
	{
		printf("word: %s\n", line_split_quotes[i]);
		free(line_split_quotes[i]);
		i++;
	}
	free(line_split_quotes);
	return (1);
}
