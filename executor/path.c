#include "minishell.h"

static void ft_free_split(char **split)
{
    int i;

    i = 0;
    if (!split)
        return;

    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

static char **get_paths(t_minishell *minishell)
{
    int i;

    i = -1;
    while (minishell->env->envp_var[++i] != NULL)
    {
        if (ft_strncmp(minishell->env->envp_var[i], "PATH=", 5) == 0)
            break;
    }
    return ft_split(minishell->env->envp_var[i] + 5, ':');
}
// {
//     t_list *tmp = envp_var;
//     char **paths = NULL;

//     while (tmp)
//     {
//         if (ft_strncmp(tmp->content, "PATH=", 5) == 0)
//         {
//             paths = ft_split(tmp->content + 5, ':');
//             break;
//         }
//         tmp = tmp->next;
//     }
//     return paths;
// }

static char *find_executable(char **paths, char *cmd)
{
    char *part_path;
    char *path;
    int i;

    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
            return path;
        free(path);
        i++;
    }
    return NULL;
}

static bool is_explicit_path(const char *cmd)
{
    return (cmd[0] == '/' || 
            (cmd[0] == '.' && cmd[1] == '/') || 
            (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'));
}

char *get_path(t_minishell *minishell, char *cmd)
{
    char **paths;
    char *path;

    if (*cmd == '\0')
        return (NULL);
    if (is_explicit_path(cmd))
    {
        if (access(cmd, F_OK) == 0)
            return (cmd);
        else
            return (NULL);
    }
    paths = get_paths(minishell);
    if (paths == NULL)
        return (NULL);
    path = find_executable(paths, cmd);
    ft_free_split(paths);
    return (path);
}

