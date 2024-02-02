#include "../../includes/minishell.h"

int	paired_quote(char *str, int i, char ch)
{
	int pair;

	pair = 0;
	while(str[i] != '\0')
	{
		if (str[i] == ch)
			pair = 1;
		if (str[i] == ' ' && pair == 1)
			break ;
		i++;
	}
	return (i);
}

void	handle_white_spaces_and_quotes(char *s, int *i, int *start)
{
	if (s[*i] == ' ')
	{
		while (s[*i] == ' ')
			(*i)++;
		*start = *i;
	}
	if (s[*i] == '\"' || s[*i] == '\'')
		*i = paired_quote(s, *i + 1, s[*i]);
}

void update_start_indexes(int *i, int *start, int *nstart)
{
	if (*nstart)
	{
		*start = *nstart;
		(*i)--;
	}
	else
		*start = *i;
}

int	count_words_and_quotes(char *s, char c)
{
	size_t	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == 34 || s[i] == 39) && s[i])
		{
			word++;
			if (s[i] == '\"' || s[i] == '\'')
				i = paired_quote(s, i + 1, s[i]) + 1;
		}
		else if (s[i] && s[i] == c)
			while (s[i] == c)
				i++;
		else
		{
			word++;
			while (s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
				i++;
		}
	}
	return (word);
}

char	*word_alloc(char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)ft_calloc((end - start) + 1, 1);
	if (word)
	{
		while (start < end)
		{
			word[i++] = s[start++];
		}
		return (word);
	}
	return (0);
}