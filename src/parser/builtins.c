#include "../../includes/parser.h"

int	echo(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	cd(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	pwd(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	export(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	unset(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	env(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	mini_exit(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	(*is_builtin(char *str))(t_tools *tools, t_parser *parser)
{
	static struct {
		char	*name;
		int		(*builtin)(t_tools *, t_parser *);
    } builtin_array[] = {
        {"echo", echo},
        {"cd", cd},
        {"pwd", pwd},
        {"export", export},
        {"unset", unset},
        {"env", env},
        {"exit", mini_exit}
    };
	size_t		i;

	i = 0;
	while (i < (sizeof(builtin_array) / sizeof(builtin_array[0])))
	{
		if (ft_strncmp(builtin_array[i].name, str, ft_strlen(builtin_array[i].name)) == 0)
			return (builtin_array[i].builtin);
		i++;
	}
	return (NULL);
}