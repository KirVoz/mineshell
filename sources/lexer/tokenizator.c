#include "lexer.h"
#include "minishell.h"

char	*extract_token(char **line)
{
	char	*start;
	char	*token;
	int		len;

	start = *line;
	len = 0;
	start = getting_start(line, start, &len);
	token = getting_token(start, len);
	while (**line && **line == ' ')
		(*line)++;
	return (token);
}

char	*getting_start(char **line, char *start, int *len)
{
	while (**line)
	{
		if (ft_strchr(QUOTES, **line))
		{
			*len = find_quotation_len(*line);
			*line = find_end_quote(*line, NULL);
			break ;
		}
		if (is_delimiter(*line))
		{
			if (*len > 0)
				break ;
			if (ft_strchr(DELIMS, **line))
			{
				*len = 1;
				(*line)++;
				break ;
			}
		}
		(*len)++;
		(*line)++;
	}
	return (start);
}

char	*getting_token(char *start, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}
