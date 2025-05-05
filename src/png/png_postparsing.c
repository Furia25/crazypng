/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_postparsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:22:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 00:49:53 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"
#include "crazypng_png.h"

static bool	png_inflate(t_png *png);

bool	png_decompress(t_png *png)
{
	if (png->data.data)
	{
		if (png->compressed_data.data)
			cp_buffer_reset(&png->compressed_data);
		return (true);
	}
	if (!png->compressed_data.data)
		return (false);
	return (png_inflate(png));
}

static bool	png_inflate(t_png *png)
{
	if (!cp_inflate(&png->data, \
		png->compressed_data.data, png->compressed_data.size))
		return (false);
	return (true);
}
