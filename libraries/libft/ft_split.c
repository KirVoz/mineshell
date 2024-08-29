/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 02:15:11 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 16:20:28 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *s, char c);
static char	*word_split(char const *s, char c, int *str_i);
static char	*word_allocation(int len);
static void	*word_deallocation(char ***result, int word_i);

char	**ft_split(char const *s, char c)
{
	int		words;
	int		word_i;
	int		str_i;
	char	**result;

	if (!s)
		return (NULL);
	words = words_count(s, c);
	word_i = 0;
	str_i = 0;
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (word_i < words)
	{
		result[word_i] = word_split(s, c, &str_i);
		if (!result[word_i])
			return (word_deallocation(&result, word_i));
		word_i++;
	}
	result[word_i] = NULL;
	return (result);
}

static char	*word_split(char const *s, char c, int *str_i)
{
	int		j;
	int		len;
	char	*sep_word;

	j = 0;
	len = 0;
	while (s[*str_i] == c && s[*str_i] != '\0')
		(*str_i)++;
	while (s[*str_i] != c && s[*str_i] != '\0')
	{
		len++;
		(*str_i)++;
	}
	sep_word = word_allocation(len);
	(*str_i) -= len;
	while (j < len)
	{
		sep_word[j] = s[*str_i];
		j++;
		(*str_i)++;
	}
	sep_word[j] = '\0';
	while (s[*str_i] == c && s[(*str_i) + 1] != c && s[(*str_i) + 1] != '\0')
		(*str_i)++;
	return (sep_word);
}

static char	*word_allocation(int len)
{
	char	*sep_word;

	sep_word = (char *)malloc((len + 1) * sizeof(char));
	if (!sep_word)
		return (NULL);
	return (sep_word);
}

static void	*word_deallocation(char ***result, int word_i)
{
	while (word_i >= 0)
	{
		free(*result[word_i]);
		word_i--;
	}
	return (NULL);
}

static int	words_count(char const *s, char c)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (s[++i] != '\0')
	{
		if (!words && s[i] != c)
			words++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
	}
	return (words);
}
/*
#include <stdio.h>
int	matrix_len(char **a);

int	main()
{
	char **a1 = ft_split("he llo", ' ');
	char **a = ft_split("          ", ' ');

	char **test = a1;
	for (int i = 0; i < matrix_len(test); i++)
		printf("%s\n", test[i]);

	// char * * tab = ft_split("  tripouille  42  ", ' ');
	// char *string = "      split       this for   me  !       ";
	// char *string = "      split       this for   me  !";
	// char **result = ft_split(string, ' ');
	// char	s[] = "  olol";
	// char	c = ' ';
	// char	**z = ft_split(s, c);
	// for (int i = 0; i < 6; i++)
	// 	printf("%s\n", result[i]);
}

int	matrix_len(char **a)
{
    int length = 0;
	if (!a)
		return (0);
    while (a[length] != NULL) {
        length++;
    }
	return (length);
}

// #include <stdio.h>

// int main()
// {
// 	// printf("%d\n", words_count("tripouille", 0));
// 	printf("%s\n", ft_split("tripouille", 0));
// }
*/
