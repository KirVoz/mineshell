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

int	if_quote(int *in_quote, char c)
{
	if (c == '\'' || c == '\"')
		*in_quote = 1;
	return (1);
}

// char	*getting_start(char **line, char *start, int *len)
// {
// 	int		in_quote;

// 	in_quote = 0;
// 	while (**line)
// 	{
// 		if (ft_strchr(QUOTES, **line) && !in_quote)
// 		{
// 			*len = find_quotation_len(*line);
// 			*line = find_end_quote(*line, NULL);
// 			break ;
// 		}
// 		if (is_delimiter(*line))
// 		{
// 			if (*len > 0)
// 				break ;
// 			if (ft_strchr(DELIMS, **line))
// 			{
// 				*len = 1;
// 				(*line)++;
// 				break ;
// 			}
// 		}
// 		(*len)++;
// 		(*line)++;
// 	}
// 	return (start);
// }

char	*getting_token(char *start, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}

char	*find_end_quote_len(char *line, int *len)
{
	int		i;
	char	quote;

	i = 1;
	quote = *line;
	while (line[i] && line[i] != quote)
	{
		i++;
		(*len)++;
	}
	*len += 2;
	return (&(line[i + 1]));
}

char	*getting_start(char **line, char *start, int *len)
{
	int	in_token;

	in_token = 0;
	while (*line)
	{
		if (ft_strchr(QUOTES, **line))
		{
			if (*len == 0)
				*line = find_end_quote_len(*line, len);
			break ;
		}
		else if (is_delimiter(*line))
		{
			if (in_token)
				in_token = 0;
			break ;
		}
		else if (!in_token)
			in_token = 1;
		(*len)++;
		(*line)++;
	}
	return (start);
}
