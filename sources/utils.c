# include "minishell.h"

void	exit_fail(const char *exit_message)
{
	perror(exit_message);
	exit(EXIT_FAILURE);
}