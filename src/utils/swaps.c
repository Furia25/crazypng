/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:18:45 by val               #+#    #+#             */
/*   Updated: 2025/05/06 01:27:48 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_utils.h"

uint32_t	swap_endian32(uint32_t value)
{
	return (((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) | \
		((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000));
}

uint16_t	swap_endian16(uint16_t value)
{
	return ((value >> 8) | (value << 8));
}

uint32_t	reverse_32bits(uint32_t code, int len)
{
	uint32_t	reversed;
	int			i;

	i = 0;
	reversed = 0;
	if (len < 0)
		len = 0;
	if (len > 32)
		len = 32;
	while (i < len)
	{
		reversed = (reversed << 1) | (code & 1);
		code >>= 1;
		i++;
	}
	return (reversed);
}

void	swap_ptr(void **ptr1, void **ptr2)
{
	void	*temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
