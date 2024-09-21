#include "minishell.h"

void execute_pwd(t_minishell *minishell, int fd)
{
    char cwd[1024]; // Буфер для хранения текущего пути

    (void)minishell;
    // Получаем текущую рабочую директорию с помощью getcwd
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putstr_fd(cwd, fd); // Выводим текущую директорию
        ft_putstr_fd("\n", fd); // Добавляем новую строку
    }
    else
    {
        perror("getcwd"); // Выводим сообщение об ошибке, если getcwd не сработала
    }
}
