/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_managing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:48:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/05 01:51:18 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"
#include <errno.h>

static bool	verify_png_signature(t_cp_file *file);

t_png	*png_open(char *file_name)
{
	t_png		*png;
	t_cp_file	*file;

	png = ft_calloc(1, sizeof(t_png));
	if (!png)
		return (NULL);
	file = cp_open(file_name, O_RDONLY);
	if (!file)
	{
		free(png);
		return (NULL);
	}
	png->file = file;
	if (!verify_png_signature(file))
	{
		png_close(png);
		return (NULL);
	}
	png->convert_endian = ft_isbigendian();
	if (!png_parse(png))
	{
		png_close(png);
		return (NULL);
	}
	return (png);
}

void	png_close(t_png *png)
{
	if (!png)
		return ;
	cp_buffer_reset(&png->uncompressed_data);
	cp_buffer_reset(&png->data);
	cp_close(png->file);
	free(png);
}

static bool	verify_png_signature(t_cp_file *file)
{
	uint64_t	signature;

	if (cp_fread(&signature, sizeof(uint64_t), 1, file) != 1)
		return (false);
	if (ft_memcmp(&signature, PNG_SIGNATURE, sizeof(uint64_t)) == 0)
	{
		return (true);
	}
	else
	{
		ft_putstr_fd(PNG_ERROR_SIGNATURE, 2);
		return (false);
	}
}
