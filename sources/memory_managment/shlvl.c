#include "minishell.h"

static int get_new_shlvl(int current_level)
{
    current_level++;
    if (current_level > 99)
    {
        printf("SHLVL reset to 1\n");
        return 1;
    }
    return current_level;
}

static int calculate_shlvl_length(int level)
{
    int length;
    
    length = 6;
    while (level > 0)
    {
        length++;
        level /= 10;
    }
    return length;
}

static void convert_level_to_string(char *str, int level, int length)
{
    str[length--] = '\0';
    while (level > 0)
    {
        str[length--] = (level % 10) + '0';
        level /= 10;
    }
}

static char *allocate_and_construct_shlvl(int level)
{
    int length;
    char *new_shlvl;

    length = calculate_shlvl_length(level);
    new_shlvl = malloc(length + 1);
    if (!new_shlvl)
        exit_fail("Failed to allocate memory for new SHLVL");
    ft_strcpy(new_shlvl, "SHLVL=");
    convert_level_to_string(new_shlvl + 6, level, length - 1);
    return new_shlvl;
}

char *increment_shlvl(const char *shlvl)
{
    int current_level;
    int new_level;

    current_level = ft_atoi(shlvl + 6);
    new_level = get_new_shlvl(current_level);
    return allocate_and_construct_shlvl(new_level);
}
