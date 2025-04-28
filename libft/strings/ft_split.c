/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:14:20 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/08 16:59:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_split(char const *str, char c)
{
	char	**result;
	size_t	iword;
	size_t	word_len;

	result = ft_calloc(count_words(str, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	iword = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str == '\0')
			break ;
		word_len = 0;
		while (str[word_len] && str[word_len] != c)
			word_len++;
		result[iword] = ft_substr(str, 0, word_len);
		if (!result[iword])
			return (free_chartab(result), NULL);
		str += word_len;
		iword++;
	}
	return (result);
}

void	free_chartab(char **tab)
{
	size_t	index;

	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	next;
	int	words;

	words = 0;
	next = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			next = 1;
		else if (next)
		{
			words++;
			next = 0;
		}
		i++;
	}
	return (words);
}

/*    int	main(int argc, char *argv[])
{
	char	*test = "split  ||this|for|me|||||!|";
	char	**t;
	char	**t2;

	t = ft_split(argv[1], '-');
	int i = 0;
	while (t[i])
	{
		puts(t[i]);
		i++;
	}
} */
