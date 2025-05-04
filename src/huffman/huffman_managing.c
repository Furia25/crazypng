/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_managing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:42:37 by val               #+#    #+#             */
/*   Updated: 2025/05/04 14:43:11 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_huffman.h"

t_huffman_table	*huffman_new_table(size_t count)
{
	t_huffman_table	*result;

	result = ft_calloc(1, sizeof(t_huffman_table));
	if (!result)
		return (NULL);
	result->codes = ft_calloc(count, sizeof(t_huffman_code));
	if (!result->codes)
	{
		free(result);
		return (NULL);
	}
	result->count = count;
	return (result);
}

t_huffman_table	*huffman_table_from_codes(t_huffman_code *codes, size_t count)
{
	t_huffman_table	*table;

	if (!codes)
		return (NULL);
	table = ft_calloc(1, sizeof(t_huffman_table));
	if (!table)
		return (NULL);
	table->count = count;
	table->codes = codes;
	return (table);
}

void	huffman_free_table(t_huffman_table *table)
{
	if (table->codes)
		free(table->codes);
	free(table);
}
