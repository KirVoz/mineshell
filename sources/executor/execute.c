#include "lexer.h"
#include "minishell.h"

static void exe_solo(t_minishell *minishell, char *line)
{
	pid_t 		pid;

	pid = fork();
	if (pid == -1)
		exit_fail("Failed to fork");
	if (pid == 0)
		execute_command(line, minishell);
	else
		waitpid(pid, &minishell->exit_code, 0);
}

int     is_builtin(char *cmd)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", cmd_len) == 0
		|| ft_strncmp(cmd, "cd", cmd_len) == 0
		|| ft_strncmp(cmd, "pwd", cmd_len) == 0
		|| ft_strncmp(cmd, "export", cmd_len) == 0
		|| ft_strncmp(cmd, "unset", cmd_len) == 0
        || ft_strncmp(cmd, "env", cmd_len) == 0
        || ft_strncmp(cmd, "exit", cmd_len) == 0)
		return (1);
	return (0);
}

void	execute(t_minishell *minishell, char *line, char **env)
{
	t_cmd	*current;
	char	*path;
	char	**res;

	res = NULL;
	res = array_init();
	lexer_main(minishell, line);
	current = minishell->cmd;
	while (current != NULL)
	{
		*res = ft_strdup(current->cmd[0]);
        if (!res)
		    exit_fail("Failed to allocate memory for result in execute");
        if (is_builtin(*res))
		{
			exe_solo(minishell, *res);
            break ;
		}
		current = current->next;
		path = get_path(minishell, *res);
		if (!path)
		{
			not_found(minishell, *res);
			break ;
		}
		execve(get_path(minishell, *res), res, env);
	}
}
