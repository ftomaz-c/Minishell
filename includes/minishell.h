/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:38:16 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/31 19:16:54 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_lexer
{
	char	*words;
	char	*token;
	int		i;
	struct	s_lexer *next;
	struct	s_lexer *pre;
}	t_lexer;

/*history.c*/
void    add_history_file(char *line);
int 	count_lines_in_file(const char *filename);

/*lexer*/
int	lex_line(char *line, t_lexer *lexer);
int		check_if_token(char c);

/*lexer utils*/
int		count_words_quotes(char *s, char c);
char	*word_alloc(char *s, int start, int end);
char	**create_split(char *s, char **split, int nwords, char c);
char	**ft_split_quotes(char *s, char c);
#endif