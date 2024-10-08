#include "lexer.h"
#include "minishell.h"

static int	solo_builtin(char *cmd)
{
	int		len;
	char	*cmd_lower;

	len = ft_strlen(cmd);
	cmd_lower = str_to_lower(cmd);
	if (ft_strncmp(cmd_lower, "cd", len) == 0
        || ft_strncmp(cmd_lower, "export",len) == 0
        || ft_strncmp(cmd_lower, "unset", len) == 0
		|| ft_strncmp(cmd_lower, "env", len) == 0
        || ft_strncmp(cmd_lower, "exit", len) == 0)
	{
		free(cmd_lower);
		return (1);
	}
	free(cmd_lower);
	return (0);
}

static int	is_builtin(char *cmd)
{
	int		len;
	char	*cmd_lower;

	len = ft_strlen(cmd);
	cmd_lower = str_to_lower(cmd);
	if (ft_strncmp(cmd_lower, "echo", len) == 0 || ft_strncmp(cmd_lower, "cd",
			len) == 0 || ft_strncmp(cmd_lower, "pwd", len) == 0
		|| ft_strncmp(cmd_lower, "export", len) == 0 || ft_strncmp(cmd_lower,
			"unset", len) == 0 || ft_strncmp(cmd_lower, "env", len) == 0
		|| ft_strncmp(cmd_lower, "exit", len) == 0)
	{
		free(cmd_lower);
		return (1);
	}
	free(cmd_lower);
	return (0);
}

static void	free_pipes(int **pipes, int num_cmd)
{
	int	i;

	i = 0;
	while (i < num_cmd - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}


static void	write_heredoc_to_fd(t_cmd *cmd, int fd)
{
	int	j;

	j = 0;
	while (cmd->heredoc[j] != NULL)
	{
		write(fd, cmd->heredoc[j], ft_strlen(cmd->heredoc[j]));
		write(fd, "\n", 1);
		j++;
	}
}

static void	heredoc_fd(t_cmd *cmd)
{
	int	heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	write_heredoc_to_fd((cmd), heredoc_fd[1]);
	close(heredoc_fd[1]);
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 file");
		exit(EXIT_FAILURE);
	}
	close(heredoc_fd[0]);
}

static void open_file(t_minishell *minishell, const char *filename, int perm_or_no_file)
{
	if (access(filename, R_OK) == -1 || access(filename, W_OK) == -1)
	{
		if (perm_or_no_file == 1)
			permission_denied(minishell, (char *)filename, 1);
		else
			no_file(minishell, (char *)filename);
		exit(minishell->exit_code);
	}
	else
		return ;
}

