#include "minishell.h"

void	exit_fail(const char *exit_message)
{
	perror(exit_message);
	exit(EXIT_FAILURE);
}

void    error_handler(t_minishell *minishell, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(error, 2);
    ft_putstr_fd("\n", 2);
    minishell->exit_code = 1;
    exit (1);
}

void    not_found(t_minishell *minishell, char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found", 2);
    ft_putstr_fd("\n", 2);
    minishell->exit_code = 127;
    // printf("structs exit code in not_found = %d\n", minishell->exit_code); //del
}

void    no_file(t_minishell *minishell, char *filename)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(filename, 2);
    ft_putstr_fd(": ", 2);
    perror("");
    minishell->exit_code = 1;
}

void    no_path_file(t_minishell *minishell, char *filename)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(filename, 2);
    ft_putstr_fd(": No such file or directory", 2);
    ft_putstr_fd("\n", 2);
    minishell->exit_code = 127;
}

void    arg_count_error(t_minishell *minishell, char *command)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": too many arguments", 2);
    ft_putstr_fd("\n", 2);
    minishell->exit_code = 1;
}

int    syntax_error(t_minishell *minishell, char *token)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd("syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
    minishell->exit_code = 258;
    return (0);
}

int    syntax_quote_error(t_minishell *minishell, char *token)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd("syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
    minishell->exit_code = 258;
    return (0);
}