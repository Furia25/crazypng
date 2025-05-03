/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_managing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:42:37 by val               #+#    #+#             */
/*   Updated: 2025/05/03 22:31:05 by val              ###   ########.fr       */
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

void	huffman_free_table(t_huffman_table *table)
{
	if (table->codes)
		free(table->codes);
	free(table);
}
