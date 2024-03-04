#include "../../includes/lexer.h"

char	get_special_char(char *str, int i)
{
	if (str[i + 3] == 't')
		return ('\t');
	else if (str[i + 3] == 'n')
		return ('\n');
	else if (str[i + 3] == 'r')
		return ('\r');
	return (0);
}

char	*get_new_special_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '$' && str[i])
		new_str[j++] = str[i++];
	if (str[i] == '$')
	{
		new_str[j] = get_special_char(str, i);
		if (!new_str[j])
		{
			free(str);
			return (NULL);
		}
		i += 5;
		j++;
	}
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	return (new_str);
}

void	check_special_chars(char **list)
{
	size_t	position;
	int		index;
	char	*str;
	size_t	size;

	index = 0;
	while (list[index])
	{
		size = ft_strlen(list[index]);
		if (size > 4) 
		{
			position = find_char_position_new(list[index], '$');
			if (position < size && list[index][position + 1] == '\''
			&& list[index][position + 2] == '\\' && list[index][position + 4] == '\'')
			{
				str = get_new_special_str(list[index]);
				if (!str)
					break;
				free(list[index]);
				list[index] = str;
			}
		}
		index++;
	}
}