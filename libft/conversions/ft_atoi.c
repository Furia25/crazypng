/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:27:07 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/17 17:35:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '	' || c == '\f')
		return (1);
	return (c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int					index;
	int					sign;
	unsigned long long	result;

	if (!nptr)
		return (0);
	index = 0;
	result = 0;
	sign = 1;
	while (nptr[index] && ft_isspace(nptr[index]))
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			sign *= -1;
		index++;
	}
	while (nptr[index] && nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = result * 10 + (nptr[index] - '0');
		index++;
	}
	return (result * sign);
}

/* int main(void)
{
	printf("%d", atoi("     					+1500"));
} */