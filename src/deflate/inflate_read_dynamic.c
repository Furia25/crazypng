/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_read_dynamic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:53:34 by val               #+#    #+#             */
/*   Updated: 2025/06/23 00:28:20 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static bool	create_dynamic_tables(t_inflate_dynamic_data *data,
				t_huffman_table **litlen,
				t_huffman_table **dist);

static bool	read_dynamic_hlengths(t_inflate_dynamic_data *data);
static bool	init_dynamic_clen_tab(t_inflate_dynamic_data *data);

bool	inflate_get_dynamic(t_inflate_context *context,
			t_huffman_table **litlen, t_huffman_table **dist)
{
	t_inflate_dynamic_data	data;
	t_huffman_code			clen_codes[DEFLATE_CLEN_SIZE];

	data.context = context;
	if (!read_dynamic_hlengths(&data))
		return (false);
	if (!init_dynamic_clen_tab(&data))
		return (false);
	assign_huffman_codes(clen_codes, data.clen_tab, DEFLATE_CLEN_SIZE);
	data.clen_hufftable.codes = clen_codes;
	data.clen_hufftable.count = DEFLATE_CLEN_SIZE;
	data.clen_hufftable.max_bits = DEFLATE_CLEN_MAXBITS;
	return (create_dynamic_tables(&data, litlen, dist));
}

static bool	create_dynamic_tables(t_inflate_dynamic_data *data,
				t_huffman_table **litlen,
				t_huffman_table **dist)
{
	int		all_lengths[DEFLATE_LL_TABLE_SIZE + DEFLATE_D_TABLE_SIZE + 1];

	ft_memset(all_lengths, 0,
		(DEFLATE_LL_TABLE_SIZE + DEFLATE_D_TABLE_SIZE) * sizeof(int));
	if (!read_dynamic_code_lengths(data, &data->clen_hufftable,
			all_lengths, data->hlit + data->hdist))
		return (false);
	*litlen = huffman_new_table(data->hlit);
	if (!*litlen)
		return (false);
	*dist = huffman_new_table(data->hdist);
	if (!*dist)
	{
		huffman_free_table(*litlen);
		return (false);
	}
	assign_huffman_codes((*litlen)->codes, all_lengths, data->hlit);
	assign_huffman_codes((*dist)->codes, all_lengths + data->hlit, data->hdist);
	(*litlen)->max_bits = DEFLATE_MAXBITS;
	(*dist)->max_bits = DEFLATE_MAXBITS;
	return (true);
}

static bool	read_dynamic_hlengths(t_inflate_dynamic_data *data)
{
	uint8_t	temp;

	temp = 0;
	if (!bs_sread_8bits(&data->context->bit_stream, 5, &temp))
		return (false);
	if (!bs_sread_8bits(&data->context->bit_stream, 5, &data->hdist))
		return (false);
	if (!bs_sread_8bits(&data->context->bit_stream, 4, &data->hclen))
		return (false);
	data->hlit = 257 + temp;
	data->hdist += 1;
	data->hclen += 4;
	return (true);
}

static bool	init_dynamic_clen_tab(t_inflate_dynamic_data *data)
{
	uint8_t	i;
	uint8_t	value;

	i = 0;
	while (i < 19)
	{
		data->clen_tab[i] = 0;
		i++;
	}
	i = 0;
	while (i < data->hclen)
	{
		value = 0;
		if (!bs_sread_8bits(&data->context->bit_stream, 3, &value))
			return (false);
		data->clen_tab[g_inflate_hclen_order[i]] = value;
		i++;
	}
	return (true);
}
