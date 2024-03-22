#include "../../includes/minishell.h"

int	count_char_in_str(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	init_expander(t_expander *expander)
{
	expander->size = 1;
	expander->index = 0;
	expander->start = 0;
	expander->split = ft_calloc(expander->size, sizeof(char *));
}

int	realloc_split(t_expander *expander, char *str, int i)
{
	expander->size++;
	expander->split = ft_realloc(expander->split, expander->size * \
	sizeof(char *), (expander->size - 1) * sizeof(char *));
	if (!expander->split)
	{
		free_list(expander->split);
		return (0);
	}
	if (str[expander->start] == '$' && (str[expander->start + 1] == '\"'
			|| str[expander->start + 1] == '\''))
		expander->start++;
	expander->split[expander->index] = ft_substr(str, expander->start, \
	i - expander->start + 1);
	if (!expander->split[expander->index])
	{
		free_list(expander->split);
		return (0);
	}
	expander->start = i + 1;
	expander->index++;
	return (1);
}

char	**split_expander(char *str)
{
	t_expander	expander;
	int			i;

	if (!count_char_in_str(str, '$'))
		return (NULL);
	init_expander(&expander);
	i = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '\'')
		{
			expander.start = i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] && (str[i + 1] == '\'' || str[i + 1] == '\0'
				|| str[i] == '\''))
		{
			if (!realloc_split(&expander, str, i))
				return (NULL);
		}
		i++;
	}
	expander.split[expander.index] = NULL;
	return (expander.split);
}
