#include "lexer.h"
#include "minishell.h"

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
