#include "lexer.h"
#include "minishell.h"

size_t	strlcpy_eq(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	copy_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	copy_len = dstsize - 1;
	if (copy_len > src_len)
		copy_len = src_len;
	ft_memcpy(dst, src, copy_len);
	dst[copy_len] = '=';
	dst[copy_len + 1] = '\0';
	return (src_len);
}

size_t	expanded_env_var_len(char *line)
{
	int	len;

	len = 0;
	while (*line && *line != '\n')
	{
		len++;
		line++;
	}
	return (len);
}

char	*allocate_env_value(char *value)
{
	char	*env_value;

	env_value = ft_strdup(value);
	if (!env_value)
		exit_fail("Memory allocation for env_value failed.");
	return (env_value);
}

char	set_quote(char c, int *in_quote)
{
	*in_quote = 1;
	return (c);
}

int	dollar_special_case(char **token)
{
	if (**token == '$')
	{
		if (*(*token + 1) && *(*token + 1) == '?')
		{
			free(*token);
			*token = ft_strdup("$?"); //rewrite
			return (0);
		}
		if (!*(*token + 1))
			return (0);
		if (*(*token + 1) && *(*token + 1) == '$')
			return (1);
		if (**token == '$')
			return (1);
		if (!*(*token + 1))
			return (1);
	}
	return (0);
}
