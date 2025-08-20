/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_read_lengths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:06:11 by val               #+#    #+#             */
/*   Updated: 2025/06/23 00:29:42 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static bool	decode_lengths(t_inflate_dynamic_data *data,
				t_huffman_table *clen_huff, int *code_lengths);
static bool	fill_repeat_last(t_inflate_dynamic_data *data,
				int *code_lengths, uint8_t extra_bits, uint8_t base);

bool	read_dynamic_code_lengths(t_inflate_dynamic_data *data,
			t_huffman_table *clen_huff, int *code_lengths,
			uint16_t total_codes)
{
	data->temp_i = 0;
	data->temp_size = total_codes;
	data->temp_last = 0;
	while (data->temp_i < total_codes)
	{
		if (!decode_lengths(data, clen_huff, code_lengths))
			return (false);
	}
	return (true);
}

static bool	decode_lengths(t_inflate_dynamic_data *data,
				t_huffman_table *clen_huff, int *code_lengths)
{
	int	symbol;

	symbol = huffman_decode(&data->context->bit_stream, clen_huff);
	if (symbol < 0 || symbol > 18)
		return (false);
	if (symbol <= 15)
	{
		code_lengths[data->temp_i] = symbol;
		data->temp_last = symbol;
		data->temp_i++;
		return (true);
	}
	else if (symbol == 16)
		return (fill_repeat_last(data, code_lengths, 2, 3));
	else if (symbol == 17 || symbol == 18)
	{
		data->temp_last = 0;
		if (symbol == 17)
			return (fill_repeat_last(data, code_lengths, 3, 3));
		else if (symbol == 18)
			return (fill_repeat_last(data, code_lengths, 7, 11));
	}
	return (false);
}

static bool	fill_repeat_last(t_inflate_dynamic_data *data,
				int *code_lengths, uint8_t extra_bits, uint8_t base)
{
	uint16_t	extra;

	extra = 0;
	if (!bs_sread_16bits(&data->context->bit_stream, extra_bits, &extra))
		return (false);
	extra += base;
	if (data->temp_i + extra > data->temp_size)
	{
		ft_putstr_fd("Error: Code lengths exceed buffer size. \
			Attempted to write ", 2);
		ft_putnbr_fd(extra, 2);
		ft_putstr_fd(" entries at index ", 2);
		ft_putnbr_fd(data->temp_i, 2);
		ft_putstr_fd(" / ", 2);
		ft_putnbr_fd(data->temp_size, 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	while (extra)
	{
		code_lengths[data->temp_i] = data->temp_last;
		data->temp_i++;
		extra--;
	}
	return (true);
}
