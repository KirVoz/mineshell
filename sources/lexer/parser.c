#include "lexer.h"
#include "minishell.h"

void	init_command(t_minishell *minishell)
{
	minishell->cmd->cmd = 0;
	minishell->cmd->in_file = 0;
	minishell->cmd->out_file = 0;
}

char	*ft_strjoin_parser(char const *s1, char const *s2)
{
	int		join_i;
	int		source_i;
	int		len_s1;
	int		len_s2;
	char	*joined_str;

	if (!s1 || !s2)
		return (NULL);
	join_i = 0;
	source_i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined_str = (char *)malloc(len_s1 + len_s2 + 2);
	if (!joined_str)
		return (NULL);
	while (join_i < len_s1)
		joined_str[join_i++] = s1[source_i++];
	joined_str[join_i++] = ' ';
	source_i = 0;
	while (join_i < len_s1 + len_s2 + 1)
		joined_str[join_i++] = s2[source_i++];
	joined_str[join_i] = '\0';
	return (joined_str);
}

void	parser(t_minishell *minishell, char **tokens)
{
	char *res;
	char *temp;

	init_command(minishell);
	while (*tokens)
	{
		res = ft_strdup("");
		if (!res)
			exit(1);
		while (*tokens && !ft_strchr(DELIMS, **tokens))
		{
			temp = ft_strjoin_parser(res, *tokens);
			free(res);
			res = temp;
			tokens++;
		}
		if (*res)
			ft_lstadd_back(&minishell->cmd->cmd, ft_lstnew(res));
		else
			free(res);
		if (*tokens)
		{
			tokens++;
			minishell->cmd->out_file = 1;
		}
	}
}