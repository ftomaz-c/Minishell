#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*lexer/lexer.c*/
char	*remove_quotes(char	*str, int i);
int		lex_line(char *line, t_tools *tools);
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
void	remove_quotes_add_word(char *line_split, int start, int j, t_lexer **lexer);

/*lexer/lexer_split.c*/
void	handle_characters(char *s, int *i, int *start);
char	**lexer_split(char *s, char c);
char	**create_split(char *s, char **split, int nwords, char c);

/*lexer/lexer_split_utils.c*/
char	*word_alloc(char *s, int start, int end);
int		count_words_and_quotes(char *s, char c);
void	update_start_indexes(int *i, int *start, int *nstart);
void	handle_white_spaces_and_quotes(char *s, int *i, int *start);
int		paired_quote(char *str, int i, char ch);

/*lexer/expander.c*/
void	expander(char **env, char **list);

/*lexer/expander_utils.c*/
int		find_single_quote(char *str);
int		ft_isalphanum_or_underscore(int c);
int		find_char_position_new(char *str, char c);
int		get_end_position(char *str, int position);
char	*add_prefix_and_suffix(char *str, char **env, int position, int end);

#endif