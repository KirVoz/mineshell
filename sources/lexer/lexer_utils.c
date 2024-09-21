#include "lexer.h"
#include "minishell.h"

char	*quote_counter(char *line)
{
	int		double_q;
	int		single_q;
	char	*line_cpy;

	double_q = 0;
	single_q = 0;
	line_cpy = line;
	while (*line_cpy)
	{
		if (ft_strchr("\"", *line_cpy))
			double_q++;
		else if (ft_strchr("\'", *line_cpy))
			single_q++;
		line_cpy++;
	}
	if (double_q % 2 != 0)
		return ("\"");
	else if (single_q % 2 != 0)
		return ("'");
	return (NULL);
}

char	hanging_pipe_heredoc(char *line)
{
	if (ft_strchr(line, '<')
			&& ft_strncmp(ft_strchr(line, '<'), "<<", 2) == 0
			&& ft_strncmp(ft_strchr(line, '<') + 2, "<", 1) != 0)
		return ('h');
	else if (ft_strrchr(line, '|')
			&& !(*(ft_strrchr(line, '|') + 1)))
		return ('p');
	return (0);
}
