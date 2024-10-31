/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:56:22 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/09 17:17:02 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fail(const char *exit_message)
{
	perror(exit_message);
	exit(EXIT_FAILURE);
}

static char	*join_free(char *res, char *arg)
{
	char	*res_tmp;

	res_tmp = res;
	res = ft_strjoin(res, arg);
	free(res_tmp);
	return (res);
}

char	*construct_error(char *arg1, char *arg2, char *arg3, char mode)
{
	char	*res;

	res = NULL;
	if (!(mode == 'm' || mode == 'l' || mode == 'e'))
		res = allocate_dup("minishell: ", "res in construct_error");
	else
		res = allocate_dup("", "res in construct_error");
	if (arg1)
		res = join_free(res, arg1);
	if (mode == 'm')
		res = join_free(res, "/: ");
	if (mode == 's' || mode == 'l')
		res = join_free(res, ": ");
	if (arg2)
		res = join_free(res, arg2);
	if (arg3)
		res = join_free(res, arg3);
	if (mode == 'n')
		res = join_free(res, "\n");
	return (res);
}
