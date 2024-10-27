/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:17:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:17:39 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	get_new_shlvl(int current_level)
{
	current_level++;
	if (current_level > 99)
	{
		printf("SHLVL reset to 1\n");
		return (1);
	}
	return (current_level);
}

static int	calculate_shlvl_length(int level)
{
	int	length;
	int	temp;

	temp = level;
	length = 6;
	if (temp == 0)
		return (7);
	while (temp > 0)
	{
		length++;
		temp /= 10;
	}
	return (length);
}

static void	convert_level_to_string(char *str, int level, int length)
{
	str[length] = '\0';
	length--;
	if (level == 0)
	{
		str[length] = '0';
		return ;
	}
	while (level > 0 && length >= 0)
	{
		str[length--] = (level % 10) + '0';
		level /= 10;
	}
}

static char	*allocate_and_construct_shlvl(int level)
{
	int		length;
	char	*new_shlvl;

	length = calculate_shlvl_length(level);
	new_shlvl = malloc(sizeof(char) * (length + 1));
	if (!new_shlvl)
		exit_fail("Failed to allocate memory for new SHLVL");
	if (ft_memcpy(new_shlvl, "SHLVL=", 6) == NULL)
	{
		free(new_shlvl);
		exit_fail("Failed to copy SHLVL to new_shlvl");
	}
	convert_level_to_string(new_shlvl + 6, level, length - 6);
	return (new_shlvl);
}

char	*increment_shlvl(const char *shlvl)
{
	int	current_level;
	int	new_level;

	current_level = ft_atoi(shlvl + 6);
	if (current_level < 0)
		return (allocate_and_construct_shlvl(0));
	new_level = get_new_shlvl(current_level);
	return (allocate_and_construct_shlvl(new_level));
}
