#include "lexer.h"
#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

char	**array_init(void)
{
	char	**empty_array;

	empty_array = (char **)malloc(2 * sizeof(char *));
	if (!empty_array)
		exit_fail("Failed to allocate memory for empty command");
	empty_array[0] = ft_strdup("");
	empty_array[1] = NULL;
	return (empty_array);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
