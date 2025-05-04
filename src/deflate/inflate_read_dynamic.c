/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_read_dynamic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:53:34 by val               #+#    #+#             */
/*   Updated: 2025/05/04 20:42:44 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static bool	create_dynamic_tables(t_inflate_dynamic_data *data, \
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
	if (!create_dynamic_tables(&data, litlen, dist))
		return (false);
	return (true);
}

static bool	create_dynamic_tables(t_inflate_dynamic_data *data, \
	t_huffman_table **litlen,
	t_huffman_table **dist)
{
	int		litlen_lengths[DEFLATE_LL_TABLE_SIZE];
	int		dist_lengths[DEFLATE_D_TABLE_SIZE];

	ft_putstr_fd("La bite1\n", 2);
	if (!read_dynamic_code_lengths(data, &data->clen_hufftable, \
		litlen_lengths, data->hlit))
		return (false);
	ft_putstr_fd("La bite2\n", 2);
	if (!read_dynamic_code_lengths(data, &data->clen_hufftable, \
		dist_lengths, data->hdist))
		return (false);
	ft_putstr_fd("La bite3\n", 2);
	*litlen = huffman_new_table(data->hlit);
	if (!*litlen)
		return (false);
	*dist = huffman_new_table(data->hdist);
	if (!*dist)
	{
		huffman_free_table(*litlen);
		return (false);
	}
	assign_huffman_codes((*litlen)->codes, litlen_lengths, data->hlit);
	assign_huffman_codes((*dist)->codes, dist_lengths, data->hdist);
	return (true);
}

static bool	read_dynamic_hlengths(t_inflate_dynamic_data *data)
{
	if (!bs_sread_8bits(&data->context->bit_stream, 5, &data->hlit))
		return (false);
	if (!bs_sread_8bits(&data->context->bit_stream, 5, &data->hdist))
		return (false);
	if (!bs_sread_8bits(&data->context->bit_stream, 4, &data->hclen))
		return (false);
	data->hlit += 257;
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
