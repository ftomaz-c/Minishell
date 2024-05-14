/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:27:15 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/*src/expander/expander.c*/
int		check_conditions_expander(char *str, int position);
void	expand_split(char **env, char **split);
char	*merge_list_of_strings(char **list, char *separator);
char	*expand_tilde(char *str, char *home_var);
char	*expander(char **env, char **list, t_tools *tools);

/*src/expander/expander_utils_1.c*/
int		find_single_quote(char *str);
int		find_char_position_new(char *str, char c);
int		get_end_position(char *str, int position);
char	*add_prefix_and_suffix(char *str, char **env, int position, int end);

/*src/expander/expander_utils_2.c*/
char	*add_quotes(int j, char *str, char quote, char *value);
char	get_quote_flag(char *str, int i);
char	*add_quotes_to_value(char *str, int flagquote, int j, int i);
char	*build_str(char *value, char *prefix, char *suffix);

/*src/expander/expander_split.c*/
void	init_expander(t_expander *expander);
int		realloc_split(t_expander *expander, char *str, int i);
char	**split_expander(char *str);

#endif