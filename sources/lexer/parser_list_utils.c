#include "lexer.h"
#include "minishell.h"

t_cmd	*ft_mini_lstnew(char **content)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_mini_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}
