#include "lexer.h"
#include "minishell.h"

void	print_list_state(t_minishell *minishell, char *name)
{
	t_cmd	*current;
	int		cmd_index;
	int		arg_index;

	current = minishell->cmd;
	cmd_index = 0;
	printf("\n*LIST STATE %s:\n", name);
	while (current != NULL)
	{
		printf("Command %d:\n", cmd_index);
		arg_index = 0;
		while (current->cmd[arg_index] != NULL)
		{
			printf(" Arg %d:\n   cmd:        %s,\n   infile:     %s,\n   outfile:    %s,\n \
  s_infiles:  %s,\n   s_oufiles:  %s,\n   is_append: %d, inpipe: %d, outpipe: %d\n", 
			   arg_index, current->cmd[arg_index], current->infile, current->outfile,
			   current->skipped_in, current->skipped_out, current->append, current->inpipe, current->outpipe);
			arg_index++;
		}
		current = current->next;
		cmd_index++;
	}
	printf("\n");
}

void	print_tokens_state(char **tokens, char *name)
{
	int	i;

	i = 0;
	printf("\n*TOKENS STATE %s:\n", name);
	while (*tokens)
		printf("  Token %d: %s\n", i++, *(tokens++));
	printf("\n");
}
