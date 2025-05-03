/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_deflate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:48:50 by val               #+#    #+#             */
/*   Updated: 2025/05/03 20:57:17 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_huffman.h"

t_huffman_table	*huffman_deflate_table(void)
{
	t_huffman_table	*table;
	t_huffman_code	*temp;
	size_t			index;

	table = huffman_new_table(288);
	if (!table)
		return (NULL);
		table->max_bits = 9;
	index = 0;
	temp = table->codes;
	while (index <= 143)
	{
		temp[index].code = 0x30 + index;
		temp[index].bits = 8;
		index++;
	}
	
	return (table);
}
