#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*lexer/lexer.c*/
int		lex_line(char *line, t_tools *tools);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	add_word_to_node(char *word, int start, int end, t_lexer **lexer);
void	add_token_to_node(char token, t_lexer **lexer);
void	add_line_to_lexer_struct(char **line_split, t_lexer **lexer);

/*lexer/lexer_utils_1.c*/
int		check_if_token(char c);
void	ft_lstaddback(t_lexer **lst, t_lexer *new);
void	free_lexer(t_lexer **lexer);
void	free_list(char	**list);
int	    find_next_char_position(char *str, int i, char c);

/*lexer/lexer_utils_2.c*/
void	handle_quote(char *line, int *flag, int *i, char quote);
int		check_unclosed_quotes(char *line);
int	    check_if_token_valid(char *str, char c, int position);
void	add_temp_to_word(char *str, char **word, int start, int i);

/*lexer_split.c*/
void	handle_characters(char *s, int *i, int *start);
char	**lexer_split(char *s, char c);
char	**create_split(char *s, char **split, int nwords, char c);

/*lexer_split_utils.c*/
char	*word_alloc(char *s, int start, int end);
int		count_words_and_quotes(char *s, char c);
void	update_start_indexes(int *i, int *start, int *nstart);
void	handle_white_spaces_and_quotes(char *s, int *i, int *start);
int		paired_quote(char *str, int i, char ch);

/*expander.c*/
void	expander(char **env, char **list);

#endif