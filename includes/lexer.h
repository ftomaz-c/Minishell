#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int		expand_wildcards(char **str);
int		wildcard_match(char *name, char *wildcard, int position);

/*src/lexer/lexer.c*/
void	add_word_to_node(char *word, t_lexer **lexer);
void	add_token_to_node(char token, t_lexer **lexer, t_tools *tools);
char	*remove_quotes(char	*str, int i);
void	add_line_to_lexer_struct(char **line_split, t_lexer **lexer, t_tools *tools);
int		lexer(char *line, t_tools *tools);

void	syntax_err(char token);

/*src/lexer/lexer_utils_1.c*/
int		check_if_token(char c);
void	ft_lstaddback(t_lexer **lst, t_lexer *new);
void	free_lexer(t_lexer **lexer);
void	free_list(char	**list);
int		find_next_char_position(char *str, int i, char c);

/*src/lexer/lexer_utils_2.c*/
void	handle_quote(char *line, int *flag, int *i, char quote);
int		check_unclosed_quotes(char *line);
int		check_if_token_valid(char *str, char c, int position);
void	add_temp_to_word(char *str, char **word, int start, int i);
void	remove_quotes_add_word(char *line, int start, int j, t_lexer **lexer);

/*src/lexer/lexer_utils_3.c*/
void	check_special_chars(char **list);
char	*get_new_special_str(char *str);
char	get_special_char(char *str, int i);
void	syntax_err(char token);
int		valid_syntax(t_lexer *lexer, t_tools *tools);

/*src/lexer/lexer_split.c*/
void	handle_characters(char *s, int *i, int *start);
char	**create_split(char *s, char **split, int nwords, char c);
char	**lexer_split(char *s, char c);
int		check_token_flag(char *str, int i, int flag, int position);

/*src/lexer/lexer_split_utils.c*/
int		paired_quote(char *str, int i, char ch);
void	handle_white_spaces_and_quotes(char *s, int *i, int *start);
void	update_start_indexes(int *i, int *start, int *nstart);
int		count_words_and_quotes(char *s, char c, size_t size);
char	*word_alloc(char *s, int start, int end);

/*src/lexer/expander.c*/
char	*expander(char **env, char **list, t_tools *tools);
char	*merge_list_of_strings(char **list, char *separator);

/*src/lexer/expander_utils_1.c*/
int		find_single_quote(char *str);
int		ft_isalphanum_or_underscore(int c);
int		find_char_position_new(char *str, char c);
int		get_end_position(char *str, int position);
char	*add_prefix_and_suffix(char *str, char **env, int position, int end);

/*src/lexer/expander_utils_2.c*/
char	*add_quotes(int j, char *str, char quote, char *value);
char	*add_quotes_to_value(char *str, int flagquote, int j, int i);
char	*build_str(char *value, char *prefix, char *suffix);

/*src/lexer/expander_split.c*/
int		count_char_in_str(char *str, char c);
void	init_expander(t_expander *expander);
int		realloc_split(t_expander *expander, char *str, int i);
char	**split_expander(char *str);

#endif