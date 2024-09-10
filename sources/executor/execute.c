#include "lexer.h"
 #include "minishell.h"

 static void exe_solo(t_minishell *minishell, char *line)
 {
     pid_t pid;
     int status;

     printf("Executing solo command: %s\n", line);
     pid = fork();
     if (pid == -1)
     {
         perror("Failed to fork");
         exit(EXIT_FAILURE);
     }
     if (pid == 0)
     {
         // Дочерний процесс
         execute_command(line, minishell);
         exit(minishell->exit_code); // Завершить дочерний процесс с кодом завершения
     }
     else
     {
         waitpid(pid, &status, 0);
         if (WIFEXITED(status))
             minishell->exit_code = WEXITSTATUS(status);
         else
             minishell->exit_code = 1; // Установить код ошибки, если процесс завершился некорректно
     }
 }

 static void exe_from_env(t_minishell *minishell, char *path, char **res, char **env)
 {
     pid_t pid;
     int status;

     printf("Executing command from env: %s\n", path);
     pid = fork();
     if (pid == -1)
     {
         perror("Failed to fork");
         exit(EXIT_FAILURE);
     }
     if (pid == 0)
     {
         // Дочерний процесс
         execve(path, res, env);
         perror("execve failed"); // Если execve вернул управление, значит произошла ошибка
         exit(EXIT_FAILURE);
     }
     else
     {
         // Родительский процесс
         waitpid(pid, &status, 0);
         if (WIFEXITED(status))
             minishell->exit_code = WEXITSTATUS(status);
         else
             minishell->exit_code = 1; // Установить код ошибки, если процесс завершился некорректно
     }
 }

 static int is_builtin(char *cmd)
 {
     size_t cmd_len;

    cmd_len = ft_strlen(cmd);
    if (ft_strncmp(cmd, "echo", cmd_len) == 0 || ft_strncmp(cmd, "cd", cmd_len) == 0 || 
        ft_strncmp(cmd, "pwd", cmd_len) == 0 || ft_strncmp(cmd, "export", cmd_len) == 0 || 
        ft_strncmp(cmd, "unset", cmd_len) == 0 || ft_strncmp(cmd, "env", cmd_len) == 0 || 
        ft_strncmp(cmd, "exit", cmd_len) == 0)
        return (1);
     return (0);
 }

 static int **create_pipes(int num_cmd)
 {
     int i;
     int **pipes;

     pipes = malloc((num_cmd - 1) * sizeof(int *));
     if (!pipes)
         exit_fail("Failed to allocate memory for pipes");
     i = 0;
     while (i < num_cmd - 1)
     {
         pipes[i] = malloc(2 * sizeof(int));
         if (!pipes[i] || pipe(pipes[i]) == -1)
             exit_fail("Failed to create pipe");
         i++;
     }
     return pipes;
 }

 static void close_pipes(int **pipes, int num_cmd)
 {
     int i;

     i = 0;
     while (i < num_cmd - 1)
     {
         close(pipes[i][0]);
         close(pipes[i][1]);
         i++;
     }
 }

 static void free_pipes(int **pipes, int num_cmd)
 {
     int i;

     i = 0;
     while (i < num_cmd - 1)
     {
         free(pipes[i]);
         i++;
     }
     free(pipes);
 }

 static void execute_child(t_minishell *minishell, t_cmd *current, int **pipes, int i, int num_cmd, char **env)
 {
     int j;

     if (i > 0)
     {
         if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
         {
             perror("dup2 stdin");
             exit(EXIT_FAILURE);
         }
     }
     if (i < num_cmd - 1)
     {
         if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
         {
             perror("dup2 stdout");
             exit(EXIT_FAILURE);
         }
     }
     for (j = 0; j < num_cmd - 1; j++)
     {
         close(pipes[j][0]);
         close(pipes[j][1]);
     }
     if (is_builtin(current->cmd[0]))
         execute_command(current->cmd[0], minishell);
     else
    {
        if (execve(get_path(minishell, current->cmd[0]), current->cmd, env) == -1)
        {
            not_found(minishell, current->cmd[0]);
            exit(EXIT_FAILURE);
        }
     }
 }

 // static void execute_child(t_minishell *minishell, t_cmd *current, int **pipes, int i, int num_cmd, char **env)
 // {
 //     int j;

 //     if (i > 0)
 //         dup2(pipes[i - 1][0], STDIN_FILENO);
 //     if (i < num_cmd - 1)
 //         dup2(pipes[i][1], STDOUT_FILENO);
 //     j = 0;
 //     while (j < num_cmd - 1)
 //     {
 //         close(pipes[j][0]);
 //         close(pipes[j][1]);
 //         j++;
 //     }
 //     if (is_builtin(current->cmd[0]))
 //         execute_command(current->cmd[0], minishell);
 //     else
 //     {
 //         if (execve(get_path(minishell, current->cmd[0]), current->cmd, env) == -1)
 //         {
 //             not_found(minishell, current->cmd[0]);
 //             exit(EXIT_FAILURE);
 //         }
 //     }
 // }

 void exe_with_pipes(t_minishell *minishell, char **env)
 {
     int i;
     int num_cmd;
     t_cmd *current;
     int **pipes;
     pid_t *pids;
     int exit_code = 0;

     num_cmd = 0;
     current = minishell->cmd;
     while (current)
     {
         num_cmd++;
         current = current->next;
     }
     pipes = create_pipes(num_cmd);
     pids = malloc(num_cmd * sizeof(pid_t));
     if (!pids)
         exit_fail("Failed to allocate memory for pids");
     current = minishell->cmd;
     i = 0;
     while (i < num_cmd)
     {
         pids[i] = fork();
         if (pids[i] == -1)
             exit_fail("Failed to fork");
         if (pids[i] == 0)
             execute_child(minishell, current, pipes, i, num_cmd, env);
         current = current->next;
         i++;
     }
     close_pipes(pipes, num_cmd);
     i = 0;
     while (i < num_cmd)
     {
         int status;
         waitpid(pids[i], &status, 0);
         if (WIFEXITED(status))
         {
            exit_code = WEXITSTATUS(status);
            if (exit_code != 0)
            {
                printf("Command failed with exit code: %d\n", exit_code);
            }
        }
         i++;
     }
     minishell->exit_code = exit_code;
     free_pipes(pipes, num_cmd);
     free(pids);
 }

 int is_pipe(t_minishell *minishell, char **env)
 {
     t_cmd *cur;
     int i = 0;

     cur = minishell->cmd;
     while (cur)
     {
         i++;
         cur = cur->next;
     }
     if (i == 1)
         return 0;
     exe_with_pipes(minishell, env);
     return 1;
 }

 void execute_single_command(t_minishell *minishell, char *cmd, char **env)
 {
     char *path;

     if (is_builtin(cmd))
     {
         printf("Executing built-in command: %s\n", cmd);
         exe_solo(minishell, cmd);
     }
     else
     {
         path = get_path(minishell, cmd);
         if (!path)
         {
             not_found(minishell, cmd);
             return;
         }
         printf("Executing external command: %s\n", cmd);
         exe_from_env(minishell, path, &cmd, env);
     }
 }

 void execute(t_minishell *minishell, char **env)
 {
     t_cmd *current;
     char **res;

     printf("Starting execution\n");

     res = array_init();
     if (!*res) {
         exit_fail("Failed to allocate memory for result in execute");
     }

     current = minishell->cmd;
 	while (current)
 	{
 		printf("!!!Command: %s\n", current->cmd[0]);
 		current = current->next;
 	}
 	current = minishell->cmd;

     *res = ft_strdup(current->cmd[0]);
     if (!*res) {
         exit_fail("Failed to allocate memory for command string");
     }

     printf("Command to execute: %s\n", *res);

 	(void)env;
     if (!is_pipe(minishell, env)) {
         execute_single_command(minishell, *res, env);
     }
     printf("Execution finished\n\n");
 }