#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char			*words;
	char			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

/*lexer*/
int		lex_line(char *line, t_lexer **lexer);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	add_word_to_node(char *word, int start, int end, t_lexer **lexer);
void	add_token_to_node(char token, t_lexer **lexer);
void	add_line_to_lexer_struct(char **line_split, t_lexer **lexer);

/*lexer utils*/
int		check_if_token(char c);
void	ft_lstaddback(t_lexer **lst, t_lexer *new);
void	free_list(char	**list);
void	free_lexer(t_lexer **lexer);

/*lexer_split.c*/
char	**lexer_split(char *s, char c);
char	**create_split(char *s, char **split, int nwords, char c);

/*lexer_split_utils.c*/
char	*word_alloc(char *s, int start, int end);
int		count_words_and_quotes(char *s, char c);
void	update_start_indexes(int *i, int *start, int *nstart);
void	handle_white_spaces_and_quotes(char *s, int *i, int *start);
int		paired_quote(char *str, int i, char ch);

/*expander.c*/
void	expander(char **list);

#endif