static void	redirects(t_minishell *minishell, t_cmd *current, int **pipes,
		int i, int num_cmd)
{
	t_list	*tmp;
	int 	flags;
	int 	last_input_fd;
	int 	last_output_fd;

	last_input_fd = -1;
	last_output_fd = -1;
	tmp = current->files;
	while (tmp)
	{
		if (tmp->mode == 'h')
		{
			if (last_input_fd != -1)
				close(last_input_fd);
			heredoc_fd(current);
		}
		else if (tmp->mode == 'o')
		{
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			last_output_fd = open(tmp->filename, flags, 0644);
			open_file(minishell, tmp->filename, 1);
		}
		else if (tmp->mode == 'a')
		{
			flags = O_WRONLY | O_CREAT | O_APPEND;
			last_output_fd = open(tmp->filename, flags, 0644);
			open_file(minishell, tmp->filename, 1);
		}
		else if (tmp->mode == 'i')
		{
			last_input_fd = open(tmp->filename, O_RDONLY);
			open_file(minishell, tmp->filename, 0);
			if (last_input_fd == -1)
			{
				no_file(minishell, tmp->filename);
				exit(minishell->exit_code);
			}
		}
		tmp = tmp->next;
	}
	if (last_input_fd != -1)
	{
		dup2(last_input_fd, STDIN_FILENO);
		close(last_input_fd);
	}
	else if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (last_output_fd != -1)
	{
		dup2(last_output_fd, STDOUT_FILENO);
		close(last_output_fd);
	}
	else if (i < num_cmd - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

static void	close_pipes(int **pipes, int num_cmd)
{
	int	j;

	j = -1;
	while (++j < num_cmd - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}

static int	path_present(t_minishell *minishell)
{
	int	i;

	i = -1;
	while (minishell->env[++i] != NULL)
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == 0)
			break ;
	}
	if (minishell->env[i])
		return (1);
	return (0);
}

static int	file_dir_check(char *cmd)
{
	while (ft_isspace(*cmd))
		cmd++;
	if ((*cmd == '.' || *cmd == '/' || (*cmd == '.' && *(cmd + 1) == '/')
			|| (*cmd == '.' && *(cmd + 1) == '.' && *(cmd + 2) == '/'))
		&& ft_strncmp(cmd, "./minishell", ft_strlen(cmd)) != 0)
		return (1);
	return (0);
}

static void	handle_file_dir(t_minishell *minishell, char **cmd)
{
	struct stat	stat_buf;

	stat(*cmd, &stat_buf);
	if (access(*cmd, F_OK) == -1)
	{
		no_path_file(minishell, *cmd);
		exit(minishell->exit_code);
	}
	else if (access(*cmd, F_OK) == 0 && S_ISDIR(stat_buf.st_mode))
	{
		is_a_directory(minishell, *cmd, 'e');
		exit(minishell->exit_code);
	}
	else if (access(*cmd, X_OK) == -1)
	{
		permission_denied(minishell, *cmd, 0);
		exit(minishell->exit_code);
	}
}

static void	execute_child(t_minishell *minishell, t_cmd *current, int **pipes,
		int i, int num_cmd, char **env)
{
	redirects(minishell, current, pipes, i, num_cmd);
	close_pipes(pipes, num_cmd);
	if (is_builtin(current->cmd[0]))
	{
		execute_command(minishell, STDOUT_FILENO, current);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (!path_present(minishell))
			return (no_path_file(minishell, current->cmd[0]));
		if (file_dir_check(current->cmd[0]))
			return (handle_file_dir(minishell, current->cmd));
		if (!get_path(minishell, current->cmd[0]))
		{
			not_found(minishell, current->cmd[0]);
			exit(minishell->exit_code);
		}
		execve(get_path(minishell, current->cmd[0]), current->cmd, env);
		exit(minishell->exit_code);
	}
}

static int	count_commands(t_cmd *cmd)
{
	int	num_cmd;

	num_cmd = 0;
	while (cmd)
	{
		num_cmd++;
		cmd = cmd->next;
	}
	return (num_cmd);
}

static int	**setup_pipes(int num_cmd)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * (num_cmd - 1));
	while (++i < num_cmd - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (pipes);
}

static pid_t	*fork_processes(t_minishell *minishell, int num_cmd,
		int **pipes, char **env)
{
	t_cmd	*cur;
	pid_t	*pids;
	int		i;

	i = -1;
	cur = minishell->cmd;
	pids = malloc(sizeof(pid_t) * num_cmd);
	while (++i < num_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			execute_child(minishell, cur, pipes, i, num_cmd, env);
		}
		cur = cur->next;
	}
	return (pids);
}

static void	wait_for_processes(pid_t *pids, int num_cmd, t_minishell *minishell)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	i = 0;
	while (i < num_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	minishell->exit_code = exit_code;
}

static void	execute_commands(t_minishell *minishell, char **env)
{
	int		num_cmd;
	int		**pipes;
	pid_t	*pids;

	num_cmd = count_commands(minishell->cmd);
	pipes = NULL;
	pids = NULL;
	if (num_cmd == 1 && solo_builtin(minishell->cmd->cmd[0]))
	{
		minishell->tmp->is_child = 0;
		execute_command(minishell, STDOUT_FILENO, minishell->cmd);
	}
	else
	{
		if (num_cmd > 1)
			pipes = setup_pipes(num_cmd);
		pids = fork_processes(minishell, num_cmd, pipes, env);
		if (num_cmd > 1)
		{
			close_pipes(pipes, num_cmd);
			free_pipes(pipes, num_cmd);
		}
		wait_for_processes(pids, num_cmd, minishell);
		free(pids);
	}
}

void	execute(t_minishell *minishell)
{
	char	**env;

	env = minishell->env;
	execute_commands(minishell, env);
	free_minishell(minishell);
}
