/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:39:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/17 19:43:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;

	if (!s)
		return (NULL);
	chr = (char) c;
	while (*s != '\0')
	{
		if (*s == chr)
			return ((char *) s);
		s++;
	}
	if (chr == '\0')
		return ((char *) s);
	return (NULL);
}

long	ft_strchri(char *s, int c)
{
	char	chr;
	long	index;

	if (!s)
		return (-1);
	chr = (char) c;
	index = 0;
	while (s[index])
	{
		if (s[index] == chr)
			return (index);
		index++;
	}
	if (chr == '\0')
		return (index);
	return (-1);
}

/* 
int	main(void)
{
	char *test = "TEST1 ABCDEF";
	printf("%p\n", ft_strchr(test, '1'));
	printf("%p", test);
} */