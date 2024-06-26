/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 14:37:13 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*src/lexer/lexer.c*/
void	add_word_to_node(char *word, t_lexer **lexer);
void	add_token_to_node(char token, t_lexer **lexer);
void	add_line_to_lexer_struct(char **line_split, t_lexer **lexer);
int		lex_line(char	**line_split_quotes, t_tools *tools);
int		lexer(char *line, t_tools *tools);

/*src/lexer/lexer_utils1.c*/
int		invalid_redir_syntax(char **list);
int		is_fd_token(char *str, char c, int position);
int		check_if_token_valid(char *str, char c, int position);
int		check_if_token(char c);
void	free_lexer(t_lexer **lexer);

/*src/lexer/lexer_utils2.c*/
char	*remove_quotes(char	*str, int i);
void	remove_quotes_add_word(char *line, int start, int j, t_lexer **lexer);
void	handle_quote(char *line, int *flag, int *i, char quote);
int		check_unclosed_quotes(char *line);
void	add_temp_to_word(char *str, char **word, int start, int i);

/*src/lexer/lexer_utils3.c*/
char	get_special_char(char *str, int i);
char	*get_new_special_str(char *str);
void	check_special_chars(char **list);
int		valid_token_starter(t_lexer *lexer);
int		valid_syntax(t_lexer *lexer, t_tools *tools);

/*src/lexer/lexer_split.c*/
void	syntax_err(char token);
void	handle_characters(char *s, int *i, int *start, int flag);
char	**create_split(char *s, char **split, int nwords, int flag);
char	**lexer_split(char *s, int flag);
int		check_token_flag(char *str, int i, int flag, int position);

/*src/lexer/lexer_split_utils.c*/
int		paired_quote(char *str, int i, char ch, int flag);
void	handle_white_spaces_and_quotes(char *s, int *i, int *start, int flag);
void	update_start_indexes(int *i, int *start, int *nstart);
int		count_words_and_quotes(char *s, size_t size, int flag);
char	*word_alloc(char *s, int start, int end);

#endif