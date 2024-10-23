#include "lexer.h"
#include "minishell.h"
#include <stdio.h>

void	print_visible(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == ' ')
		{
			printf("\\ws");
		}
		else if (strcmp(str, "") == 0)
		{
			printf("\\es");
		}
		else
		{
			putchar(*str);
		}
		str++;
	}
	if (*str == '\0')
		printf("\\0");
	// printf("\n");
}

void	print_list_state_v(t_minishell *minishell, char *name)
{
	t_cmd	*current;
	int		cmd_index;
	t_list	*files;

	current = minishell->cmd;
	cmd_index = 0;
	printf("\n*LIST STATE %s:\n", name);
	while (current != NULL)
	{
		printf("Command %d:\n", cmd_index);
		for (int arg_index = 0; current->cmd[arg_index] != NULL; arg_index++)
		{
			printf(" Arg %d:\n   cmd:         ", arg_index);
			print_visible(current->cmd[arg_index]);
			printf("\n   whitespace:  %d\n",
			current->whitespace[arg_index]);
			printf("\n");
		}

		files = current->files;
		printf(" Redirects: ");
		int j = 0;
		while (files != NULL)
		{
			printf("\n");
			printf("   filename[%d]: ", j);
			print_visible((char *)files->filename);
			printf("\n");
			printf("       mode[%d]: %c", j, files->mode);
			j++;
			files = files->next;
		}
		printf("\n");
		for (int i = 0; current->heredoc && current->heredoc[i]; i++)
		{
			printf("   heredoc: ");
			print_visible(current->heredoc[i]);
			printf("\n");
		}
		current = current->next;
		cmd_index++;
	}
	printf("\n");
}

void	print_tokens_state_v(t_minishell *minishell, char **tokens, char *name, char mode)
{
	int	i;

	i = 0;
	printf("\n*TOKENS STATE %s:\n", name);
	while (*tokens)
	{
		printf(" Token %d: ", i);
		print_visible(*(tokens++));
		printf(" ws: %d", minishell->tmp->ws_tmp[i]);
		printf("\n");
		if (mode == 'w')
			printf(" W-space: %d\n", minishell->tmp->ws_tmp[i]);
		i++;
	}
	printf("\n");
}
