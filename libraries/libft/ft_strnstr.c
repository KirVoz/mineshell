/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:09:49 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:14:54 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char *res, const char *little, size_t start);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	char	*res;

	i = 0;
	j = 0;
	if (len == 0 && (!big || !little))
		return (NULL);
	little_len = ft_strlen(little);
	res = (char *)big;
	while (res[i] != '\0' && i < len && little[j] != '\0')
	{
		if (res[i] == little[j])
			j++;
		i++;
	}
	if (j == little_len && ft_check(res, little, i - little_len))
		return (&res[i - little_len]);
	return (NULL);
}

static int	ft_check(char *res, const char *little, size_t start)
{
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	while (little[j] != '\0')
	{
		if (little[j] != res[i])
			return (0);
		i++;
		j++;
	}
	return (1);
}
/*
#include <string.h>
#include <stdio.h>

int main()
{
	const char *str1 = ft_strnstr("lorem ipsum dolor sit amet", "ipsumm", 30);
	const char *str2 = strnstr("lorem ipsum dolor sit amet", "ipsumm", 30);
	printf("%s\n", str1);
	printf("%s", str2);
}

int	main()
{
	printf("%s", ft_strnstr(((void *)0), "fake", 3));

	printf("%s", strnstr(((void *)0), "fake", 3));
}

int main()
{
void test_case(const char *big, const char *little, size_t len) {
    char *result = ft_strnstr(big, little, len);

    if (result == NULL) {
        printf("'%s' not in '%s'\n", little, big);
    } else {
        printf("'%s' is index %ld in '%s'\n",
       	little, result - big, big);
    }
}

int main() {
    // Test cases
    const char *big1 = "Hello, World!";
	const char *big2 = "FF";
	const char *big3 = "MZIRIBMZIRIBMZE123";
	const char *big4 = "123456789";
	const char *big5 = "oh no not the empty string !";
	const char *big6 = "oh no not the empty string !";


    const char *little1 = "World";
    const char *little2 = "Universe";
    const char *little3 = "Hello";
    const char *little4 = "";
    const char *little5 = "!";
	const char *little6 = "see F your F return F now F";
	const char *little7 = "MZIRIBMZE";
    const char *little8 = "9";
    const char *little9 = "";
    const char *little10 = "";

    test_case(big1, little1, ft_strlen(big1));
    test_case(big1, little2, ft_strlen(big1));
    test_case(big1, little3, ft_strlen(big1));
    test_case(big1, little4, ft_strlen(big1));
    test_case(big1, little5, ft_strlen(big1));
	test_case(big2, little6, ft_strlen(little6));
	test_case(big3, little7, ft_strlen(little7));
	test_case(big4, little8, 8);
	test_case(big5, little9, ft_strlen(big5));
	test_case(big6, little10, 0);
}
*/
