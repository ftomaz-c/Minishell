#include "../../includes/lexer.h"

int	wildcard_match(char *name, char *wildcard, int position)
{
	char	*prefix;
	char	*suffix;
	char	*middle;
	int		i;
	int		j;
	char	*c;
	int		is_wild;
	int		next_wild;

	prefix = NULL;
	suffix = NULL;
	middle = NULL;
	is_wild = 0;
	next_wild = find_next_char_position(wildcard, position + 1, '*');
	if (position != 0 && next_wild > (int)ft_strlen(wildcard) - 1)
		prefix = ft_substr(wildcard, 0, position);
	if (position != (int)ft_strlen(wildcard) - 1 && next_wild > (int)ft_strlen(wildcard) - 1)
		suffix = ft_substr(wildcard, position + 1, ft_strlen(wildcard));
	if (next_wild && next_wild < (int)ft_strlen(wildcard))
		middle = ft_substr(wildcard, position + 1, next_wild - position - 1);
	if (!prefix && !suffix && !middle)
		return (1);
	if (prefix && ft_strncmp(name, prefix, ft_strlen(prefix)) == 0)
		is_wild = 1;
	if (suffix)
	{
		i = ft_strlen(name) - ft_strlen(suffix);
		j = 0;
		while (name[i] && suffix[j] && name[i] == suffix[j])
		{
			i++;
			j++;
		}
		if (!name[i] && !suffix[j])
			is_wild = 1;
		else
			is_wild = 0;
	}
	if (middle)
	{
		j = 0;
		while (1)
		{
			c = ft_strchr(name + j, middle[0]);
			i = 0;
			while (c && i < (int)ft_strlen(middle) && middle[i] && c[i] == middle[i])
			{
				i++;
				j++;
			}
			if (!middle[i])
			{
				is_wild = 1;
				break;
			}
			else if (!c)
			{
				is_wild = 0;
				break;
			}
			while (name[j] != c[0] && name[j] && c[0])
				j++;
		}
	}
	free(prefix);
	free(suffix);
	free(middle);
	return (is_wild);
}

int	expand_wildcards(char **str)
{
	DIR				*dir;
	struct dirent	*entry;
	int				index;
	char			*new_str;
	char			*d_name;
	char			*tmp;
	int				position;
	char			*wild;

	index = 0;
	while (str[index] && !ft_strchr(str[index], '*'))
		index++;
	if (str[index] && ft_strchr(str[index], '*'))
	{
		wild = ft_strdup(str[index]);
		dir = opendir(".");
		new_str = ft_strdup("");
		while ((entry = readdir(dir)) != NULL)
		{
			position = find_char_position(wild, '*');
			if (wildcard_match(entry->d_name, wild, position) && entry->d_name[0] != '.')
			{
				d_name = add_quotes_to_value(entry->d_name, 2, 1, 0);
				tmp = ft_strjoin(new_str, d_name);
				free(new_str);
				new_str = ft_strjoin(tmp, " ");
				free(tmp);
				free(d_name);
			}
		}
		free(str[index]);
		str[index] = ft_strdup(new_str);
		free(new_str);
		if (!str[index][0])
		{
			ft_putstr_fd(str[0], STDERR_FILENO);
			ft_putstr_fd(": cannot access '", STDERR_FILENO);
			ft_putstr_fd(wild, STDERR_FILENO);
			ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
			free(wild);
			closedir(dir);
			return (0);
		}
		free(wild);
		closedir(dir);
	}
	return (1);
}
