#include "../includes/libft.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int len = 0;

	while (s2[len] != '\0')
	{
		s1[len] = s2[len];
		len++;
	}	
	s1[len] = '\0';

	return (s1);	
}
