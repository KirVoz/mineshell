#include "minishell.h"

void	*ft_realloc_exe(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

char	*str_to_lower(char *str)
{
	char	*lower_str;
	int		i;

	lower_str = allocate_dup(str, "Lower_str in str_to_lower");
	i = 0;
	while (lower_str[i])
	{
		lower_str[i] = ft_tolower(lower_str[i]);
		i++;
	}
	return (lower_str);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}
