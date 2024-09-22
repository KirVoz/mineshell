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

char	*env_var_copy(char **token)
{
	char	*variable_name;
	char	*c_token;
	size_t	var_len;

	var_len = 0;
	(*token)++;
	c_token = *token;
	while (**token && !(**token == ' ' || **token == '"' || **token == '\''))
	{
		var_len++;
		(*token)++;
	}
	variable_name = (char *)malloc((var_len + 2) * sizeof(char));
	if (!variable_name)
		exit_fail("Memmory allocation for variable_name failed.");
	strlcpy_eq(variable_name, c_token, var_len + 1);
	return (variable_name);
}

char	set_quote(char c, int *in_quote)
{
	*in_quote = 1;
	return (c);
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

size_t	expanded_line_len(t_minishell *minishell, char *token)
{
	char	current_quote;
	size_t	len;
	int		in_quote;

	current_quote = 0;
	len = 0;
	in_quote = 0;
	while (*token)
	{
		if ((*token == '\'' || *token == '\"') && !in_quote)
			current_quote = set_quote(*token, &in_quote);
		else if (*token == current_quote && in_quote)
			in_quote = 0;
		else if (*token == '$' && current_quote == '"'
			&& !(*(token + 1) == '"' || *(token + 1) == '\''))
		{
			len += env_value_len(minishell, &token);
			// printf("expanded_line_len %zu\n", len); //del
			continue ;
		}
		else if (*token != current_quote || in_quote)
			len++;
		token++;
	}
	return (len);
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
