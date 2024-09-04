#include "minishell.h"

void pipex(t_minishell *minishell)
{
    int fd[2];
    pid_t pid;

    if (minishell->cmd->cmd[1] == NULL) // Если передана только одна команда
    {
        execute_command(minishell->cmd->cmd[0], minishell);
    }
    else // Если переданы две команды
    {
        if (pipe(fd) == -1)
            exit_fail("pipe");
        pid = fork();
        if (pid == -1)
            exit_fail("fork");
        if (pid == 0)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            execute_command(minishell->cmd->cmd[0], minishell);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execute_command(minishell->cmd->cmd[1], minishell);
            exit(EXIT_SUCCESS);
        }
    }
}
// наверно можно подавать в цикле в зависимости от наличия и отсутствия пайпов
// но от осознания количества вариантов которые можно подать и приходит понимание что это не так просто
