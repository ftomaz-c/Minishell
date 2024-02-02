#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char	*words;
	char	*token;
	int		i;
	struct	s_lexer *next;
	struct	s_lexer *pre;
}	t_lexer;

/*lexer*/
int		lex_line(char *line, t_lexer *lexer, char **envp);

/*lexer utils*/
int		check_if_token(char c);
void	init_lexer(t_lexer *lexer);
int		exit_simple_error(char *msg);

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
void	expander(char **list, char **env);

#endif