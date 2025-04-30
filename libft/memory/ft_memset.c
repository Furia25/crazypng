/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:52:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 01:01:25 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	val;
	uint64_t		block;
	size_t			chunks;

	p = (unsigned char *)ptr;
	val = (unsigned char)value;
	while (((uintptr_t)p & 0x7) && num--)
		*p++ = val;
	block = val * 0x0101010101010101ULL;
	chunks = num / 8;
	while (chunks--)
	{
		*(uint64_t *)p = block;
		p += 8;
	}
	num %= 8;
	while (num--)
		*p++ = val;
	return (ptr);
}

/* int main () 
{
   char str[50];

   strcpy(str, "Welcome to Tutorialspoint");
   puts(str);

   ft_memset(str, '#', 7);
   puts(str);
   
   return(0);
} */